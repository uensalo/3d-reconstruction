#pragma once
#ifndef __recon_pointcloud_h__
#define __recon_pointcloud_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/semanticlabel.hpp"
#include "recon/vertex.hpp"

namespace recon {
	class PointCloud {
	public:
		PointCloud() {};
		~PointCloud() {};
		PointCloud(const std::vector<Vertex>&);
		PointCloud(const PointCloud&);

		inline std::vector<Vertex> points() const { return m_points; };
		inline Matrix4 transform() const { return m_trafo; };

		void push_point();
		void apply_transform(const Matrix4&);

		PointCloud operator=(const PointCloud&);
	private:
		std::vector<Vertex> m_points;
		Matrix4 m_trafo;
		SemanticLabel m_label;
	};
}
#endif