//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <map>
#include <set>
#include "Movie.h"


class User;

class RecommendationSystem
{

private:
    struct MovieComparator {
        bool operator()(const sp_movie& a, const sp_movie& b) const {
            return *a < *b;
        }
    };

    std::set<sp_movie, MovieComparator> _movies;
    std::unordered_map<sp_movie, std::vector<double>,
            hash_func, equal_func> _movie_features;
    //helpers
    static double cosine_similarity(const std::vector<double>& v1,
                                    const std::vector<double>& v2);

    static bool compare_similarities(const std::pair<double, double>& a,
                                     const std::pair<double, double>& b);


public:
    RecommendationSystem();
    sp_movie add_movie_to_rs(const std::string& name, int year,
                             const std::vector<double>& features);

    sp_movie recommend_by_content(const User& user_rankings) const;

    sp_movie recommend_by_cf(const User& user, int k) const;

    double predict_movie_score(const User& user, const sp_movie& movie, int k) const;

    sp_movie get_movie(const std::string& name, int year) const;

    friend std::ostream& operator<<(std::ostream& os, const RecommendationSystem& rs);

};

#endif // RECOMMENDATIONSYSTEM_H
