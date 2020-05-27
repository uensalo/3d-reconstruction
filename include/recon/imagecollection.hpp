#pragma once
#ifndef __recon_imagecollection_h__
#define __recon_imagecollection_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/fileutils.hpp"

namespace recon {
	class ImageCollection {
	public:
		ImageCollection() { m_flag = -1; };
		ImageCollection(std::string fname, int flag);
		ImageCollection(std::string fname, int no_frames, int flag);
		ImageCollection(std::string fname, int sampling_rate, int no_frames, int flag);
		ImageCollection(std::string fname, int start_idx, int end_idx, int sampling_rate, int flag);
		ImageCollection(const ImageCollection& c) { m_images = c.m_images; m_flag = c.m_flag; };
		~ImageCollection() {};

		size_t size() { return m_images.size(); };

		bool is_color() { return m_flag == FLAG_COLOR; };
		bool is_depth() { return m_flag == FLAG_DEPTH; };

		void push_back(const Image& img) { m_images.push_back(img); };
		Image operator[](int i) { return m_images[i]; };
		ImageCollection operator=(const ImageCollection& c) { m_images = c.m_images; return *this; };
		ImageCollection operator+(const Image& im) { ImageCollection c; c.m_images = m_images; c.m_images.push_back(im); return c; };
		ImageCollection operator+=(const Image& im) { m_images.push_back(im); };
		ImageCollection operator+(const ImageCollection& c) { ImageCollection r; r.m_images = m_images; for (Image im : c.m_images) { r.m_images.push_back(im); } return r; };
		ImageCollection operator+=(const ImageCollection& c) { for (Image im : c.m_images) { m_images.push_back(im); } return *this; };

		static const int FLAG_COLOR = 0;
		static const int FLAG_DEPTH = 1;
		static const int FLAG_SEMANTIC = 2;
	private:
		std::vector<Image> m_images;
		int m_flag;
	};
}
#endif
#pragma once
