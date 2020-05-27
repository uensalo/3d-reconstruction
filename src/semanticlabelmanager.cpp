#pragma once
#include "recon/semanticlabelmanager.hpp"

using namespace recon;

SemanticLabelManager:: SemanticLabelManager(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		std::getline(file, line); // first line is schema, skip this
		int idx = 1;
		m_index_to_label_map.push_back(SemanticLabel());
		while (std::getline(file, line)) {
			SemanticLabel label;
			std::stringstream ss(line);
			std::string tmp;
			std::getline(ss, tmp, ',');
			std::string r = tmp;
			std::getline(ss, tmp, ',');
			std::string g = tmp;
			std::getline(ss, tmp, ',');
			std::string b = tmp;
			std::getline(ss, tmp, ';');
			label.m_name = tmp;
			label.m_index = idx++;
			std::string color_str = b + g + r;
			m_color_to_label_map.insert(std::pair<std::string, SemanticLabel>(color_str, label));
			m_index_to_label_map.push_back(label);
		}
		
	}
}

SemanticLabel SemanticLabelManager::get_label(const std::string& color_str) const {
	return m_color_to_label_map.find(color_str)->second;
}
