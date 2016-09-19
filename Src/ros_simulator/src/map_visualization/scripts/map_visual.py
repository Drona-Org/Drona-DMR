#!/usr/bin/env python
import rospy
from sensor_msgs.msg import PointCloud
import xml.etree.ElementTree as ET
from geometry_msgs.msg import Point32
import std_msgs.msg

def create_pointcload(points, res):
    obscacles_cloud = PointCloud()
    header = std_msgs.msg.Header()
    header.stamp = rospy.Time.now()
    header.frame_id = '/simulator'
    obscacles_cloud.header = header
    for p in points:
        obscacles_cloud.points.append(Point32(p[0] * res, p[1] * res, p[2] * res))
    return obscacles_cloud

def parse_config(config_file_name):
    config_document = ET.parse(config_file_name)
    xml_config = config_document.getroot()
    assert xml_config.tag == "configuration"
    def parse_coords(name):
        element =  xml_config.find(name)
        return [(int(child.attrib.get('x', 0)), 
                 int(child.attrib.get('y', 0)), 
                 int(child.attrib.get('z', 0)))
            for child in element.findall("coord")] if element != None else []
    return parse_coords("obstacles"), parse_coords("starts"), parse_coords("ends"), parse_coords("charging_stations")

def run_publisher():
    rospy.init_node('map_visualization', anonymous=True)
    res = rospy.get_param('~map/res', 0.2)
    config_file_name = rospy.get_param('~map/cmap')
    obstacles, starts, ends, chargings = parse_config(config_file_name)
    obs_pub = rospy.Publisher(rospy.resolve_name("~obs_array"), PointCloud, queue_size=10)
    ends_pub = rospy.Publisher(rospy.resolve_name("~ends_array"), PointCloud, queue_size=10)
    starts_pub = rospy.Publisher(rospy.resolve_name("~starts_array"), PointCloud, queue_size=10)
    chargings_pub = rospy.Publisher(rospy.resolve_name("~chargings_array"), PointCloud, queue_size=10)
    rospy.sleep(1)
    obscacles_cloud = create_pointcload(obstacles, res)
    starts_cloud = create_pointcload(starts, res)
    ends_cloud = create_pointcload(ends, res)
    chargings_cloud = create_pointcload(chargings, res)
    obs_pub.publish(obscacles_cloud)
    starts_pub.publish(starts_cloud)
    ends_pub.publish(ends_cloud)
    chargings_pub.publish(chargings_cloud)

if __name__ == "__main__":
    try:
        run_publisher()
    except rospy.ROSInterruptException:
        pass
