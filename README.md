# ublox2rinex
an ROS package to convert the GNSS raw measurements from topic "/ublox_gps_node/rxmraw" in ROS bag to RINEX file. tested on California part of the UrbanLoco dataset.

Compile the code:

Firstly create an ROS workspace mkdir -p ~/ublox_ws/src

cd ~/ublox_ws/src

catkin_init_workspace

Then download this package, and put it inside ~/ublox_ws/src.

cd ~/ublox_ws

catkin_make

Run the code:

Open the first terminal, input: roscore

Then open the second terminal, input: cd ~/ublox_ws

source devel/setup.bash

rosrun ublox2rinex ublox_raw_parser

Then open the third terminal, input: rosbag play PATH_OF_YOUR_BAG.bag

Finally you will see a file named rinex_CA_20190828184706.obs inside ~/ublox_ws/

That is the rinex file.
