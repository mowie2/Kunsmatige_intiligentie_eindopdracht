# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(pigisland)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wpedantic)#  -Werror)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

  
add_executable(pigisland
	src/kmint/pigisland/main.cpp
	src/kmint/pigisland/node_algorithm.cpp
	src/kmint/pigisland/resources.cpp
	src/kmint/pigisland/shark.cpp
	src/kmint/pigisland/boat.cpp
	src/kmint/pigisland/pig.cpp
	src/states/AttackState.cpp
	src/states/RestState.cpp
	src/states/WanderState.cpp
	src/states/ScaredState.cpp
	src/Astar.cpp
	src/states/SavingPigsState.cpp
	src/states/GrassIsland.cpp
	src/states/Forest.cpp
	src/kmint/pigisland/Forces/Alignment.cpp
	src/kmint/pigisland/Forces/Cohesion.cpp
	src/kmint/pigisland/Forces/Seperation.cpp
	src/kmint/pigisland/Forces/ToKnabbel.cpp
	src/states/GrainField.cpp
	src/kmint/pigisland/Forces/ToPorcus.cpp
	src/kmint/pigisland/Forces/AwayFromBorder.cpp
	src/kmint/pigisland/BorderMarker.cpp
  )

target_compile_features(pigisland PUBLIC cxx_std_17)
target_link_libraries(pigisland PRIVATE kmint)
target_include_directories(pigisland PRIVATE 
  src
  include)

add_custom_target(pigisland-resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
