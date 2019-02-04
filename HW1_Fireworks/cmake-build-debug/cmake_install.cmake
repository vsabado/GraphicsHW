<<<<<<< HEAD
# Install script for directory: /home/vladpc/GraphicsHW/HW1_Fireworks
=======
# Install script for directory: /home/vlad/Git Repositories/GraphicsHW/HW1_Fireworks
>>>>>>> e87de891e0cd7cb3b81ca6ef29d1c1f2df4eb53a

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

<<<<<<< HEAD
# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

=======
>>>>>>> e87de891e0cd7cb3b81ca6ef29d1c1f2df4eb53a
if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/home/vladpc/GraphicsHW/HW1_Fireworks/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/home/vlad/Git Repositories/GraphicsHW/HW1_Fireworks/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> e87de891e0cd7cb3b81ca6ef29d1c1f2df4eb53a
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
