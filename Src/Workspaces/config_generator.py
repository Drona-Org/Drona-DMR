import xml.etree.ElementTree as ET
import xml.dom.minidom
import sys, os, itertools
import random

COLOR_BLACK = 0x000000
COLOR_WHITE = 0xffffff
COLOR_RED = 0xff0000
COLOR_GREEN = 0x00ff00
COLOR_BLUE = 0x0000ff
COLOR_YELLOW = COLOR_RED ^ COLOR_GREEN

def offset_coords(list_of_coords, offset):
	minx, miny, minz = offset
	for i in range(len(list_of_coords)):
		x, y, z = list_of_coords[i]
		list_of_coords[i] = x - minx, y - miny, z - minz

def read_goxel_file(fname):
	env_map = {COLOR_RED: [], COLOR_GREEN: [], COLOR_BLUE: [], COLOR_WHITE: [], COLOR_YELLOW: [], COLOR_BLACK: []}
	with open(fname, "r") as goxelf:
		lines = goxelf.readlines()
		for line in lines:
			if line.startswith("#"):
				continue
			x, y, z, color = line.split(" ", 3)
			r, g, b = int(color[0:2], 16), int(color[2:4], 16), int(color[4:6], 16)
			x, y, z, color = int(x), int(y), int(z), (r << 16) ^ (g << 8) ^ b
			if color in env_map:
				env_map[color].append((x, y, z))
			else:
				raise Exception("Unrecognized color")
	xs, ys, zs = zip(*itertools.chain(*env_map.values()))
	minx, miny, minz, maxx, maxy, maxz = min(xs), min(ys), min(zs), max(xs), max(ys), max(zs)
	for coords in env_map.values():
		offset_coords(coords, (minx, miny, minz))
	env_map['dim'] = (maxx - minx + 1, maxy - miny + 1, maxz - minz + 1)
	return env_map

char_color_map = {
	'r': COLOR_RED, 
	'g': COLOR_GREEN, 
	'b': COLOR_BLUE,
	'w': COLOR_WHITE,
	'x': COLOR_BLACK,
	'y': COLOR_YELLOW
}

def flip_axis(env_map, axis=1):
	dim = env_map['dim']
	for coords in env_map.values():
		if type(coords) == list:
			for i in range(len(coords)):
				coord = list(coords[i])
				coord[axis] = dim[axis] - coord[axis] - 1
				coords[i] = tuple(coord)

def read_map_file(map_file):
	env_map = {COLOR_RED: [], COLOR_GREEN: [], COLOR_BLUE: [], COLOR_WHITE: [], COLOR_YELLOW: [], COLOR_BLACK: []}
	with open(map_file, "r") as mapf:
		maxx, j, k = 0, 0, 0
		for line in mapf.readlines():
			if line.startswith("#"):
				continue
			if line.startswith("==="):
				k += 1
			maxx = max(len(line) - 1, maxx)
			for i, c in enumerate(line):
				if not c.isspace():
					env_map[char_color_map[c]].append((i, j, k))
			j += 1
	env_map['dim'] = (maxx, j, k + 1)
	flip_axis(env_map, 1)
	return env_map

def find_or_create(xml_element, tag):
	r = xml_element.find(tag)
	if r == None:
		return ET.SubElement(xml_element, tag)
	return r

def set_xml_config(xml_config, env_map):
	# set dimension
	dim = env_map['dim']
	dimension_element = find_or_create(xml_config, "dimension")
	dimension_element.set('x', str(dim[0]))
	dimension_element.set('y', str(dim[1]))
	dimension_element.set('z', str(dim[2]))
	# set robot start locations
	robots_element = find_or_create(xml_config, "robots")
	robots_element.clear()
	robots_count = 0
	for start in env_map[COLOR_BLUE]:
		robot_element = ET.SubElement(robots_element, "robot")
		start_element = ET.SubElement(robot_element, "start")
		robot_element.set('id', str(robots_count))
		robots_count += 1
		start_element.set('x', str(start[0]))
		start_element.set('y', str(start[1]))
		start_element.set('z', str(start[2]))
	def create_list_of_coord(color, name):
		robots_element = find_or_create(xml_config, name)
		robots_element.clear()
		for coord in env_map[color]:
			coord_element = ET.SubElement(robots_element, "coord")
			coord_element.set('x', str(coord[0]))
			coord_element.set('y', str(coord[1]))
			coord_element.set('z', str(coord[2]))
	create_list_of_coord(COLOR_WHITE, "obstacles")
	create_list_of_coord(COLOR_GREEN, "starts")
	create_list_of_coord(COLOR_RED, "ends")
	create_list_of_coord(COLOR_YELLOW, "charging_stations")
	return xml_config

def take_num_robots(env_map, num_robots):
	env_map[COLOR_BLUE] = random.sample(env_map[COLOR_BLUE], num_robots)

def take_num_starts(env_map, num_starts):
	env_map[COLOR_GREEN] = random.sample(env_map[COLOR_GREEN], num_starts)

def main(input_file, config_file_name, num_robots=None, num_starts=None):
	with open(input_file, "r") as inputf:
		input_is_map = inputf.readline().startswith("# Map")
	if input_is_map:
		env_map = read_map_file(input_file)
	else:
		env_map = read_goxel_file(input_file)
	if os.path.isfile(config_file_name):
		config_document = ET.parse(config_file_name)
		xml_config = config_document.getroot()
		xml_config.tag = "configuration"
	else:
		xml_config = ET.Element('configuration')
		config_document = ET.ElementTree(xml_config)
	if num_robots:
		take_num_robots(env_map, num_robots)
	if num_starts:
		take_num_starts(env_map, num_starts)
	set_xml_config(xml_config, env_map)
	config_document.write(config_file_name, encoding='utf-8', xml_declaration=True) 
	
	xml_f = xml.dom.minidom.parse(config_file_name) # or xml.dom.minidom.parseString(xml_string)
	with open(config_file_name, "w+") as prettifyf:
		prettifyf.write(xml_f.toprettyxml())

if __name__ == "__main__":
	main(sys.argv[1], sys.argv[2])
