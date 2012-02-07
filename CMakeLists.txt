cmake_minimum_required(VERSION 2.6)
project(QweakSimG4)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

GEANT4_COLLATE_APPLICATION_SOURCES(my_project_sources)

add_executable(QweakSimG4 ${my_project_sources})
add_executable(QweakSimRoot ${my_project_sources})
target_link_libraries(QweakSimG4 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

