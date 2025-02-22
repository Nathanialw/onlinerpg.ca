//
// Created by desktop on 10/25/24.
//

#include "files.h"

#include <filesystem>
#include <vector>
#include <random>
#include <iostream>


namespace fs = std::filesystem;

namespace Files {

     uint8_t Get_Random_Pic(const std::string &assets_folder) {
	     std::vector<fs::path> image_files;

	     for (const auto &entry: fs::directory_iterator(assets_folder)) {
		     if (entry.is_regular_file() && entry.path().extension() == ".png") { // Assuming images are .png files
			     std::cout << "Found image: " << entry.path().filename().stem() << std::endl;
			     //get just the file name

			     image_files.push_back(entry.path().filename());
		     }
	     }

	     if (image_files.empty()) {
		     std::cerr << "No images found in the assets folder" << std::endl;
		     return 0;
	     }

	     std::random_device rd;
	     std::mt19937 gen(rd());
	     std::uniform_int_distribution<> dis(0, image_files.size() - 1);

	     auto path = image_files[dis(gen)];
	     std::cout << "Random image: " << path << std::endl;
	     auto picNum = stoi(path.string());
	     std::cout << "Random picNum: " << picNum << std::endl;
	     return static_cast<uint8_t>(picNum);
     }
}