#pragma once
#ifndef __recon_typedefines_h__
#define __recon_typedefines_h__

#include <Eigen/Dense>
#include <opencv2/opencv.hpp>

namespace recon {
	typedef Eigen::MatrixXd Matrix;
	typedef Eigen::VectorXd Vector;

	typedef Eigen::Matrix4d Matrix4;
	typedef Eigen::Matrix3d Matrix3;
	typedef Eigen::Matrix2d Matrix2;

	typedef Eigen::Vector4d Vector4;
	typedef Eigen::Vector3d Vector3;
	typedef Eigen::Vector2d Vector2;

	typedef Eigen::Vector4d Point4;
	typedef Eigen::Vector3d Point3;
	typedef Eigen::Vector2d Point2;

	typedef Eigen::Vector4d Color4;
	typedef Eigen::Vector3d Color3;

	typedef Eigen::Vector2i Coord2;

	typedef Eigen::Vector2i Size2i;
	typedef Eigen::Vector2d Size2d;

	typedef cv::Mat Image;
}

#endif