//
// Created on 2/21/2022.
//
#ifndef USERFACTORY_H
#define USERFACTORY_H
#include "User.h"
#include "RecommendationSystem.h"
class UsersLoader
{
public:

    static std::vector<User> create_users(
            const std::string& users_file_path,
            std::shared_ptr<RecommendationSystem> rs);

    // Prevent instantiation
    UsersLoader() = delete;

};

#endif //USERFACTORY_H
