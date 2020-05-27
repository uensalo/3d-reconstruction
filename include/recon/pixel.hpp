#pragma once
#ifndef __recon_pixel_h__
#define __recon_pixel_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"

namespace recon {
	class Pixel {
	public:
		Pixel(const Coord2& coords, const Color4& color) : m_coord(coords), m_color(color), m_depth(-1) {};
		Pixel(const Coord2& coords, const Color4& color, double depth) : m_coord(coords), m_color(color), m_depth(depth) {};

		inline Coord2 coord() { return m_coord; };
		inline Color4 color() { return m_color; };
		inline double depth() { return m_depth; };

		inline void set_coord(const Coord2& coord) { m_coord = coord; };
		inline void set_color(const Color4& color) { m_color = color; };
		inline void set_depth(const double& depth) { m_depth = depth; };

		inline bool has_depth() { return m_depth > 0; };

	private:
		Coord2 m_coord;
		Color4 m_color;
		double m_depth;
	};
}

#endif