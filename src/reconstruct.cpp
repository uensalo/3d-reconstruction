#pragma once
#include "recon/reconstruct.hpp"
using namespace recon;

void Reconstructor::configure(const std::string& main_path, int sampling_rate, int no_frames) {
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Reading first " << no_frames << " frames at a sampling rate of " << sampling_rate << "." << std::endl;
#endif
	ImageCollection color_images(main_path + COLOR_IMAGE_SUBDIRECTORY, sampling_rate, no_frames, ImageCollection::FLAG_COLOR);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading color images." << std::endl << std::endl;
#endif
	ImageCollection depth_images(main_path + DEPTH_IMAGE_SUBDIRECTORY, sampling_rate, no_frames, ImageCollection::FLAG_DEPTH);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading depth images." << std::endl << std::endl;
#endif
	ImageCollection semantic_images(main_path + SEMANTIC_IMAGE_SUBDIRECTORY, sampling_rate, no_frames, ImageCollection::FLAG_SEMANTIC);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading semantic images." << std::endl << std::endl;
#endif

	Camera color_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "color.txt", 0);
	Camera depth_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "depth.txt", 0);

	m_semantic_manager = SemanticLabelManager(main_path + CAMERA_DATA_SUBDIRECTORY + SEMANTIC_LABEL_FILENAME);

	m_scene = Scene(color_camera, depth_camera);
	double to_mm = depth_camera.size_in_mm().x() / depth_camera.size_in_pixels().x();
	CameraPose cur_color_pose(color_camera.camera_parameters().rotation(), to_mm * color_camera.camera_parameters().translation());
	CameraPose cur_depth_pose(depth_camera.camera_parameters().rotation(), to_mm * depth_camera.camera_parameters().translation());
	m_image_map.append_color_pair(color_images[0], cur_color_pose);
	m_image_map.append_depth_pair(depth_images[0], cur_depth_pose);
	m_image_map.append_semantic_image(semantic_images[0]);
	for (int i = 1; i < color_images.size(); i++) {
		m_image_map.append_color_pair(color_images[i], cur_color_pose);
		m_image_map.append_depth_pair(depth_images[i], cur_depth_pose);
		m_image_map.append_semantic_image(semantic_images[i]);
	}
}

void Reconstructor::configure(const std::string& main_path, int start_idx, int end_idx, int sampling_rate) {
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Reading frames with start index " << start_idx << " and end index " << end_idx << " at a sampling rate of " << sampling_rate << "." << std::endl;
#endif
	ImageCollection color_images(main_path + COLOR_IMAGE_SUBDIRECTORY, start_idx, end_idx, sampling_rate, ImageCollection::FLAG_COLOR);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading color images." << std::endl << std::endl;
#endif
	ImageCollection depth_images(main_path + DEPTH_IMAGE_SUBDIRECTORY, start_idx, end_idx, sampling_rate, ImageCollection::FLAG_DEPTH);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading depth images." << std::endl << std::endl;
#endif
	ImageCollection semantic_images(main_path + SEMANTIC_IMAGE_SUBDIRECTORY, start_idx, end_idx, sampling_rate, ImageCollection::FLAG_SEMANTIC);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading semantic images." << std::endl << std::endl;
#endif
	Camera color_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "color.txt", 0);
	Camera depth_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "depth.txt", 0);

	m_semantic_manager = SemanticLabelManager(main_path + CAMERA_DATA_SUBDIRECTORY + SEMANTIC_LABEL_FILENAME);

	m_scene = Scene(color_camera, depth_camera);
	double to_mm = depth_camera.size_in_mm().x() / depth_camera.size_in_pixels().x();
	CameraPose cur_color_pose(color_camera.camera_parameters().rotation(), to_mm * color_camera.camera_parameters().translation());
	CameraPose cur_depth_pose(depth_camera.camera_parameters().rotation(), to_mm * depth_camera.camera_parameters().translation());
	m_image_map.append_color_pair(color_images[0], cur_color_pose);
	m_image_map.append_depth_pair(depth_images[0], cur_depth_pose);
	m_image_map.append_semantic_image(semantic_images[0]);
	for (int i = 1; i < color_images.size(); i++) {
		m_image_map.append_color_pair(color_images[i], cur_color_pose);
		m_image_map.append_depth_pair(depth_images[i], cur_depth_pose);
		m_image_map.append_semantic_image(semantic_images[i]);
	}
}
void Reconstructor::configure(const std::string& main_path, int idx) {
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Reading a single frame with image index " << idx << "." << std::endl;
#endif
	ImageCollection color_images(main_path + COLOR_IMAGE_SUBDIRECTORY, idx, idx, 1, ImageCollection::FLAG_COLOR);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading color images." << std::endl << std::endl;
#endif
	ImageCollection depth_images(main_path + DEPTH_IMAGE_SUBDIRECTORY, idx, idx, 1, ImageCollection::FLAG_DEPTH);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading depth images." << std::endl << std::endl;
#endif
	ImageCollection semantic_images(main_path + SEMANTIC_IMAGE_SUBDIRECTORY, idx, idx, 1, ImageCollection::FLAG_SEMANTIC);
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Done reading semantic images." << std::endl << std::endl;
#endif
	Camera color_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "color.txt", 0);
	Camera depth_camera(main_path + CAMERA_DATA_SUBDIRECTORY + "depth.txt", 0);

	m_semantic_manager = SemanticLabelManager(main_path + CAMERA_DATA_SUBDIRECTORY + SEMANTIC_LABEL_FILENAME);

	m_scene = Scene(color_camera, depth_camera);
	double to_mm = depth_camera.size_in_mm().x() / depth_camera.size_in_pixels().x();
	CameraPose cur_color_pose(color_camera.camera_parameters().rotation(), to_mm * color_camera.camera_parameters().translation());
	CameraPose cur_depth_pose(depth_camera.camera_parameters().rotation(), to_mm * depth_camera.camera_parameters().translation());
	m_image_map.append_color_pair(color_images[0], cur_color_pose);
	m_image_map.append_depth_pair(depth_images[0], cur_depth_pose);
	m_image_map.append_semantic_image(semantic_images[0]);
	for (int i = 1; i < color_images.size(); i++) {
		m_image_map.append_color_pair(color_images[i], cur_color_pose);
		m_image_map.append_depth_pair(depth_images[i], cur_depth_pose);
		m_image_map.append_semantic_image(semantic_images[i]);
	}
}

