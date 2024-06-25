FROM osrf/ros:indigo-dekstop-full

RUN 
RUN apt-get update && apt-get install -y git && apt-get install -y python3-pip && apt install -y libspatialindex-dev && apt install -y openssh-server && apt-get install -y \
    x11-apps \
    xterm \
    libcanberra-gtk* \
    libglew-dev \
    mesa-utils \
    && rm -rf /var/lib/apt/lists/*

RUN source /opt/ros/indigo/setup.bash
RUN git clone https://github.com/Alkylite/robuild_docker_tapir.git

RUN cd robuild_docker_tapir/rosbuilt_tapir/tapir-master

RUN source /opt/ros/indigo/setup.bash

RUN make ros
RUN make vrep_plugin

RUN echo "ALL DONE - use 'cd problems/tag' and run './simulate-ros' to start siumlation"


