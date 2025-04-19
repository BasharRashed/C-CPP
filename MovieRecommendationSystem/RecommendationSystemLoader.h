
#ifndef RECOMMENDATIONSYSTEMLOADER_H
#define RECOMMENDATIONSYSTEMLOADER_H
#include "RecommendationSystem.h"
class RecommendationSystemLoader
{
public:
    static std::unique_ptr<RecommendationSystem> create_rs_from_movies(
            const std::string& file_path);
    RecommendationSystemLoader() = delete;
};

#endif // RECOMMENDATIONSYSTEMLOADER_H
