cmake_minimum_required (VERSION 2.8.15)
cmake_policy(VERSION 3.15)
project (VulkanLab C CXX)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL -DGLFW_EXPOSE_NATIVE_X11 -DGLFW_EXPOSE_NATIVE_GLX -DOPENGL_GL_PREFERENCE=LEGACY )

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++17")

set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)
add_subdirectory(ext/nanogui)
set_property(TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies")
add_definitions(${NANOGUI_EXTRA_DEFS})
include_directories(${NANOGUI_EXTRA_INCS})

# glm
find_package(glm REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# glfw
find_package(glfw3 REQUIRED)
list(APPEND glfw_INCLUDE_DIRS "${X11_X11_INCLUDE_PATH}")
list(APPEND glfw_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}")
message(STATUS "glfw3 included at ${GLFW3_INCLUDE_DIR}")


# Assimp
find_package(assimp REQUIRED)

# Threads
find_package(Threads REQUIRED)

# X11
set(_GLFW_X11 1)
find_package(X11 REQUIRED)
list(APPEND glfw_PKG_DEPS "x11")

# Check for XRandR (modern resolution switching and gamma control)
if (NOT X11_Xrandr_INCLUDE_PATH)
    message(FATAL_ERROR "The RandR headers were not found")
endif()

# Check for Xinerama (legacy multi-monitor support)
if (NOT X11_Xinerama_INCLUDE_PATH)
    message(FATAL_ERROR "The Xinerama headers were not found")
endif()

# Check for Xkb (X keyboard extension)
if (NOT X11_Xkb_INCLUDE_PATH)
    message(FATAL_ERROR "The X keyboard extension headers were not found")
endif()

# Check for Xcursor (cursor creation from RGBA images)
if (NOT X11_Xcursor_INCLUDE_PATH)
    message(FATAL_ERROR "The Xcursor headers were not found")
endif()

# Check for XInput (modern HID input)
if (NOT X11_Xi_INCLUDE_PATH)
    message(FATAL_ERROR "The XInput headers were not found")
endif()

list(APPEND glfw_INCLUDE_DIRS "${X11_Xrandr_INCLUDE_PATH}"
        "${X11_Xinerama_INCLUDE_PATH}"
        "${X11_Xkb_INCLUDE_PATH}"
        "${X11_Xcursor_INCLUDE_PATH}"
        "${X11_Xi_INCLUDE_PATH}")

include_directories(glfw ${CMAKE_SOURCE_DIR}/include)
include_directories(nanogui ext/nanogui/include)
include_directories(protobuf Engine/src/Network/definitions)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS Engine/src/Network/protos/addressbook.proto)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# opengl
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})

set(LIBS ${GLFW3_LIBRARY} assimp nanogui ${PROTOBUF_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -fpermissive")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(STB_IMAGE "Engine/vendor/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "Engine/vendor/glad.c")
set(LIBS ${LIBS} GLAD)

file(GLOB_RECURSE xlib_SOURCES "Engine/src/*.cpp")
file(GLOB_RECURSE xlib_HEADERS "Engine/src/*.h")

add_executable(VulkanLab ${xlib_SOURCES} ${xlib_HEADERS} ${PROTO_SRCS} ${PROTO_HDRS})

link_directories(${CMAKE_SOURCE_DIR}/lib)
SET_TARGET_PROPERTIES(VulkanLab PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(VulkanLab PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(VulkanLab PUBLIC ${GLFW3_INCLUDE_DIR})
target_link_libraries(VulkanLab ${CMAKE_SOURCE_DIR}/lib/libGLAD.a ${CMAKE_SOURCE_DIR}/lib/libglfw3.a assimp nanogui ${Protobuf_LIBRARIES} ${ENET_LIBRARIES} ${NANOGUI_EXTRA_LIBS} glm X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
