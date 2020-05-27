#pragma once
#ifndef __recon_matchgraph_h__
#define __recon_matchgraph_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/imagecollection.hpp"

namespace recon {
	class MatchGraph {
	public:
		MatchGraph() { m_adj_mat = Matrix(8, 8); m_no_images = 8; };
		MatchGraph(int no_images) { m_adj_mat = Matrix(no_images, no_images); m_no_images = no_images; };
		MatchGraph(const MatchGraph& g) { m_adj_mat = g.m_adj_mat; m_no_images = g.m_no_images; }
		~MatchGraph() {};
		void add_edge(int i, int j, double weight) { m_adj_mat(i, j) = weight; m_adj_mat(j, i) = weight; };
		double weight(int i, int j) { return m_adj_mat(i, j); };
	private:
		Matrix4 m_adj_mat;
		int m_no_images;
	};
}
#endif
