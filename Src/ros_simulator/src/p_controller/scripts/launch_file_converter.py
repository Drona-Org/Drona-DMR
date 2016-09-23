#!/usr/bin/env python

import xml.etree.ElementTree as ET
import os, sys, argparse, errno
import rospkg
import random, copy

import yaml

rospack = rospkg.RosPack()
p_controller_dir = rospack.get_path('p_controller')

launch_file_template_path = os.path.join(p_controller_dir, "launch/test_motion_planner.launch.template")
rviz_file_template_path = os.path.join(p_controller_dir, "launch/test_motion_planner.rviz.template")

def make_dir(path):
    try:
        os.makedirs(path, exist_ok=True)  # Python>3.2
    except TypeError:
        try:
            os.makedirs(path)
        except OSError as exc: # Python >2.5
            if exc.errno == errno.EEXIST and os.path.isdir(path):
                pass
            else: raise

def workspace_to_launch_file(outdir, outname, workspace_file):
    out_rviz_name = outname + ".rviz"
    out_launch_file_name = outname + ".launch"

    ws_doc = ET.parse(workspace_file)
    launch_doc = ET.parse(launch_file_template_path)
    ws_xml = ws_doc.getroot()
    launch_xml = launch_doc.getroot()

    with open(rviz_file_template_path, "r") as rviz_template_f:
        rviz_yaml = yaml.safe_load(rviz_template_f)

    e = filter(lambda e : e.attrib.get("name") == "map/cmap", launch_xml.findall("param"))[0]
    e.attrib["value"] = e.attrib["value"].format(workspace_xml_path=os.path.relpath(workspace_file, p_controller_dir))

    e = filter(lambda e : e.attrib.get("pkg") == "rviz", launch_xml.findall("node"))[0]
    e.attrib["args"] = e.attrib["args"].format(rviz_path=os.path.join(os.path.relpath(outdir, p_controller_dir), out_rviz_name))

    e = filter(lambda e : e.attrib.get("type") == "test_motion_planner", launch_xml.findall("node"))[0]
    e.attrib["args"] = e.attrib["args"].format(workspace_xml_path=os.path.relpath(workspace_file, p_controller_dir), num_threads=20)
    test_motion_planner_e = e

    mesh_template = filter(lambda e : e.attrib.get("type") == "mesh_visualization", launch_xml.findall("node"))[0]
    launch_xml.remove(mesh_template)

    robot_rviz_marker_template = filter(lambda disp: "nanoplus_visualization" in disp.get("Marker Topic", ""), rviz_yaml["Visualization Manager"]["Displays"])[0]
    import pdb; pdb.set_trace()
    rviz_yaml["Visualization Manager"]["Displays"].remove(robot_rviz_marker_template)

    robots = ws_xml.find("robots").findall("robot")
    for robot in robots:
        robot_id = robot.attrib["id"]
        new_mesh = copy.deepcopy(mesh_template)
        for c in ("r", "g", "b"):
            e = filter(lambda e : e.attrib.get("name") == "color/{0}".format(c), new_mesh.findall("param"))[0]
            e.attrib["value"] = str(random.uniform(0, 1))
        e = filter(lambda e : e.attrib.get("from") == "~odom", new_mesh.findall("remap"))[0]
        e.attrib["to"] = "odom{0}".format(robot_id)
        launch_xml.append(new_mesh)
        # add remapping to node test_motion_planner
        ET.SubElement(test_motion_planner_e, 
                      tag="remap", 
                      attrib={
                                "from": "~odom{0}".format(robot_id), 
                                "to":  "odom{0}".format(robot_id)
                      })
        # Add to rviz display
        new_robot_marker = copy.deepcopy(robot_rviz_marker_template)
        new_robot_marker["Marker Topic"] = new_robot_marker["Marker Topic"].format(robot_id=robot_id)
        rviz_yaml["Visualization Manager"]["Displays"].append(new_robot_marker)

    make_dir(outdir)
    out_launch_file_path = os.path.join(outdir, out_launch_file_name)
    launch_doc.write(out_launch_file_path, encoding='utf-8', xml_declaration=False)
    with open(os.path.join(outdir, out_rviz_name), "w+") as out_rviz_f:
        out_rviz_f.write(yaml.dump(rviz_yaml))

def main():
    parser = argparse.ArgumentParser(description='Convert workspace.xml into ros launch files.')
    parser.add_argument('-dir', '--outdir', type=str, dest="outdir", help="ouput directory")
    parser.add_argument('-o', '--outname', type=str, dest="outname", help="ouput filename")
    parser.add_argument('-w', '--workspace', type=str, dest="workspace", help="workspace.xml file")
    options = parser.parse_args()
    if options.outdir == None:
        options.outdir = os.path.splitext(os.path.basename(options.workspace))[0]
    if options.outname == None:
        options.outname = os.path.splitext(os.path.basename(options.workspace))[0]
    workspace_to_launch_file(options.outdir, options.outname, options.workspace)

if __name__ == '__main__':
    main()

