#include <iostream>

#include "plycpp/plycpp.h"

pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
const std::string filename = "/tmp/test.ply";

pcl::PointCloud<pcl::PointXYZ>::Ptr loaded_cloud(new pcl::PointCloud<pcl::PointXYZ>());

TEST(TestpointXYZCase, TestpointXYZ) {
  cloud->width = 2;
  cloud->height = 1;
  cloud->points.resize(2);
  cloud->points[0].x = 1.0;
  cloud->points[0].y = 2.0;
  cloud->points[0].z = 3.0;
  cloud->points[1].x = 5.0;
  cloud->points[1].y = 6.0;
  cloud->points[1].z = 7.0;

  // Save the point cloud to a PLY file
  std::cout << "saving ply file" << std::endl;
  plycpp::savePLYFile(filename, cloud);

  std::cout << "cloud 1 size: " << cloud->points.size() << std::endl;

  // Load the point cloud from the PLY file
  try {
    plycpp::loadPLYFile(filename, loaded_cloud);
  } catch (plycpp::Exception& e) {
    std::cout << "got exception " << e.what() << std::endl;
  }

  std::cout << "cloud 2 size: " << loaded_cloud->points.size() << std::endl;

  for (size_t index = 0; index < loaded_cloud->points.size(); index++) {
    std::cout << "x: " << loaded_cloud->points.at(index).x
              << " y: " << loaded_cloud->points.at(index).y
              << " z: " << loaded_cloud->points.at(index).z << std::endl;
  }

  ASSERT_EQ(cloud->size(), loaded_cloud->size());
  for (int i = 0; i < cloud->size(); i++) {
    bool points_are_different = (cloud->points[i].x != loaded_cloud->points[i].x ||
                                 cloud->points[i].y != loaded_cloud->points[i].y ||
                                 cloud->points[i].z != loaded_cloud->points[i].z);
    EXPECT_FALSE(points_are_different);
  }
  EXPECT_TRUE(std::filesystem::exists("/tmp/test.ply"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
