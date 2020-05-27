#pragma once
#ifndef __recon_semanticmanager_h__
#define	__recon_semanticmanager_h__

#include "recon/common.hpp"
#include "recon/semanticlabel.hpp"

namespace recon {
	class SemanticLabelManager {
	public:
		SemanticLabelManager() {};
		SemanticLabelManager(const std::string&);
		SemanticLabel get_label(const std::string& color_str) const;
		inline SemanticLabel get_label(int i) const { return m_index_to_label_map[i]; };
		inline size_t no_classes() const { return m_index_to_label_map.size(); };
	private:
		std::map<std::string, SemanticLabel> m_color_to_label_map;
		std::vector<SemanticLabel> m_index_to_label_map;
	};
}

#endif 
