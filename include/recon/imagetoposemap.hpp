#pragma once
#ifndef __recon_imagetoposemap_h__
#define __recon_imagetoposemap_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/imagecollection.hpp"
#include "recon/camerapose.hpp"

namespace recon {
	class ImageToPoseMap {
	public:
		ImageToPoseMap() {};

		void append_depth_pair(const Image& im, const CameraPose& p) { m_depth_poses.push_back(p), m_depth_images.push_back(im); };
		void append_color_pair(const Image& im, const CameraPose& p) { m_color_poses.push_back(p), m_color_images.push_back(im); };
		void append_semantic_image(const Image& im) { m_semantic_images.push_back(im); };

		
		inline size_t size() { return m_depth_images.size(); };
		inline Image get_depth_image(int i) { return m_depth_images[i]; };
		inline Image get_color_image(int i) { return m_color_images[i]; };
		inline Image get_semantic_image(int i) { return m_semantic_images[i]; };

		CameraPose get_depth_pose(int i) { return m_depth_poses[i]; };
		CameraPose get_color_pose(int i) { return m_color_poses[i]; };

	private:
		ImageCollection m_depth_images;
		ImageCollection m_color_images;
		ImageCollection m_semantic_images;

		std::vector<CameraPose> m_depth_poses;
		std::vector<CameraPose> m_color_poses;
	};
}
#endif
