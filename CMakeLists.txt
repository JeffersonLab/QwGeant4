# Require at least cmake 2.6.0
cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# Name of this project
project(QweakSimG4)

# Where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ 
# is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Load Geant4 through Find and Use files (the Geant4_DIR directory is where
# the Geant4 cmake Find and Use files can be found)
set(Geant4_DIR $ENV{G4INSTALL}/build)
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

# Load ROOT and setup include directory
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

# Create ROOT dictionary
ROOT_GENERATE_DICTIONARY(${CMAKE_CURRENT_SOURCE_DIR}/src/QweakSimUserMainEvent_Dict
	${CMAKE_CURRENT_SOURCE_DIR}/include/QweakSimUser*.hh
	LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/*_LinkDef.hh)
add_custom_target(dict ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/QweakSimUserMainEvent_Dict.cxx)

# Add the project include directory and put all source files in my_project_sources
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB my_project_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/QweakSimUserMainEvent_Dict.cc)

# Add the target executables
add_executable(QweakSimG4   QweakSimG4.cc   ${my_project_sources})
add_executable(QweakSimRoot QweakSimRoot.cc ${my_project_sources})

# Link the ROOT and Geant4 libraries
target_link_libraries(QweakSimG4   ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
target_link_libraries(QweakSimRoot ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
