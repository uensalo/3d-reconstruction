#include "recon/camera.hpp"

using namespace recon;

Camera::Camera(const std::string& path, int id) {
	//open camera metadata file 
	std::ifstream metadata_file(path);
	if (metadata_file.is_open()) {
		CameraParameterRecord rec;
		std::string line;
		std::getline(metadata_file, line); // first line is schema, skip this
		getline(metadata_file, line); // second line is intrinsics [fx, fy, cx, cy, s]
		line = line.substr(1, line.length() - 2);
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		std::stringstream ss(line);
		std::string tmp;

		std::getline(ss, tmp, ',');
		rec.m_fx = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_fy = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_cx = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_cy = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_s = std::stod(tmp);

		getline(metadata_file, line); // third line is rotation [qx, qy, qz, qw]. x and y are swapped.
		line = line.substr(1, line.length() - 2);
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		ss = std::stringstream(line);

		std::getline(ss, tmp, ',');
		rec.m_qy = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_qx = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_qz = std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_qw = std::stod(tmp);

		getline(metadata_file, line); // fourth line translation [x, y, z]. x and y are swapped.
		line = line.substr(1, line.length() - 2);
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		ss = std::stringstream(line);

		std::getline(ss, tmp, ',');
		rec.m_y = 1000 * std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_x = 1000 * std::stod(tmp);

		std::getline(ss, tmp, ',');
		rec.m_z = std::stod(tmp);

		getline(metadata_file, line); // fifth line is distortion [k1, k2, k3, a1, a2, a3]
		line = line.substr(1, line.length() - 2);
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		ss = std::stringstream(line);

		std::getline(ss, tmp, ',');
		double kx = std::stod(tmp);

		std::getline(ss, tmp, ',');
		double ky = std::stod(tmp);

		std::getline(ss, tmp, ',');
		double kz = std::stod(tmp);

		getline(metadata_file, line); // sixth line is reference id
		unsigned int ref = std::stoul(line);

		getline(metadata_file, line); // seventh line is pixel wxh
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		ss = std::stringstream(line);

		std::getline(ss, tmp, 'x');
		int sizepx = std::stoi(tmp);

		std::getline(ss, tmp, 'x');
		int sizepy = std::stoi(tmp);

		getline(metadata_file, line); // eighth line is sensor wxh in mm
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		ss = std::stringstream(line);

		std::getline(ss, tmp, 'x');
		double sizesx = std::stod(tmp);

		std::getline(ss, tmp, 'x');
		double sizesy = std::stod(tmp);

		m_params = CameraParameters(rec);
		m_id = id;
		m_pixel_size = Size2i(sizepx, sizepy);
		m_sensor_size = Size2d(sizesx, sizesy);
		m_ref = ref;
		m_distortion = Point3(kx, ky, kz);
		m_pose = CameraPose(m_params.rotation(), m_params.translation());
		m_projection = m_params.intrinsics() * m_pose.rototranslation();
	}
}


Camera::Camera(const Camera& c) {
	m_id = c.m_id;
	m_pixel_size = c.m_pixel_size;
	m_sensor_size = c.m_sensor_size;
	m_params = c.m_params;
	m_ref = c.m_ref;
	m_distortion = c.m_distortion;
	m_projection = c.m_projection;
	m_pose = c.m_pose;
}

Camera::~Camera() {

}

void Camera::translate(const Vector3& trs) {
	m_pose.translate(trs);
	m_projection = m_params.intrinsics() * m_pose.rototranslation();
}

void recon::Camera::rotate(const Matrix3& rot) {
	m_pose.rotate(rot);
	m_projection = m_params.intrinsics() * m_pose.rototranslation();
}

CameraParameters Camera::normalized_camera_parameters() const {
	double factor = m_sensor_size.x() / m_pixel_size.x();
	CameraParameterRecord rec;
	rec.m_fx = m_params.fx() * factor;
	rec.m_fy = m_params.fy() * factor;
	rec.m_cx = m_params.cx() * factor;
	rec.m_cy = m_params.cy() * factor;
	rec.m_s = m_params.s() * factor;

	rec.m_qx = m_params.qx();
	rec.m_qy = m_params.qy();
	rec.m_qz = m_params.qz();
	rec.m_qw = m_params.qw();

	rec.m_x = m_params.x();
	rec.m_y = m_params.y();
	rec.m_z = m_params.z();

	return CameraParameters(rec);
}

void Camera::normalize_camera_parameters() {
	double factor = m_sensor_size.x() / m_pixel_size.x();
	CameraParameterRecord rec;
	rec.m_fx = m_params.fx() * factor;
	rec.m_fy = m_params.fy() * factor;
	rec.m_cx = m_params.cx() * factor;
	rec.m_cy = m_params.cy() * factor;
	rec.m_s = m_params.s() * factor;

	rec.m_qx = m_params.qx();
	rec.m_qy = m_params.qy();
	rec.m_qz = m_params.qz();
	rec.m_qw = m_params.qw();

	rec.m_x = m_params.x();
	rec.m_y = m_params.y();
	rec.m_z = m_params.z();

	m_params = CameraParameters(rec);
}
