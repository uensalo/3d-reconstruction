#pragma once
#ifndef __recon_camera_pose_h__
#define __recon_camera_pose_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"

namespace recon {
	class CameraPose {
	public:
		CameraPose() {};
		CameraPose(Matrix3 rotation, Vector3 translation)
			: m_rotation(rotation), m_translation(translation) {};
		CameraPose(const CameraPose& c) { m_rotation = c.m_rotation; m_translation = c.m_translation; };
		~CameraPose() {};

		inline Matrix3 rotation() { return m_rotation; };
		inline Vector3 translation() { return m_translation; };
		inline Matrix rototranslation() { Matrix m(3, 4); m << m_rotation, m_translation; return m; };

		void rotate(const Matrix3& rot) { m_rotation = rot * m_rotation; };
		void translate(const Vector3& trs) { m_translation += trs; };

		CameraPose operator=(const CameraPose& o) { m_rotation = o.m_rotation; m_translation = o.m_translation; return *this; };

	private:
		Matrix3 m_rotation;
		Vector3 m_translation;
	};
}

#endif