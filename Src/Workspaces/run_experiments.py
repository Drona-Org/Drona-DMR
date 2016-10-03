import os

exp_base_dir = "Experiments"

launch_files = []

for root, dirs, files in os.walk(exp_base_dir):
	for f in files:
		if os.path.splitext(f)[1] == ".launch":
			launch_files.append(os.path.join(root, f))

stat_file = os.path.join(exp_base_dir, "stats")

env = os.environ.copy()
env['TEST_DRIVER_OUT_STAT_FILE'] = os.path.abspath(stat_file)

from subprocess import Popen, PIPE
import time
def run_experiment(launch_file):
	with open(stat_file, "a") as sf:
		sf.write("--- BEGIN {0}\n".format(launch_file))
	proc = Popen(['roslaunch', launch_file], stdin=PIPE, env=env)
	time.sleep(1)
	proc.stdin.write("r")
	proc.wait()
	with open(stat_file, "a") as sf:
		sf.write("--- END\n")

for launch_file in launch_files:
	run_experiment(launch_file)