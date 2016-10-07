import sys, re
from collections import defaultdict
import pandas as pd
import matplotlib.pyplot as plt  
import numpy as np

def read_stats(stat_file):
    def match_float(s, prefix=""):
        return float(re.search(prefix + r"([-+]?\d*\.\d+|\d+)", s).group(1))
    data = defaultdict(list)
    while True:
        begin = stat_file.readline()
        if not begin:
            break;
        data["grid_size"].append(int(re.search(r'g=(\d+)', begin).group(1)))
        data["robot_num"].append(int(re.search(r'r_(\d+)', begin).group(1)))
        data["start_num"].append(min(int(x.group(1)) for x in re.finditer(r's=(\d+)', begin)))
        data["density"].append(match_float(begin, prefix="d="))
        data["astar_t_include"].append(match_float(stat_file.readline()))
        data["astar_t_exclude"].append(match_float(stat_file.readline()))
        data["num_calls_include"].append(int(match_float(stat_file.readline())))
        data["num_calls_exclude"].append(int(match_float(stat_file.readline())))
        data["total_length_sln"].append(int(match_float(stat_file.readline())))
        end = stat_file.readline()

    return pd.DataFrame(data)

def process_data(df):
    df['avg_astar_t_included'] = df['astar_t_include']/df['num_calls_include']
    df['avg_astar_t_excluded'] = df['astar_t_exclude']/df['num_calls_exclude']
    df['solve_t_per_distance'] = df['astar_t_include']/df['total_length_sln']
    return df.groupby(["grid_size", "robot_num"]).mean().reset_index()


## BEGIN plot

# These are the "Tableau 20" colors as RGB.    
tableau20 = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),    
             (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),    
             (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),    
             (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),    
             (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)] 
# Scale the RGB values to the [0, 1] range, which is the format matplotlib accepts.    
for i in range(len(tableau20)):    
    r, g, b = tableau20[i]    
    tableau20[i] = (r / 255., g / 255., b / 255.)  

import math
def float_roundup(f, r):
    return math.floor(f / r) * r + r

def plot_data(df):
    plt.figure(figsize=(12, 14))    
    # Remove the plot frame lines. They are unnecessary chartjunk.    
    ax = plt.subplot(111)    
    ax.spines['left'].set_bounds(0, 0.01)
    ax.spines['bottom'].set_bounds(0, 0.075)
    ax.spines["top"].set_visible(False)    
    ax.spines["right"].set_visible(False)    
    # Ensure that the axis ticks only show up on the bottom and left of the plot.    
    # Ticks on the right and top of the plot are generally unnecessary chartjunk.    
    ax.get_xaxis().tick_bottom()    
    ax.get_yaxis().tick_left()

    # # Limit the range of the plot to only where the data is.    
    # # Avoid unnecessary whitespace.    
    # plt.ylim(0, 90)    
    # plt.xlim(1968, 2014)    
    # Make sure your axis ticks are large enough to be easily read.    
    # You don't want your viewers squinting to read your plot.
    plt.yticks(np.arange(0, 1.0, 0.1), fontsize=14)    
    plt.xticks(fontsize=14)

    df = df.drop('total_length_sln', 1)
    df = df.drop('num_calls_exclude', 1)
    df = df.drop('num_calls_include', 1)
    df = df.drop('astar_t_exclude', 1)
    df = df.drop('astar_t_include', 1)
    df = df.drop('start_num', 1)
    df = df.drop('density', 1)
    grid_sizes = sorted(set(df.grid_size.values))
    plt.xticks(range(len(grid_sizes)), grid_sizes)
    gb = df.groupby("robot_num")
    max_y_pos = 0
    for rank, (name, sub_df) in enumerate(gb):
        print sub_df.avg_astar_t_included.values
        plt.plot(map(lambda x: grid_sizes.index(x), sub_df.grid_size.values), 
                sub_df.avg_astar_t_included.values,
                lw=2.5, color=tableau20[rank])
        y_pos = max(sub_df.avg_astar_t_included.values)
        plt.text(len(grid_sizes) - 1 + 0.1, y_pos, name, fontsize=14, color=tableau20[rank])
        max_y_pos = max(max_y_pos, y_pos)

    ylim = float_roundup(max_y_pos, 0.05) + 0.01
    plt.ylim(0, ylim)  
    plt.xlim(xmin=0)
    plt.text(len(grid_sizes) - 1 + 0.2, ylim / 2 + 0.05, "Number of Robots", fontsize=16, rotation=270)

    # Provide tick lines across the plot to help your viewers trace along    
    # the axis ticks. Make sure that the lines are light and small so they    
    # don't obscure the primary data lines.    
    for y in np.arange(0, ylim, 0.05):    
        plt.plot(range(len(grid_sizes)), [y] * len(grid_sizes), "--", lw=0.5, color="black", alpha=0.3)    
      
    # Remove the tick marks; they are unnecessary with the tick lines we just plotted.    
    plt.tick_params(axis="both", which="both", bottom="off", top="off",    
                    labelbottom="on", left="off", right="off", labelleft="on")
    plt.xlabel("Grid Size", fontsize=16)  
    plt.ylabel("A* solving time(sec)", fontsize=16)  
    
    # plt.text(len(grid_sizes) - 1 + 0.1, y_pos + , name, fontsize=14, color=tableau20[rank])    
    plt.savefig("plot_ex.png", bbox_inches="tight")

from tabulate import tabulate

def to_latex(df):
    df = df.drop('total_length_sln', 1)
    df = df.drop('num_calls_exclude', 1)
    df = df.drop('num_calls_include', 1)
    df = df.drop('astar_t_exclude', 1)
    df = df.drop('astar_t_include', 1)
    df = df.drop('start_num', 1)
    df = df.drop('density', 1)
    grid_sizes = sorted(set(df.grid_size.values))
    table = []
    for num, g1 in df.groupby("robot_num"):
        row = [num] + ["N/A"] * len(grid_sizes)
        table.append(row)
        for grid_size, g2 in g1.groupby("grid_size"):
            row[grid_sizes.index(grid_size) + 1] = round(g2.avg_astar_t_excluded.values[0], 4)
    headers = ["Num of robots"] + map(lambda x: "{0}x{0}".format(x), grid_sizes)
    print tabulate(table, headers, tablefmt="latex")
if __name__ == '__main__':
    df = read_stats(open(sys.argv[1], "r"))
    df = process_data(df)
    df.to_csv("data.csv")
    plot_data(df)
    to_latex(df)