void Reconstructor::get_feature_match_indices(const Image& d_i1, const Image& d_i2, std::vector<Coord2>& idx1, std::vector<Coord2>& idx2) {
	idx1 = std::vector<Coord2>();
	idx2 = std::vector<Coord2>();

	Image img1 = d_i1;
	img1.convertTo(img1, CV_8U, 0.00390625);

	Image img2 = d_i2;
	img2.convertTo(img2, CV_8U, 0.00390625);

	cv::Mat descriptors1, descriptors2;
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Ptr<cv::Feature2D> orb = cv::ORB::create(500);
	orb->detect(img1, keypoints1);
	orb->compute(img1, keypoints1, descriptors1);

	orb->detect(img2, keypoints2);
	orb->compute(img2, keypoints2, descriptors2);

	std::vector<cv::DMatch> matches;
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_L2, false);
	matcher->match(descriptors1, descriptors2, matches);

	//filter out most outliers
	for (int i = 0; i < matches.size(); i++) {
		cv::DMatch match = matches[i];
		int img1_idx = match.queryIdx;
		int img2_idx = match.trainIdx;
		cv::Point2f img1pt = keypoints1[img1_idx].pt;
		cv::Point2f img2pt = keypoints2[img2_idx].pt;

		if (std::abs(img2pt.y - img1pt.y) + std::abs(img2pt.x - img1pt.x) < 15) {
			Coord2 img1_idxi((int)img1pt.x, (int)img1pt.y);
			Coord2 img2_idxi((int)img2pt.x, (int)img2pt.y);
			idx1.push_back(img1_idxi);
			idx2.push_back(img2_idxi);
		}
	}
}

