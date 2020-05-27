#pragma once
#ifndef __recon_reconstruct_h__
#define __recon_reconstruct_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/camera.hpp"
#include "recon/imagetoposemap.hpp"
#include "recon/scene.hpp"
#include "recon/matchgraph.hpp"
#include "recon/semanticlabelmanager.hpp"
#include "recon/vertex.hpp"

namespace recon {

	class Reconstructor {
	public:
		/**
		 * Warning: Do not forget to configure the Reconstructor before using it...
		 */
		Reconstructor() {};

		~Reconstructor() {};

		/**
		 * Returns the depth camera associated with the Scene object of the Reconstructor
		 */
		inline Camera depth_camera() { return m_scene.depth_camera(); };

		/**
		 * Returns the color camera associated with the Scene object of the Reconstructor
		 */
		inline Camera color_camera() { return m_scene.color_camera(); };

		/**
		 * Returns the ImageToPoseMap instance of the Reconstructor
		 */
		inline ImageToPoseMap pose_map() { return m_image_map; };

		/**
		 * Returns the number of frames associated with the Reconstructor
		 */
		inline size_t no_frames() { return m_image_map.size(); };

		/**
		 * Returns the SemanticLabelManager of the Reconstructor
		 */
		inline SemanticLabelManager label_manager() { return label_manager(); };

		/**
		 * Read a single image at a specified index
		 */
		void configure(const std::string& directory_name, int idx);

		/**
		 * Read images starting from 0 until index no_frames - 1, with the specified sampling rate
		 */
		void configure(const std::string& directory_name, int sampling_rate, int no_frames);

		/**
		 * Read images starting and ending at specific indices, with the specified sampling rate
		 */
		void configure(const std::string& directory_name, int start_idx, int end_idx, int sampling_rate);

		/**
		 * Computes the features and returns the matched indices of two images. The indices of the matched features
		 * for the first image are returned in the first vector, and the indices for the second image are returned in
		 * the second vector through the parameter list.
		 */
		void get_feature_match_indices(const Image& i1, const Image& i2, std::vector<Coord2>& idx1, std::vector<Coord2>& idx2);


		/**
		 * Projects a depth image to 3D coordinates. It is possible to specify a color image and a semantic label image
		 * for the semantic labelling and the coloring of the vertices returned by the projection. It is possible to provide
		 * empty images for color_image and label_image. However, if an empty image is provided to color_image but not to
		 * a label_image, the function will assign label colors as the color of vertices.
		 */
		std::vector<Vertex> project_depth_image(const Image& depth_image, const Image& color_image, const Image& label_image,
												const Camera& depth_camera, const Camera& color_camera, 
												const Matrix4& trafo = Matrix4::Identity());

		/**
		 * Projects a depth map only at the specified indices.
		 */
		std::vector<Vector4> project_depth_at_indices(const Image& depth, const Matrix3& intrinsics, const double&
			conversion_factor, const std::vector<Coord2>& indices);

		/**
		 * Estimates an affine transform between two geometric point clouds. Can be used to perform point cloud
		 * stitching.
		 */
		Matrix4 estimate_transform_between_points(const std::vector<Point4>& p1, const std::vector<Point4>& p2);

		/**
		 * Estimates the relative transform between the camera poses of two frames by estimating the essential matrix
		 * of frames i and j stored by the ImageToPoseMap object of the Reconstructor.
		 */
		Matrix4 estimate_camera_pose(int frame_i, int frame_j);

		/**
		 * Projects a frame specified at an index of a frame present in the ImageToPoseMap of the Reconstructor. It is possible
		 * to specify whether the Reconstructor should be using color and semantic information on top of depth maps, and a transform
		 * the points will be multiplied by after the projection to world coordinates. Only the last parameter is optional, and no
		 * transformation is used. If color is not requested and semantic labels are requested, then the color provided to vertices
		 * will be the colors in the label image.
		 *
		 * TODO: Swap the booleans with a 1 byte flag bitmap
		 */
		void project_frame(int frame_no, bool use_color, bool use_semantic_labels, const Matrix4& trafo = Matrix4::Identity());

		/**
		 * Saves the Scene object as a .ply file to the current working directory with a specified filename. Setting center to
		 * true centers the mesh around its centroid, and setting semantic_instancing to true attempts to divide the Scene into 
		 * semantic point clouds. Note that use_semantic_labels must be set to true if semantic instancing is desired.
		 */
		void save_scene(const std::string& filename, bool center, bool semantic_instancing);

		/**
		 * Deletes all vertices in the Scene object of the Reconstructor
		 */
		void flush_scene();									

	private:
		ImageToPoseMap m_image_map;
		MatchGraph m_match_graph;
		Scene m_scene;
		SemanticLabelManager m_semantic_manager;
	};
}
#endif