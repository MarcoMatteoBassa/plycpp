import numpy as np
import open3d as o3d


def main():
    print("Load a ply point cloud, print it, and render it")
    pcd = o3d.io.read_point_cloud(
        "/tmp/test_intensity.ply")
    o3d.visualization.draw_geometries([pcd])


if __name__ == "__main__":
    main()
