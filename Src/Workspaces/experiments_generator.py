import sys, os, errno
import glob, shutil, re
import math

from config_generator import main as generate_config_from_map
from random_map_generator import main as generate_random_map

sys.path.insert(0, os.path.abspath("../ros_simulator/src/p_controller"))
from scripts.launch_file_converter import main as generate_launch_file

exp_base_dir = "Experiments"

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise

def generate_experiments_for_grid(grid_side, 
                               expected_block_size, 
                               num_robots, 
                               num_starts, 
                               density=0.2,
                               use_generated_maps=False):
    grid_out_dir = "Grid[g={0}_b={1}_s={2}_d={3}]".format(
                        grid_side, expected_block_size, num_starts, density)

    grid_out_dir = os.path.join(exp_base_dir, grid_out_dir)

    mkdir_p(grid_out_dir)

    out_map_file_name = os.path.join(grid_out_dir, "map.txt")

    if not use_generated_maps or not os.path.isfile(out_map_file_name):
        print "Generating " + out_map_file_name
        generate_random_map(['-g', '{0},{0}'.format(grid_side), 
                         '-b', '{0},{0}'.format(expected_block_size), 
                         '-s', str(num_starts),
                         '-e', str(0),
                         '-r', str(max(*num_robots)),
                         '-d', str(density),
                         out_map_file_name]
        )
    else:
        print "Using existing " + out_map_file_name

    for f in os.listdir(grid_out_dir):
        if f != "map.txt":
            shutil.rmtree(os.path.join(grid_out_dir, f))

    for num_robot in num_robots:
        _num_starts = min(num_robot * 4, num_starts)
        out_exp_dir = os.path.join(grid_out_dir, "Experiment[r_{0}_s={1}]".format(num_robot, _num_starts))

        mkdir_p(out_exp_dir)
        
        out_ws_xml_file_name = os.path.join(out_exp_dir, "Workspace.xml")

        generate_config_from_map(out_map_file_name, out_ws_xml_file_name, 
                                    num_robots=num_robot, 
                                    num_starts=_num_starts)

        generate_launch_file(['-dir', out_exp_dir,
                              '-w', out_ws_xml_file_name,
                              '--no-rviz']
                            )

grid_sizes = [16, 32, 64, 128, 256]

possible_num_robots = [4, 8, 16, 32, 64, 128]
num_robots = {g: [x for x in possible_num_robots if x <= g] for g in grid_sizes}

densities = [0.1, 0.15, 0.2]

for density in densities:
    for g in grid_sizes:
        expected_block_size = int(math.floor(float(g) / 10))
        generate_experiments_for_grid(g, expected_block_size, num_robots[g], max(2 * x for x in num_robots[g]), density=density, use_generated_maps=True)
