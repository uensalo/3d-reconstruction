#include "recon/cameraparameters.hpp"

using namespace recon;

recon::CameraParameters::CameraParameters(const CameraParameterRecord& o) {
	m_fx = o.m_fx;
	m_fy = o.m_fy;
	m_cx = o.m_cx;
	m_cy = o.m_cy;
	m_s = o.m_s;

	m_qx = o.m_qx;
	m_qy = o.m_qy;
	m_qz = o.m_qz;
	m_qw = o.m_qw;

	m_x = o.m_x;
	m_y = o.m_y;
	m_z = o.m_z;

	m_intrinsics << m_fx, m_s, m_cx, 0, m_fy, m_cy, 0, 0, 1;

	m_rotation << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw),
				  2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw),
				  2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy);

	m_translation = Vector3(m_x, m_y, m_z);

	m_intrinsics4 << m_fx, m_s, m_cx, 0, 0, m_fy, m_cy, 0, 0, 0, 1, 0, 0, 0, 0, 1;

	m_rotation4 << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw), 0,
		2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw), 0,
		2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy), 0,
		0, 0, 0, 1;

	m_translation4 = Vector4(m_x, m_y, m_z, 0);

}

recon::CameraParameters::CameraParameters(const CameraParameters& o) {
	m_fx = o.m_fx;
	m_fy = o.m_fy;
	m_cx = o.m_cx;
	m_cy = o.m_cy;
	m_s = o.m_s;

	m_qx = o.m_qx;
	m_qy = o.m_qy;
	m_qz = o.m_qz;
	m_qw = o.m_qw;

	m_x = o.m_x;
	m_y = o.m_y;
	m_z = o.m_z;

	m_rotation = o.m_rotation;
	m_translation = o.m_translation;
	m_intrinsics = o.m_intrinsics;

	m_rotation4 = o.m_rotation4;
	m_translation4 = o.m_translation4;
	m_intrinsics4 = o.m_intrinsics4;

}

recon::CameraParameters::~CameraParameters() {
}

void recon::CameraParameters::reassign_params(const CameraParameterRecord& o) {
	m_fx = o.m_fx;
	m_fy = o.m_fy;
	m_cx = o.m_cx;
	m_cy = o.m_cy;
	m_s = o.m_s;

	m_qx = o.m_qx;
	m_qy = o.m_qy;
	m_qz = o.m_qz;
	m_qw = o.m_qw;

	m_x = o.m_x;
	m_y = o.m_y;
	m_z = o.m_z;

	m_intrinsics << m_fx, m_s, m_cx, 0, m_fy, m_cy, 0, 0, 1;

	m_rotation << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw),
		2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw),
		2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy);

	m_translation = Vector3(m_x, m_y, m_z);

	m_intrinsics4 << m_fx, m_s, m_cx, 0, 0, m_fy, m_cy, 0, 0, 0, 1, 0, 0, 0, 0, 1;

	m_rotation4 << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw), 0,
		2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw), 0,
		2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy), 0,
		0, 0, 0, 1;

	m_translation4 = Vector4(m_x, m_y, m_z, 0);
}

CameraParameters recon::CameraParameters::operator=(const CameraParameters& o)
{
	m_fx = o.m_fx;
	m_fy = o.m_fy;
	m_cx = o.m_cx;
	m_cy = o.m_cy;
	m_s = o.m_s;

	m_qx = o.m_qx;
	m_qy = o.m_qy;
	m_qz = o.m_qz;
	m_qw = o.m_qw;

	m_x = o.m_x;
	m_y = o.m_y;
	m_z = o.m_z;

	m_intrinsics << m_fx, m_s, m_cx, 0, m_fy, m_cy, 0, 0, 1;

	m_rotation << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw),
		2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw),
		2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy);

	m_translation = Vector3(m_x, m_y, m_z);

	m_intrinsics4 << m_fx, m_s, m_cx, 0, 0, m_fy, m_cy, 0, 0, 0, 1, 0, 0, 0, 0, 1;

	m_rotation4 << 1 - 2 * (m_qy * m_qy - m_qz * m_qz), 2 * (m_qx * m_qy - m_qz * m_qw), 2 * (m_qx * m_qz + m_qy * m_qw), 0,
		2 * (m_qx * m_qy + m_qz * m_qw), 1 - 2 * (m_qx * m_qx + m_qz * m_qz), 2 * (m_qy * m_qz - m_qx * m_qw), 0,
		2 * (m_qx * m_qz - m_qy * m_qw), 2 * (m_qy * m_qz + m_qx * m_qw), 1 - 2 * (m_qx * m_qx + m_qy * m_qy), 0,
		0, 0, 0, 1;

	m_translation4 = Vector4(m_x, m_y, m_z, 0);

	return *this;
}
