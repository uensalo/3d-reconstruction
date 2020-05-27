# 3d-reconstruction
Semantic 3D Point Cloud Reconstruction from RGBD images and semantic labels.

Dependencies: TinyPly (point cloud output), Eigen (matrix operations), OpenCV (image IO and feature extraction/matching).

Further documentation of files under include/recon are marked as TODOs.

CMake Support: Currently, building this would be very painful, as it is only source code for the time being.

Invocation for Sample App:
3d-reconstruction.exe <directory_name> <image_index> <output_prefix>

Directory structure for images:
├───depth
├───metadata
├───rgb
└───semantic
depth, rgb, and semantic should contain images named <index>.png, and each image in each of these directories should match at the index they are given (i.e. depth map with index i should correspond to the depth map of color image i and semantic image i should be a semantically labelled version of color image i). Note that "depth" should contain images obtained and encoded as per [SyncCamera's](https://github.com/uensalo/SyncCamera)'s [KinectCamera](https://github.com/uensalo/SyncCamera/blob/master/app/src/main/java/com/moveit/synccamera/KinectCamera.java) class.

The metadata directory should contain three files: color.txt, depth.txt and labels.csv. The format of color.txt and depth.txt should be as follows:
<Schema>
[fx, fy, cx, cy, s]
[qx, qy, qz, qw]
[x, y, z]
[k1, k2, k3, a1, a2, a3]
<reference_id>
<width_px>x<height_px>
<width_mm>x<height_mm>
The repository contains an example file for all three of the files mentioned.
The repository contains an example of how files should be organized under /data.
Under /out, the repository contains the example point cloud output in .ply format.
