//
// Created by bashar on 1/25/2025.
//
#include "RecommendationSystemLoader.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <stdexcept>

std::unique_ptr<RecommendationSystem> RecommendationSystemLoader::create_rs_from_movies(
        const std::string& file_path) {

    auto rs = std::make_unique<RecommendationSystem>();
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string movie_info;
        iss >> movie_info;

        // Parse movie name and year
        size_t dash_pos = movie_info.find('-');

        std::string name = movie_info.substr(0, dash_pos);
        std::string year_str = movie_info.substr(dash_pos + 1);

        std::istringstream year_stream(year_str);
        int year;
        if (!(year_stream >> year) || !year_stream.good()) {
            throw std::invalid_argument("Invalid year in");
        }

        if (year <= 0) {
            throw std::invalid_argument("Year must be positive");
        }

        std::vector<double> features;
        double feature;
        while (iss >> feature) {
            features.push_back(feature);
        }

        rs->add_movie_to_rs(name, year, features);
    }

    return rs;
}
