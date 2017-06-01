# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "savvy: 2 messages, 0 services")

set(MSG_I_FLAGS "-Isavvy:/home/lv/catkin_ws/src/savvy/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(savvy_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg" NAME_WE)
add_custom_target(_savvy_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "savvy" "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg" ""
)

get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg" NAME_WE)
add_custom_target(_savvy_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "savvy" "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(savvy
  "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/savvy
)
_generate_msg_cpp(savvy
  "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/savvy
)

### Generating Services

### Generating Module File
_generate_module_cpp(savvy
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/savvy
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(savvy_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(savvy_generate_messages savvy_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg" NAME_WE)
add_dependencies(savvy_generate_messages_cpp _savvy_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg" NAME_WE)
add_dependencies(savvy_generate_messages_cpp _savvy_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(savvy_gencpp)
add_dependencies(savvy_gencpp savvy_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS savvy_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(savvy
  "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/savvy
)
_generate_msg_lisp(savvy
  "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/savvy
)

### Generating Services

### Generating Module File
_generate_module_lisp(savvy
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/savvy
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(savvy_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(savvy_generate_messages savvy_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg" NAME_WE)
add_dependencies(savvy_generate_messages_lisp _savvy_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg" NAME_WE)
add_dependencies(savvy_generate_messages_lisp _savvy_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(savvy_genlisp)
add_dependencies(savvy_genlisp savvy_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS savvy_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(savvy
  "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy
)
_generate_msg_py(savvy
  "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy
)

### Generating Services

### Generating Module File
_generate_module_py(savvy
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(savvy_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(savvy_generate_messages savvy_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/fourvel.msg" NAME_WE)
add_dependencies(savvy_generate_messages_py _savvy_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lv/catkin_ws/src/savvy/msg/ultrasonicStamped.msg" NAME_WE)
add_dependencies(savvy_generate_messages_py _savvy_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(savvy_genpy)
add_dependencies(savvy_genpy savvy_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS savvy_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/savvy)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/savvy
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(savvy_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(savvy_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/savvy)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/savvy
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(savvy_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(savvy_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/savvy
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(savvy_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(savvy_generate_messages_py geometry_msgs_generate_messages_py)
endif()
