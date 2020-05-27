#include "recon/imagecollection.hpp"

using namespace recon;
ImageCollection::ImageCollection(std::string dname, int flag) {
	m_flag = flag;
	if (flag == FLAG_COLOR || flag == FLAG_SEMANTIC) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < file_names.size(); i++) {
			m_images.push_back(fileutils::read_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images. [" << i << " / " << file_names.size() << "]" << std::endl;
#endif
		}
	} else if (flag == FLAG_DEPTH) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < file_names.size(); i++) {
			m_images.push_back(fileutils::read_depth_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if(i % 100 == 0) std::cout << "Reading images. [" << i << " / " << file_names.size() << "]" << std::endl;
#endif
		}
	}
};

ImageCollection::ImageCollection(std::string dname, int no_frames, int flag) {
	m_flag = flag;
	if (flag == FLAG_COLOR || flag == FLAG_SEMANTIC) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < std::min((int)file_names.size(), no_frames); i++) {
			m_images.push_back(fileutils::read_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images. [" << i << " / " << std::min((int)file_names.size(), no_frames) << "]" << std::endl;
#endif
		}
	}
	else if (flag == FLAG_DEPTH) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < std::min((int)file_names.size(), no_frames); i++) {
			m_images.push_back(fileutils::read_depth_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images. [" << i << " / " << std::min((int)file_names.size(), no_frames) << "]" << std::endl;
#endif
		}
	}
};

ImageCollection::ImageCollection(std::string dname, int sampling_rate, int no_frames, int flag) {
	m_flag = flag;
	if (flag == FLAG_COLOR || flag == FLAG_SEMANTIC) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < std::min((int)file_names.size(), no_frames); i += sampling_rate) {
			m_images.push_back(fileutils::read_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images with sampling rate " << sampling_rate << ". [" << i << " / " << std::min((int)file_names.size(), no_frames) << "]" << std::endl;
#endif
		}
	}
	else if (flag == FLAG_DEPTH) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = 0; i < std::min((int)file_names.size(), no_frames); i += sampling_rate) {
			m_images.push_back(fileutils::read_depth_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images with sampling rate " << sampling_rate << ". [" << i << " / " << std::min((int)file_names.size(), no_frames) << "]" << std::endl;
#endif
		}
	}
};

ImageCollection::ImageCollection(std::string dname, int start_idx, int end_idx, int sampling_rate, int flag) {
	m_flag = flag;
	if (flag == FLAG_COLOR || flag == FLAG_SEMANTIC) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = start_idx; i <= end_idx; i += sampling_rate) {
			m_images.push_back(fileutils::read_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images with sampling rate " << sampling_rate << ". [" << i << " / " << end_idx << "]" << std::endl;
#endif
		}
	}
	else if (flag == FLAG_DEPTH) {
		std::vector<std::string> file_names = fileutils::files_in_directory(dname);
		for (int i = start_idx; i <= end_idx; i += sampling_rate) {
			m_images.push_back(fileutils::read_depth_image(dname + std::to_string(i) + ".png"));
#ifdef RECON_PROGRESS_INDICATOR
			if (i % 100 == 0) std::cout << "Reading images with sampling rate " << sampling_rate << ". [" << i << " / " << end_idx << "]" << std::endl;
#endif
		}
	}
};

