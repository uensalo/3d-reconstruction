#pragma once
#include "recon/scene.hpp"

using namespace recon;

void Scene::save_scene(const std::string &filename, const SemanticLabelManager& manager, bool center_instance, bool semantic_instancing) {
	if (!semantic_instancing) {
		fileutils::write_to_ply(m_vertices, filename);
	}
	else {
		std::vector<std::vector<Vertex>> instances;
		for (size_t i = 0; i < manager.no_classes(); i++) {
			instances.push_back(std::vector<Vertex>());
		}
		for (Vertex v : m_vertices) {
			instances[v.label().m_index].push_back(v);
		}

		int idx = 0;
		for (std::vector<Vertex> instance : instances) {
			if (instance.size() == 0) { idx++;  continue; };
			if (center_instance) {
				Vector4 avg(0, 0, 0, 0);
				for (Vertex v : instance) {
					avg.x() += v.coord().x();
					avg.y() += v.coord().y();
					avg.z() += v.coord().z();
				}
				avg = avg / instance.size();
				for (int i = 0; i < instance.size(); i++) {
					instance[i].set_coord(instance[i].coord() - avg);
				}
			}
			fileutils::write_to_ply(instance, filename + "_" + manager.get_label(idx).m_name);
			idx++;
		}
	}
#ifdef RECON_PROGRESS_INDICATOR
	std::cout << "Point cloud saved under the prefix " << filename  << "." << std::endl;
#endif
}

void Scene::center_point_cloud() {
	Vector4 avg(0,0,0,0);
	for (Vertex v : m_vertices) {
		avg.x() += v.coord().x();
		avg.y() += v.coord().y();
		avg.z() += v.coord().z();
	}
	avg = avg / m_vertices.size();
	for (int i = 0; i < m_vertices.size(); i++) {
		m_vertices[i].set_coord(m_vertices[i].coord() - avg);
	}
}

void Scene::flush_scene() {
	m_vertices = std::vector<Vertex>();
}