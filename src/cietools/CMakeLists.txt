cmake_minimum_required(VERSION 3.30)
project(CIETools C)

set(CMAKE_C_STANDARD 11)
find_package(Python3 3.13 REQUIRED COMPONENTS Interpreter Development)

add_library(CIETools SHARED
        cietools.c
        conversions.c
        color_structs.h
        color_difference.h
        color_difference.c
        conversions.h
        py_operations/rgb_conversions.c
        py_operations/lch_conversions.h
        py_operations/lch_conversions.c
        py_operations/lch_conversions.h
        py_operations/lab_conversions.c
        py_operations/lab_conversions.h
        py_operations/xyz_conversions.c
        py_operations/xyz_conversions.h
        py_operations/delta_e.c
        py_operations/delta_e.h
)

if(WIN32)
    set_target_properties(CIETools PROPERTIES
            PREFIX ""
            OUTPUT_NAME "cietools"
            SUFFIX ".pyd"
    )
endif()

if (Python3_FOUND)
    message("Python include directory: ${Python3_INCLUDE_DIRS}")
    message("Python version is: ${Python3_VERSION}")
    include_directories(${Python3_INCLUDE_DIRS})
    target_link_libraries(CIETools ${Python3_LIBRARIES})
endif()

install(TARGETS CIETools
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)