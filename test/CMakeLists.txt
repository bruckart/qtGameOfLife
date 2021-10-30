

cmake_minimum_required(VERSION 3.20.4)

project(TestGameOfLife VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)


# Find includes in corresponding build directories.
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOUIC ON)

# Instruct Cmake to run automatically when needed.
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)


set(_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${Qt5Widgets_INCLUDES}
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
)

include_directories(${_INCLUDE_DIRS})

set(_HEADERS
    # ${CMAKE_CURRENT_LIST_DIR}/../include/Cell.h
    # ${CMAKE_CURRENT_LIST_DIR}/../include/Cells.h
    # ${CMAKE_CURRENT_LIST_DIR}/../include/GameOfLifeWidget.h
)

set(_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/../src/Cell.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Cells.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/GameOfLifeWidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TestGameOfLife.cpp
)

message(_HEADERS="${_HEADERS}")
message(qtGrid_header_moc="${qtGrid_header_moc}")

# qt5_wrap_cpp(qtGrid_header_moc ${_HEADERS})


add_executable(testGameOfLife
    ${qtGrid_header_moc}
    # ${qtGrid_ui_moc}
    ${_SOURCES}
)

target_link_libraries(testGameOfLife
    Qt5::Widgets
    GTest::gtest
)

# This adds the colorization and output file for when the test target via "make test"
# is invoked.
add_test(NAME TestGameOfLife 
        COMMAND testGameOfLife 
        "--gtest_color=yes" "--gtest_output=xml:testCase1.xml"
)
