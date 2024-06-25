# If not working, first do: sudo rm -rf /tmp/.docker.xauth
# It still not working, try running the script as root.
## Build the image first
### docker build -t r2_path_planning .
## then run this script
xhost +local:root


XAUTH=/tmp/.docker.xauth

docker run -it \
    --name=r_indigo_container_vers1\
    --env="DISPLAY=$DISPLAY" \
    --env="SCM_OPENGL_SOFTWARE=1" \
    --env="XAUTHORITY=$XAUTH" \
    --device=/dev/dri:/dev/dri \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --volume="$XAUTH:$XAUTH" \
    --volume="/etc/machine-id:/etc/machine-id" \
    --volume="/var/lib/dbus/machine-id:/var/lib/dbus/machine-id" \
    --net=host \
    --runtime=nvidia \
    --privileged \
    osrf/ros:indigo-desktop-full \
    bash

echo "Done."