Matrix4 Reconstructor::estimate_camera_pose(int i, int j) {

	Image img1 = m_image_map.get_color_image(i);
	cv::cvtColor(img1, img1, cv::COLOR_BGR2GRAY);

	Image img2 = m_image_map.get_color_image(j);
	cv::cvtColor(img2, img2, cv::COLOR_BGR2GRAY);

	cv::Mat descriptors1, descriptors2;
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Ptr<cv::Feature2D> orb = cv::ORB::create(500);
	orb->detect(img1, keypoints1);
	orb->compute(img1, keypoints1, descriptors1);

	orb->detect(img2, keypoints2);
	orb->compute(img2, keypoints2, descriptors2);

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_L2, false);
	std::vector<cv::DMatch> matches;
	matcher->match(descriptors1, descriptors2, matches);

	std::vector<cv::Point2f> pts1;
	std::vector<cv::Point2f> pts2;
	//filter out most outliers
	for (int i = 0; i < matches.size(); i++) {
		cv::DMatch match = matches[i];
		int img1_idx = match.queryIdx;
		int img2_idx = match.trainIdx;
		cv::Point2f img1pt = keypoints1[img1_idx].pt;
		cv::Point2f img2pt = keypoints2[img2_idx].pt;
		pts1.push_back(img1pt);
		pts2.push_back(img2pt);
	}

	Matrix3 k = m_scene.color_camera().normalized_camera_parameters().intrinsics();
	cv::Mat intrinsic_params(3,3,CV_64F);

	intrinsic_params.at<double>(0, 0) = k(0, 0);
	intrinsic_params.at<double>(0, 1) = k(0, 1);
	intrinsic_params.at<double>(0, 2) = k(0, 2);

	intrinsic_params.at<double>(1, 0) = k(1, 0);
	intrinsic_params.at<double>(1, 1) = k(1, 1);
	intrinsic_params.at<double>(1, 2) = k(1, 2);

	intrinsic_params.at<double>(2, 0) = k(2, 0);
	intrinsic_params.at<double>(2, 1) = k(2, 1);
	intrinsic_params.at<double>(2, 2) = k(2, 2);

	cv::Mat E = cv::findEssentialMat(pts1, pts2, intrinsic_params, cv::RANSAC, 0.999, 1.0, cv::noArray());
	
	cv::Mat R, t;
	cv::recoverPose(E, pts1, pts2, intrinsic_params, R, t, cv::noArray());
	
	Matrix4 trafo = Matrix4::Zero();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			trafo(i, j) = R.at<double>(i, j);
		}
	}
	trafo(0, 3) = t.at<double>(0, 0);
	trafo(1, 3) = t.at<double>(1, 0);
	trafo(2, 3) = t.at<double>(2, 0);
	trafo(3, 3) = 1;

	return trafo;
}

std::vector<Point4> Reconstructor::project_depth_at_indices(const Image& depth_image, const Matrix3& depth_intrinsics,
	const double& depth_mm_per_pixel, const std::vector<Coord2>& indices) {
	Matrix3 k_inv = depth_intrinsics.inverse();
	std::vector<Vector4> vertices;
	for (Coord2 idx : indices) {
		double z = (depth_image.at<unsigned short>(idx.x(), idx.y()) >> 3);
		Point3 coord = k_inv * z * Point3(idx.y() * depth_mm_per_pixel, idx.x() * depth_mm_per_pixel, 1);
		Point4 hom_coord(coord.x(), coord.y(), coord.z(), 1);
		vertices.push_back(hom_coord);
	}
	return vertices;
}



Matrix4 Reconstructor::estimate_transform_between_points(const std::vector<Point4>& p1, const std::vector<Point4>& p2) {
	Matrix4 trafo;
	size_t n = p1.size();
	std::vector<double> weights;
	Matrix A(4 * n, 16);
	Vector b(4 * n);
	for (int k = 0; k < n; k++) {
		Point4 mk = p1[k];
		Matrix Mk = Matrix::Zero(4, 16);

		Mk.block<1, 4>(0, 0) = mk;
		Mk.block<1, 4>(1, 4) = mk;
		Mk.block<1, 4>(2, 8) = mk;
		Mk.block<1, 4>(3, 12) = mk;

		A.block<4, 16>(4 * k, 0) = Mk;
		b.segment<4>(4 * k) = p2[k];
	}
	Vector x = (A.transpose() * A).inverse() * A.transpose() * b;
	trafo.block<1, 4>(0, 0) = x.segment<4>(0);
	trafo.block<1, 4>(1, 0) = x.segment<4>(4);
	trafo.block<1, 4>(2, 0) = x.segment<4>(8);
	trafo.block<1, 4>(3, 0) = x.segment<4>(12);
	return trafo;
}

