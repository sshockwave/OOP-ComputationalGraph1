project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
        graph.cpp
        graph.h
        main.cpp
        node.cpp
        node.h
        operation_node.cpp
        operation_node.h)
