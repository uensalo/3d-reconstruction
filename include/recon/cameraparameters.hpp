#pragma once
#ifndef __recon_camera_parameters_h__
#define __recon_camera_parameters_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"

namespace recon {
	/// Container struct for camera parameters
	struct CameraParameterRecord {
		//intrinsics
		double m_fx;
		double m_fy;
		double m_cx;
		double m_cy;
		double m_s;

		//rotation as quaternions
		double m_qx;
		double m_qy;
		double m_qz;
		double m_qw;

		//translation
		double m_x;
		double m_y;
		double m_z;
	};

	class CameraParameters {
	public:
		/// Warning: do not use this constructor to construct CameraParameter instances.
		CameraParameters() {};
		
		CameraParameters(double fx, double fy, double cx, double cy, double s, double qx, double qy, double qz, double qw, double x, double y, double z)
			: m_fx(fx), m_fy(fy), m_cx(cx), m_cy(cy), m_s(s), m_qx(qx), m_qy(qy), m_qz(qz), m_qw(qw), m_x(x), m_y(y), m_z(z) {};
		
		/** 
		 * Constructs a CameraParameters instance using the fields of the CameraParameterRecord
		 *
		 * Note that all the fields should of the camera parameter record must be present for the proper
		 * functioning of this class.
		 */
		CameraParameters(const CameraParameterRecord&);

		CameraParameters(const CameraParameters&);

		~CameraParameters();

		/// Returns the focal length of the camera on the x axis.
		inline double fx() const { return m_fx; };

		/// Returns the focal length of the camera on the y axis.
		inline double fy() const { return m_fy; };

		// Returns the offset of the origin of the camera on the x axis
		inline double cx() const { return m_cx; };

		// Returns the offset of the origin of the camera on the y axis
		inline double cy() const { return m_cy; };

		/// Returns the skew
		inline double s() const { return m_s; };

		/// Returns the quarternion rotation on axis qx
		inline double qx() const { return m_qx; };

		/// Returns the quarternion rotation on axis qy
		inline double qy() const { return m_qy; };

		/// Returns the quarternion rotation on axis qz
		inline double qz() const { return m_qz; };

		/// Returns the quarternion rotation on axis qw
		inline double qw() const { return m_qw; };

		/// Returns the translation on the x axis
		inline double x() const { return m_x; };

		/// Returns the translation on the y axis
		inline double y() const { return m_y; };

		/// Returns the translation on the z axis
		inline double z() const { return m_z; };

		/// Reassigns camera parameters to the parameters specified on the record
		void reassign_params(const CameraParameterRecord&);

		/// Returns the extrinsic rotation of the camera in Euler form
		inline Matrix3 rotation() { return m_rotation; };

		// Returns the translation of the camera in vector form
		inline Vector3 translation() { return m_translation; };

		// Returns the intrinsics of the camera as a 3x3 matrix
		inline Matrix3 intrinsics() { return m_intrinsics; };

		// Returns the rotation of the camera in a 4x4 homogeneous matrix
		inline Matrix4 rotation4() { return m_rotation4; };

		// Returns the translation of the camera in homogeneous coordinates
		inline Vector4 translation4() { return m_translation4; };

		// Returns the intrinsics of the camera as a 4x4 matrix
		inline Matrix4 intrinsics4() { return m_intrinsics4; };

		CameraParameters operator=(const CameraParameters&);

	private:
		//intrinsics
		double m_fx;
		double m_fy;
		double m_cx;
		double m_cy;
		double m_s;

		//rotation as quaternions
		double m_qx;
		double m_qy;
		double m_qz;
		double m_qw;

		//translation
		double m_x;
		double m_y;
		double m_z;

		//rotation matrix
		Matrix3 m_rotation;

		//rotation4
		Matrix4 m_rotation4;

		//translation
		Vector3 m_translation;

		//translation4
		Vector4 m_translation4;

		//intrinsics matrix
		Matrix3 m_intrinsics;

		//intrinsics4 matrix
		Matrix4 m_intrinsics4;
	};
}

#endif