std::vector<Vertex> Reconstructor::project_depth_image(const Image& depth_image, const Image& color_image, const Image& label_image,
	                                    const Camera& depth_camera, const Camera& color_camera, const Matrix4& trafo) {

	if(color_image.empty() && !label_image.empty()) {
		return project_depth_image(depth_image, label_image, label_image, depth_camera, color_camera, trafo);
	}

	Matrix3 k_inv = depth_camera.normalized_camera_parameters().intrinsics().inverse();

	CameraParameters depth_cam_params = depth_camera.normalized_camera_parameters();
	CameraParameters color_cam_params = color_camera.normalized_camera_parameters();

	Size2d depth_camara_res = depth_camera.size_in_mm();
	Size2d color_camera_res = color_camera.size_in_mm();

	Size2i depth_camera_pixel_res = depth_camera.size_in_pixels();
	Size2i color_camera_pixel_res = color_camera.size_in_pixels();

	double depth_camera_mm_per_pixel = depth_camera.mm_per_pixel();
	double color_camera_mm_per_pixel = color_camera.mm_per_pixel();

	std::vector<Vertex> vertices;

	for (int i = 0; i < depth_image.rows; i++) {
		for (int j = 0; j < depth_image.cols; j++) {
			//convert kinect format depth to actual millimeters
			double z = (depth_image.at<unsigned short>(i, j) >> 3);

			//project points to 3D space
			Point3 coord = k_inv * z * Point3(j * depth_camera_mm_per_pixel, i * depth_camera_mm_per_pixel, 1);
			coord = depth_cam_params.rotation().transpose() * (coord - depth_cam_params.translation());

			//convert to 3D homogeneous coordinate
			Point4 hom_coord(coord.x(), coord.y(), coord.z(), 1);

			if (!color_image.empty()) {
				//compute color texture tap coordinate
				Point3 color_img_coord_hom = color_cam_params.intrinsics() * color_cam_params.rotation() * coord + color_cam_params.translation();
				Point2 color_img_coord(color_img_coord_hom.x() / color_img_coord_hom.z() / color_camera_res.x(), color_img_coord_hom.y() / color_img_coord_hom.z() / color_camera_res.y());

				//check if coordinates fall inside the camera (i.e. vertex is visible)
				if (color_img_coord.x() >= 0 && color_img_coord.x() <= 1 && color_img_coord.y() >= 0 && color_img_coord.y() <= 1) {
					Color4 color;
					int access_row = (int)(color_img_coord.y() * color_image.rows);
					int access_col = (int)(color_img_coord.x() * color_image.cols);
					const unsigned char* p = color_image.ptr(access_row, access_col);
					color = Color4(p[2] / 255.0, p[0] / 255.0, p[1] / 255.0, 0);

					//find semantic label associated with this vertex
					if (!label_image.empty()) {
						const unsigned char* s = label_image.ptr(access_row, access_col);
						std::string color_str = std::to_string(s[0]) + std::to_string(s[1]) + std::to_string(s[2]);
						SemanticLabel label = m_semantic_manager.get_label(color_str);

						//create and push the vertex to the return value
						Vertex vertex(trafo * hom_coord, color, label);
						vertices.push_back(vertex);
					}
					else {
						// no semantic labelling was requested
						Vertex vertex(trafo * hom_coord, color);
						vertices.push_back(vertex);
					}
				}
			}
			else {
				// no coloring was requested
				Vertex vertex(trafo * hom_coord);
				vertices.push_back(vertex);
			}
		}
	}
	return vertices;
}

void Reconstructor::project_frame(int f, bool use_color, bool use_semantic, const Matrix4& trafo) {
	
	Camera depth_camera = m_scene.depth_camera();
	Image depth_image = m_image_map.get_depth_image(f);

	Image color_image;
	Camera color_camera = m_scene.depth_camera(); // could be anything tbh...
	if (use_color) {
		color_image = m_image_map.get_color_image(f);
		color_camera = m_scene.color_camera();
	}

	Image label_image;
	if (use_semantic) {
		label_image = m_image_map.get_semantic_image(f);
	}

	std::vector<Vertex> vertices = project_depth_image(depth_image, color_image, label_image, depth_camera, color_camera, trafo);
	for (Vertex v : vertices) {
		m_scene.push_vertex(v);
	}
}

void Reconstructor::save_scene(const std::string& filename, bool center, bool semantic_instancing) {
	if (!semantic_instancing) {
		if (center) {
#ifdef RECON_PROGRESS_INDICATOR
			std::cout << "Saving a centered point cloud with name " << filename << ".ply" << "." << std::endl;
#endif
			m_scene.center_point_cloud();
		}
#ifdef RECON_PROGRESS_INDICATOR
		std::cout << "Saving a not-centered point cloud with name " << filename << ".ply" << "." << std::endl;
#endif
		m_scene.save_scene(filename);
	}
	else {
#ifdef RECON_PROGRESS_INDICATOR
		std::cout << "Saving semantic point clouds under the prefix " << filename << "." << std::endl;
#endif
		m_scene.save_scene(filename, m_semantic_manager, center, true);
	}
}

void Reconstructor::flush_scene() {
	m_scene.flush_scene();
}