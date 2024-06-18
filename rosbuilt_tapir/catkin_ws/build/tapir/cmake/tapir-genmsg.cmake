# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "tapir: 1 messages, 7 services")

set(MSG_I_FLAGS "-Itapir:/home/crazy/Desktop/catkin_ws/src/tapir/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(tapir_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv" ""
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv" ""
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv" "geometry_msgs/Point:geometry_msgs/PoseStamped:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv" ""
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv" ""
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg" "std_msgs/Float32:std_msgs/Header:std_msgs/Int32"
)

get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv" NAME_WE)
add_custom_target(_tapir_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tapir" "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Int32.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)

### Generating Services
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)
_generate_srv_cpp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
)

### Generating Module File
_generate_module_cpp(tapir
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(tapir_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(tapir_generate_messages tapir_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv" NAME_WE)
add_dependencies(tapir_generate_messages_cpp _tapir_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tapir_gencpp)
add_dependencies(tapir_gencpp tapir_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tapir_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Int32.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)

### Generating Services
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)
_generate_srv_lisp(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
)

### Generating Module File
_generate_module_lisp(tapir
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(tapir_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(tapir_generate_messages tapir_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv" NAME_WE)
add_dependencies(tapir_generate_messages_lisp _tapir_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tapir_genlisp)
add_dependencies(tapir_genlisp tapir_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tapir_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Int32.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)

### Generating Services
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)
_generate_srv_py(tapir
  "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
)

### Generating Module File
_generate_module_py(tapir
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(tapir_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(tapir_generate_messages tapir_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStopSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosCopyPasteObjects.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectPose.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosGetObjectHandle.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosSetObjectPosition.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosStartSimulation.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/msg/VrepInfo.msg" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/crazy/Desktop/catkin_ws/src/tapir/srv/simRosLoadScene.srv" NAME_WE)
add_dependencies(tapir_generate_messages_py _tapir_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tapir_genpy)
add_dependencies(tapir_genpy tapir_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tapir_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tapir
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(tapir_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(tapir_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tapir
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(tapir_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(tapir_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tapir
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(tapir_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(tapir_generate_messages_py geometry_msgs_generate_messages_py)
endif()
