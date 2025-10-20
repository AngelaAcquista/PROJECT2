cmake_minimum_required(VERSION 3.30)
project(PROJECT2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(PROJECT2
    .idea/.gitignore
    .idea/editor.xml
    .idea/modules.xml
    .idea/PROJECT2.iml
    .idea/vcs.xml
    .idea/workspace.xml
    main.cpp
    README.md)
