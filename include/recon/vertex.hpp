#pragma once
#ifndef __recon_vertex_h__
#define __recon_vertex_h__

#include "recon/common.hpp"
#include "typedefines.hpp"
#include "recon/semanticlabel.hpp"

namespace recon {
	class Vertex {
	public:
		Vertex(const Point4& coord) : m_coord(coord), m_color(Color4(0, 0, 0, 0)), m_label(SemanticLabel()) {};
		Vertex(const Point4& coord, const Color4& color) : m_coord(coord), m_color(color), m_label(SemanticLabel()) {};
		Vertex(const Point4& coord, const Color4& color, const SemanticLabel& label) : m_coord(coord), m_color(color), m_label(label) {};

		inline Point4 coord() { return m_coord; };
		inline Color4 color() { return m_color; };
		inline SemanticLabel label() { return m_label; };

		inline void set_coord(const Point4& coord) { m_coord = coord; };
		inline void set_color(const Color4& color) { m_color = color; };
		inline void set_label(const SemanticLabel& label) { m_label = label; };

	private:
		Point4 m_coord;
		Color4 m_color;
		SemanticLabel m_label;
	};
}

#endif