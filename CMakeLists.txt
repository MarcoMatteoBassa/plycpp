cmake_minimum_required(VERSION 3.8)
project(plycpp)

add_compile_options(-Wall -Wextra -Wpedantic)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(GTest REQUIRED)

get_filename_component(MODELS_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/models"
  ABSOLUTE)

include_directories(
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(plycpp SHARED src/plycpp.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PCL_LIBRARIES})

ament_target_dependencies(${PROJECT_NAME} PUBLIC
  pcl_conversions
)

if(BUILD_TESTING)
  add_subdirectory(src/test)
endif()

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets)

install(
  DIRECTORY include/
  DESTINATION include
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
ament_export_dependencies(
  pcl_conversions
)
ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_package()
