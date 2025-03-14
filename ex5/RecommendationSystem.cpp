//
// Created by bashar on 1/24/2025.
//

#include "User.h"
#include "RecommendationSystem.h"
#include <algorithm>
#include <cmath>

RecommendationSystem::RecommendationSystem() = default;
//helper
double RecommendationSystem::cosine_similarity(const std::vector<double>& v1,
                                               const std::vector<double>& v2) {
    double dot = 0, norm1 = 0, norm2 = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        dot += v1[i] * v2[i];
        norm1 += v1[i] * v1[i];
        norm2 += v2[i] * v2[i];
    }
    return dot / (sqrt(norm1) * sqrt(norm2));
}

sp_movie RecommendationSystem::get_movie(const std::string& name, int year) const {
    auto temp = std::make_shared<Movie>(name, year);
    auto it = _movies.find(temp);
    if (it!=_movies.end()){
        return *it;
    }
    return nullptr;
}

sp_movie RecommendationSystem::add_movie_to_rs(const std::string& name, int year,
                                               const std::vector<double>& features) {
    for (double f : features) {
        if (f < 1 || f > 10) {
            throw std::invalid_argument("features must be between 1-10");
        }
    }
    auto movie = std::make_shared<Movie>(name, year);
    _movies.insert(movie);
    _movie_features[movie] = features;
    return movie;
}

std::ostream& operator<<(std::ostream& os, const RecommendationSystem& rs) {
    // Iterate over the _movies set (already sorted by MovieComparator)
    for (const auto& movie : rs._movies) {
        os << *movie << "\n";  // Use Movie's operator<< to print the movie
    }
    return os;
}

sp_movie RecommendationSystem::recommend_by_content(const User& user) const {
    const auto& ratings = user.get_rank();
    if (ratings.empty()) return nullptr;

    double total_rating = 0;
    for (const auto& [movie, rating] : ratings) {
        total_rating += rating;
    }
    double avg = total_rating / ratings.size();

    std::vector<double> pref_vec(_movie_features.begin()->second.size(), 0.0);
    for (const auto& [movie, rating] : ratings) {
        const auto& features = _movie_features.at(movie);
        double adjusted_rating = rating - avg;
        for (size_t i = 0; i < features.size(); ++i) {
            pref_vec[i] += adjusted_rating * features[i];
        }
    }
    double max_sim = -1;
    sp_movie best_movie = nullptr;
    for (const auto& movie : _movies) {
        if (!ratings.count(movie)) {
            double sim = cosine_similarity(pref_vec, _movie_features.at(movie));
            if (sim > max_sim) {
                max_sim = sim;
                best_movie = movie;
            }
        }
    }
    return best_movie;
}

//helper
bool RecommendationSystem::compare_similarities(const std::pair<double, double>& a,
                                                const std::pair<double, double>& b) {
    return a.first > b.first; // Sort descending by similarity score
}

double RecommendationSystem::predict_movie_score(const User& user, const sp_movie& movie, int k) const {
    const auto& target_features = _movie_features.at(movie);
    const auto& ratings = user.get_rank();

    // Get all similarities
    std::vector<std::pair<double, double>> similarities; // (similarity, rating)
    for (const auto& [rated_movie, rating] : ratings) {
        double sim = cosine_similarity(target_features, _movie_features.at(rated_movie));
        similarities.emplace_back(sim, rating);
    }

    std::sort(similarities.begin(), similarities.end(), compare_similarities);


    double sum_sim_rat = 0, sum_sim = 0;
    for (int i = 0; i < k; ++i) {
        sum_sim_rat += similarities[i].first * similarities[i].second;
        sum_sim += similarities[i].first;
    }
    if (sum_sim > 0){
        return sum_sim_rat/sum_sim;
    }
    return 0;
}

sp_movie RecommendationSystem::recommend_by_cf(const User& user, int k) const {
    const auto& ratings = user.get_rank();
    if (ratings.empty()){
        return nullptr;
    }

    double max_score = -1;
    sp_movie best_movie = nullptr;

    // Iterate over all movies in the system
    for (const auto& movie : _movies) {
        // Skip movies the user has already rated
        if (!ratings.count(movie)) {
            // Predict score for the unrated movie
            double score = predict_movie_score(user, movie, k);

            // Track the best movie
            if (score > max_score) {
                max_score = score;
                best_movie = movie;
            }
        }
    }

    return best_movie;
}
