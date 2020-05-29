#pragma once
#ifndef __recon_fileutils_h__
#define __recon_fileutils_h__
#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "tinyply/tinyply.hpp"

namespace recon::fileutils {
	static std::string read_file(const std::string& path) {
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return contents;
		}
		throw(errno);
	}

	static std::vector<std::string> files_in_directory(const std::string& directory) {
		std::vector<std::string> files;
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (entry.is_regular_file()) {
				files.push_back(entry.path().string());
			}
		}
		return files;
	}

	static std::vector<std::string> subdirectories_in_directory(const std::string& directory) {
		std::vector<std::string> directories;
		for (const auto& entry : std::filesystem::directory_iterator(directory)) {
			if (entry.is_directory()) {
				directories.push_back(entry.path().string());
			}
		}
		return directories;
	}

	static Image read_image(const std::string& image_path) {
		return cv::imread(image_path, cv::IMREAD_COLOR);
	}

	static Image read_depth_image(const std::string& image_path) {
		Image im = cv::imread(image_path, cv::IMREAD_UNCHANGED);
		Image cn[4];
		cv::split(im, cn); // cn[2] and cn[3] are irrelevant

		Image ret(im.rows, im.cols, CV_16UC1);
		for (int i = 0; i < im.rows; i++) {
			for (int j = 0; j < im.cols; j++) {
				unsigned short v1 = *cn[0].ptr(i, j);
				unsigned short v2 = *cn[1].ptr(i, j);
				ret.at<unsigned short>(i, j) = v1 << 8 | v2;
			}
		}
		return ret;
	}

#ifdef TINYPLY_IMPLEMENTATION
	static void write_to_ply(const std::vector<Vertex>& verts, const std::string& filename) {
		tinyply::PlyFile file;

		struct double3 { double x, y, z; };
		struct uchar3 { unsigned char r, g, b; };

		std::filebuf fb_binary;
		fb_binary.open(filename + ".ply", std::ios::out | std::ios::binary);
		std::ostream outstream(&fb_binary);
		if (outstream.fail()) {
			throw std::runtime_error("Failed to create .ply file.");
		}

		std::vector<double3> coords;
		std::vector<uchar3> colors;

		for (Vertex v : verts) {
			double3 coord;
			coord.x = v.coord().x() / v.coord().w();
			coord.y = v.coord().y() / v.coord().w();
			coord.z = v.coord().z() / v.coord().w();

			uchar3 color;
			color.r = (unsigned char)(v.color()[0] * 255);
			color.g = (unsigned char)(v.color()[1] * 255);
			color.b = (unsigned char)(v.color()[2] * 255);

			coords.push_back(coord);
			colors.push_back(color);
		}

		file.add_properties_to_element("vertex", { "x", "y", "z" },
			tinyply::Type::FLOAT64, coords.size(), reinterpret_cast<uint8_t*>(coords.data()), tinyply::Type::INVALID, 0);

		file.add_properties_to_element("vertex", { "red", "blue", "green" },
			tinyply::Type::UINT8, colors.size(), reinterpret_cast<uint8_t*>(colors.data()), tinyply::Type::INVALID, 0);

		file.write(outstream, true);
	}
#endif
}
#endif