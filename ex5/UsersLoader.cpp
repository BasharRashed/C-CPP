//
// Created by bashar on 1/25/2025.
//
#include <sstream>
#include <fstream>
#include "UsersLoader.h"
#include "User.h"

std::vector<User>
UsersLoader::create_users(const std::string& users_file_path, std::shared_ptr<RecommendationSystem> rs) {

    std::vector<User> users;
    std::ifstream file(users_file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    // Read and parse header line
    std::string header_line;
    if (!std::getline(file, header_line)) {
        throw std::runtime_error("Empty users file");
    }

    std::istringstream header_stream(header_line);
    std::vector<sp_movie> movie_list;
    std::string movie_entry;

    // Parse movie header
    while (header_stream >> movie_entry) {
        size_t dash_pos = movie_entry.find('-');
        if (dash_pos == std::string::npos) {
            throw std::invalid_argument("Invalid movie format in header");
        }

        std::string name = movie_entry.substr(0, dash_pos);
        std::string year_str = movie_entry.substr(dash_pos + 1);
        int year;

        // Parse year using C++ streams
        std::istringstream year_stream(year_str);
        if (!(year_stream >> year) || !year_stream.eof()) {
            throw std::invalid_argument("Invalid format!" );
        }

        // Verify movie exists in recommendation system
        sp_movie movie = rs->get_movie(name, year);
        if (!movie) {
            throw std::invalid_argument("Movie not found");
        }
        movie_list.push_back(movie);
    }

    // Process user ratings
    std::string user_line;
    while (std::getline(file, user_line)) {
        std::istringstream user_stream(user_line);
        std::string username;
        rank_map ratings;

        // Get username
        if (!(user_stream >> username)) {
            throw std::invalid_argument("Username error!");
        }

        // Process ratings
        std::string rating_str;
        size_t movie_index = 0;

        while (user_stream >> rating_str) {

            sp_movie current_movie = movie_list[movie_index];

            if (rating_str != "NA") {
                std::istringstream rating_parser(rating_str);
                double rating;

                if (!(rating_parser >> rating) || !rating_parser.eof()) {
                    throw std::invalid_argument("Error rating");
                }

                if (rating < 1 || rating > 10) {
                    throw std::invalid_argument("Rating out of range [1,10]");
                }

                ratings[current_movie] = rating;
            }

            movie_index++;
        }

        users.emplace_back(username, ratings,rs);
    }

    return users;
}

