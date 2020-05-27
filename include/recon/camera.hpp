#pragma once
#ifndef __recon_camera_h__
#define __recon_camera_h__

#include "recon/common.hpp"
#include "recon/typedefines.hpp"
#include "recon/cameraparameters.hpp"
#include "recon/camerapose.hpp"

namespace recon {
	class Camera {
	public:
		/* 
		 * Warning: do not use this constructor to construct Camera instances.
		 */
		Camera() {};
		Camera(unsigned int id, Size2i size_in_pixels, Size2d size_in_mm, CameraParameters params, unsigned int ref = 0, Point3 distortion = Point3(0, 0, 0)) : 
		m_id(id), m_pixel_size(size_in_pixels), m_sensor_size(size_in_mm), m_params(params), m_ref(ref), m_distortion(distortion) {
			m_pose = CameraPose(params.rotation(), params.translation());
			m_projection = params.intrinsics() * m_pose.rototranslation();
		}

		/**
		 * Constructs a Camera instance by reading camera parameters from a file
		 *
		 * The camera file containing the information should be formatted as follows:
		 * First Line: Schema.
		 * Second Line: Internal Camera Parameters: [fx fy cx cy s]
		 * Third Line: Camera Rotation Quaternions: [qx qy qz qw]
		 * Fourth Line: Camera Translation: [x y z]
		 * Fifth Line: Distortion Parameters: [k1, k2, k3, a1, a2, a3]
		 * Sixth Line: Camera Extrinsics Reference ID: integer
		 * Seventh Line: Camera Resolution in Pixels: wxh (e.g. 640x480)
		 * Eighth Line: Camera Resolution in Millimeters: wxh (e.g. 5.645x4.234)
		 */
		Camera(const std::string& path, int id);

		Camera(const Camera&);

		~Camera();

		/*
		 * Returns the id of the camera
		 */
		inline unsigned int id() const { return m_id; };

		/*
		 * Returns the camera size in pixels
		 */
		inline Size2i size_in_pixels() const { return m_pixel_size; };

		/* 
		 * Returns the camera size in millimeters
		 */
		inline Size2d size_in_mm() const { return m_sensor_size; };

		/* 
		 * Returns the conversion factor from pixel units to millimeters of the camera
		 */
		inline double mm_per_pixel() const { return m_sensor_size.x() / (double)m_pixel_size.x(); };

		/* 
		 * Returns the conversion factor from millimeters to pixel units of the camera
		 */
		inline double pixel_per_mm() const { return (double)m_pixel_size.x() / m_sensor_size.x(); };

		/* 
		 * Returns the CameraParameters object associated with the Camera instance
		 */
		inline CameraParameters camera_parameters() const { return m_params; };

		/*
		 * Returns the ID of the camera whose extrinsics are the origin of the world coordinate system
		 */
		inline unsigned int reference() const { return m_ref; };

		/* 
		 * Returns the radial distortion coefficients associated with the camera
		 */
		inline Point3 distortion() const { return m_distortion; };

		/*
		 * Returns the 3x4 projection matrix associated with the camera
		 */
		inline Matrix projection() const { return m_projection; };

		/**
		 * Returns the normalized camera parameters associated with the camera
		 *
		 * Normalized camera parameters are camera parameters adjusted to units of millimeters
		 * from units of pixels. If the provided camera parameters are in millimeters, calling
		 * this returns an inaccurate set of camera parameters.
		 * 
		 */
		CameraParameters normalized_camera_parameters() const;

		/**
		 * \brief Normalizes camera parameters associated with the camera
		 *
		 * Normalized camera parameters are camera parameters adjusted to units of millimeters
		 * from units of pixels. If the provided camera parameters are in millimeters, calling
		 * this sets the camera parameters to an inaccurate set of camera parameters.
		 *
		 */
		void normalize_camera_parameters();

		/*
		 * Translates the pose of this camera by the provided vector
		 */
		void translate(const Vector3&);

		/* 
		 * Rotates the pose of the camera by the specified rotation matrix
		 */
		void rotate(const Matrix3&);

	private:
		unsigned int m_id;
		Size2i m_pixel_size;
		Size2d m_sensor_size;
		CameraParameters m_params;
		unsigned int m_ref;
		Point3 m_distortion;
		Matrix m_projection;
		CameraPose m_pose;
	};
}

#endif