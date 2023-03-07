cmake_minimum_required(VERSION 3.8)
project(plycpp)

add_compile_options(-Wall -Wextra -Wpedantic)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)

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

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets)

install(
  DIRECTORY include/
  DESTINATION include
)
add_executable(run_test src/test.cpp)
target_link_libraries(run_test plycpp)
install(TARGETS run_test
  DESTINATION bin/${PROJECT_NAME}
)
add_executable(run_test_intensity src/test_intensity.cpp)
target_link_libraries(run_test_intensity plycpp)
install(TARGETS run_test_intensity
  DESTINATION bin/${PROJECT_NAME}
)
ament_export_dependencies(
  pcl_conversions
)
ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_package()
