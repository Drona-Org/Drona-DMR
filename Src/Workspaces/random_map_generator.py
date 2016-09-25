import itertools
import numpy as np
import numpy.random as npr

color_code_map = {
    0: " ",
    1: "w",
    2: "y",
    3: "r",
    4: "g",
    5: "b",
    6: "l"
}
color_code_map_inv = {v: k for k, v in color_code_map.items()}

def cell_neighbors(coord, grid_dim):
    assert len(coord) == len(grid_dim)
    zero = np.zeros(len(grid_dim))
    ret = []
    for offset in itertools.product(*itertools.repeat((-1, 0, 1), len(grid_dim))):
        if np.equal(offset, zero).all():
            continue
        neighbor = np.add(coord, offset)
        if np.logical_and(np.less_equal(zero, neighbor), np.less(neighbor, grid_dim)).all():
            ret.append(neighbor)
    return ret

def generate_special_locations(grid, num_locs, color):
    unoccupied_idxs = np.argwhere(grid == 0)
    # for idx in unoccupied_idxs:
    prob = np.array(map(lambda coord: np.count_nonzero(grid[list(np.array(cell_neighbors(coord, grid.shape)).T)] == 1), unoccupied_idxs)) + 0.5
    prob /= np.sum(prob)
    fill_idxs = np.random.choice(len(unoccupied_idxs), size=num_locs, p=prob)
    grid[list(unoccupied_idxs[fill_idxs].T)] = color_code_map_inv[color]

def generate_map(options):
    grid = generate_obstacles(options.grid_size, options.expected_block_size)
    generate_special_locations(grid, options.num_robots, "b")
    generate_special_locations(grid, options.num_starts, "g")
    generate_special_locations(grid, options.num_ends, "r")
    generate_special_locations(grid, options.num_chargings, "y")
    return grid

def generate_obstacles(dim, expected_cube_size=None):
    if not expected_cube_size:
        expected_cube_size = np.maximum(np.array(dim) / 8, np.ones(len(dim)))
    grid = np.zeros(dim)
    stop = False
    for i in range(20):
        grid = put_random_cube(grid, expected_cube_size)
    return grid

def put_random_cube(grid, expected_cube_size):
    grid_bk = np.copy(grid)
    while True:
        new_cube = np.minimum(tuple(map(lambda x: npr.binomial(2 * x - 1, 0.4) + 1, expected_cube_size)), grid.shape)
        max_origin = np.subtract(grid.shape, new_cube)
        origin = tuple(map(lambda x: npr.randint(low=0, high=x+1), max_origin))
        sub_m_slice = map(lambda t: slice(*t), zip(origin, np.add(origin, new_cube)))
        if (grid[sub_m_slice] == 1).all():
            continue
        grid_bk = np.copy(grid)
        grid[sub_m_slice] = 1
        if test_connected(grid):
            return grid
        else:
            grid = grid_bk


def test_connected(grid):
    start = zip(*np.where(grid == 0))[0]
    mark = grid == 1
    walk_grid(grid, start, mark)
    return mark.all()

def walk_grid(grid, start, mark):
    frontier = [start]
    mark[tuple(start)] = True
    while len(frontier) > 0:
        loc = frontier.pop()
        for i in range(len(grid.shape)):
            l = np.copy(loc)
            l[i] = loc[i] - 1
            if l[i] >= 0 and not mark[tuple(l)]:
                mark[tuple(l)] = True
                frontier.append(np.copy(l))
            l[i] = loc[i] + 1
            if l[i] < grid.shape[i] and not mark[tuple(l)]:
                mark[tuple(l)] = True
                frontier.append(np.copy(l))


def grid_to_str(grid):
    s = ""
    if len(grid.shape) == 2:
        for j, col in enumerate(grid):
            for i, v in enumerate(col):
                s += color_code_map[v]
            s += "\n"
    elif len(grid.shape) == 3:
        s += grid_to_str(grid[:,:,0])
        for i in range(1, grid.shape[2]):
            s += "=" * grid.shape[0]
            s += grid_to_str(grid[:,:,i])
    else:
        raise Exception("Invalid grid dimension")
    return s

def comma_seperated_list(s):
    try:
        return tuple(map(int, s.split(',')))
    except:
        raise argparse.ArgumentTypeError("Coordinates must be x,y,z")

import argparse
def main():
    parser = argparse.ArgumentParser(description='Random 2/3D grid map generator.')
    parser.add_argument('outfile', type=str, help="ouput filename")
    parser.add_argument('-g', '--grid-size', type=comma_seperated_list, dest="grid_size", help="size of the grid", required = True)
    parser.add_argument('-b', '--expected-block-size', type=comma_seperated_list, dest="expected_block_size", help="Expectation of random obstacle's block size", required=True)
    parser.add_argument('-s', '--num-starts', type=int, dest="num_starts", help="Number of start locations(green)", default=1)
    parser.add_argument('-e', '--num-ends', type=int, dest="num_ends", help="Number of end locations(red)", default=1)
    parser.add_argument('-c', '--num-chargings', type=int, dest="num_chargings", help="Number of charinging locations(yellow)", default=0)
    parser.add_argument('-r', '--num-robots', type=int, dest="num_robots", help="Number of robots(blue for its start locations)", default=2)
    options = parser.parse_args()
    assert len(options.expected_block_size) == len(options.grid_size)
    grid = generate_map(options)
    with open(options.outfile, "w+") as outfile:
        outfile.write("# Map\n")
        outfile.write(grid_to_str(grid))


if __name__ == "__main__":
    main()
