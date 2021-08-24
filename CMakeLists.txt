cmake_minimum_required(VERSION 3.2)

project (CppDemos)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Load Dependencies
# =================

FIND_PACKAGE( Boost REQUIRED COMPONENTS program_options )

# Includes and Link Dir
# =====================

include_directories(
    src
    ${Boost_INCLUDE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
    )

link_directories( 
    ${CMAKE_INSTALL_PREFIX}/lib
    )

# Build Library
# =============

# add_library(${PROJECT_NAME}
#    )


# Config Demo
# ============

add_executable(config_demo src/config_demo.cpp)

target_link_libraries(config_demo
    ${Boost_LIBRARIES}

    )        


# Smart Pointer Demo
# ==================

add_executable(smart_pointer_member_demo src/smart_pointer_member_demo.cpp)

# Polymorphism Demo
# =================

add_executable(polymorphism_demo src/polymorphism_demo.cpp)