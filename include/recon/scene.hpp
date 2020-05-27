#pragma once
#ifndef __recon_scene_h__
#define __recon_scene_h__

#include "recon/defines.hpp"
#include "recon/camera.hpp"
#include "recon/semanticlabelmanager.hpp"
#include "recon/vertex.hpp"

#define TINYPLY_IMPLEMENTATION
#include "recon/fileutils.hpp"

namespace recon {
	class Scene {
	public:
		Scene() {};
		Scene(const Camera& color_camera, const Camera& depth_camera) : m_color_camera(color_camera), m_depth_camera(depth_camera) {};
		~Scene() {};

		void push_vertex(Vertex& vertex) { m_vertices.push_back(vertex); };
		void save_scene(const std::string&, const SemanticLabelManager& manager = SemanticLabelManager(), bool = false, bool = false);
		void flush_scene();

		inline Camera color_camera() { return m_color_camera; };
		inline Camera depth_camera() { return m_depth_camera; };
		void center_point_cloud();

	private:
		Camera m_color_camera;
		Camera m_depth_camera;
		std::vector<Vertex> m_vertices;
	};
}

#endif