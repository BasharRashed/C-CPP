//
// Created by bashar on 1/24/2025.
//

#include "User.h"
#include "RecommendationSystem.h"
#include <iostream>
#include <utility>

User::User(std::string user_name, rank_map& movie_rank_map,
           std::shared_ptr<RecommendationSystem> rs)
           :_user_name{std::move(user_name)}, _rank_map{movie_rank_map},
           _rs{std::move(rs)}{}

const std::string& User::get_name() const {
    return _user_name;
}

const rank_map& User::get_rank()const {
    return _rank_map;
}

void User::add_movie_to_user(const std::string& name, int year,
                             const std::vector<double>& features,
                             double rate) {
    // Add movie to recommendation system first
    sp_movie movie = _rs->add_movie_to_rs(name, year, features);
    // Store user's rating
    _rank_map[movie] = rate;
}

// Content-based recommendation
sp_movie User::get_rs_recommendation_by_content() {
    return _rs->recommend_by_content(*this);
}

// Collaborative filtering recommendation
sp_movie User::get_rs_recommendation_by_cf(int k) {
    return _rs->recommend_by_cf(*this, k);
}

// Movie score prediction
double User::get_rs_prediction_score_for_movie(const std::string& name, int year, int k) {
    sp_movie movie = _rs->get_movie(name, year);
    return _rs->predict_movie_score(*this, movie, k);
}

std::ostream &operator<<(std::ostream& os, const User &user) {
    os << user.get_name() << "\n";

    os << *(user._rs);

    os << std::endl;
    return os;
}



