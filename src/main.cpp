#include <iostream>
#include "recon/reconstruct.hpp"

using namespace recon;

int main(int argc, char** argv) {
	if (argc == 4) {
		std::string dir_name(argv[1]);
		int index = std::stoi(argv[2]);
		Reconstructor rec;
		rec.configure(std::filesystem::current_path().string() + "\\" + dir_name + "\\", index);
		rec.project_frame(0, true, true);
		rec.save_scene(std::string(argv[3]), true, true);
		rec.save_scene(std::string(argv[3]), true, false);
	}
	else {
		std::cout << "Wrong parameters supplied. An example invocation is: " << std::endl;
		std::cout << "3d-reconstructor.exe images 92 mycloud";
	}
	return 0;
}