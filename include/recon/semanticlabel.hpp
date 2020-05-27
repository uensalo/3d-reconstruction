#pragma once
#ifndef __recon_semanticlabel_h__
#define __recon_semanticlabel_h__

#include "recon/common.hpp"

namespace recon {
	struct SemanticLabel {
		SemanticLabel() {
			m_name = "no_label";
			m_index = 0;
		}

		bool operator==(const SemanticLabel& l) {
			return m_index == l.m_index;
		}

		std::string m_name;
		int m_index;
	};
}

#endif