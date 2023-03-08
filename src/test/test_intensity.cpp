#include <iostream>

#include "plycpp/plycpp.h"

pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>());
const std::string filename = "/tmp/test_intensity.ply";

pcl::PointCloud<pcl::PointXYZI>::Ptr loaded_cloud(new pcl::PointCloud<pcl::PointXYZI>());

TEST(TestpointXYZICase, TestpointXYZI) {
  cloud->width = 2;
  cloud->height = 1;
  cloud->points.resize(2);
  cloud->points[0].x = 1.0;
  cloud->points[0].y = 2.0;
  cloud->points[0].z = 3.0;
  cloud->points[0].intensity = 4.0;
  cloud->points[1].x = 5.0;
  cloud->points[1].y = 6.0;
  cloud->points[1].z = 7.0;
  cloud->points[1].intensity = 8.0;

  // Save the point cloud to a PLY file
  std::cout << "saving ply file" << std::endl;
  plycpp::savePLYFileI(filename, cloud);

  std::cout << "cloud 1 size: " << cloud->points.size() << std::endl;

  // Load the point cloud from the PLY file
  try {
    plycpp::loadPLYFileI(filename, loaded_cloud);
  } catch (plycpp::Exception& e) {
    std::cout << "got exception " << e.what() << std::endl;
  }

  std::cout << "cloud 2 size: " << loaded_cloud->points.size() << std::endl;

  for (size_t index = 0; index < loaded_cloud->points.size(); index++) {
    std::cout << "x: " << loaded_cloud->points.at(index).x
              << " y: " << loaded_cloud->points.at(index).y
              << " z: " << loaded_cloud->points.at(index).z
              << " intensity: " << loaded_cloud->points[index].intensity << std::endl;
  }

  //   Check if the loaded point cloud is equal to the original point cloud
  bool test_passed = true;
  if (cloud->size() != loaded_cloud->size()) {
    std::cout << "Error: point cloud sizes do not match" << std::endl;
    test_passed = false;
    EXPECT_EQ(test_passed, false);
  }
  for (int i = 0; i < cloud->size(); i++) {
    if (cloud->points[i].x != loaded_cloud->points[i].x ||
        cloud->points[i].y != loaded_cloud->points[i].y ||
        cloud->points[i].z != loaded_cloud->points[i].z ||
        cloud->points[i].intensity != loaded_cloud->points[i].intensity) {
      std::cout << "Error: point " << i << " does not match" << std::endl;
      test_passed = false;
      EXPECT_EQ(test_passed, false);
    }
  }

  EXPECT_EQ(test_passed, true);
  EXPECT_TRUE(std::filesystem::exists("/tmp/test_intensity.ply"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}