#include "recon/pointcloud.hpp"

using namespace recon;

PointCloud::PointCloud(const std::vector<Vertex>& verts) {
	for (Vertex v : verts) {
		m_points.push_back(v);
	}
	m_trafo << 1, 0, 0, 0, 
		0, 1, 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1;
	m_label = SemanticLabel();
}

PointCloud::PointCloud(const PointCloud& pc) {
	for (Vertex v : pc.m_points) {
		m_points.push_back(v);
	}
	m_trafo = pc.m_trafo;
	m_label = pc.m_label;
}

PointCloud PointCloud::operator=(const PointCloud& pc) {
	m_points = std::vector<Vertex>();
	for (Vertex v : pc.m_points) {
		m_points.push_back(v);
	}
	m_trafo = pc.m_trafo;
	m_label = pc.m_label;
	return *this;
}