import xml.etree.ElementTree as ET
import xml.dom.minidom
import sys, os, itertools

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
	for start in env_map[COLOR_YELLOW]:
		robot_element = ET.SubElement(robots_element, "robot")
		start_element = ET.SubElement(robots_element, "start")
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
	return xml_config

def main(goxel_file_name, config_file_name):
	env_map = read_goxel_file(goxel_file_name)
	if os.path.isfile(config_file_name):
		config_document = ET.parse(config_file_name)
		xml_config = config_document.getroot()
		xml_config.tag = "configuration"
	else:
		xml_config = ET.Element('configuration')
		config_document = ET.ElementTree(xml_config)
	set_xml_config(xml_config, env_map)
	config_document.write(config_file_name, encoding='utf-8', xml_declaration=True) 
	
	xml_f = xml.dom.minidom.parse(config_file_name) # or xml.dom.minidom.parseString(xml_string)
	with open(config_file_name, "w+") as prettifyf:
		prettifyf.write(xml_f.toprettyxml())

if __name__ == "__main__":
	main(sys.argv[1], sys.argv[2])
