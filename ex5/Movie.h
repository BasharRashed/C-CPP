
#ifndef EX5_MOVIE_H
#define EX5_MOVIE_H

#include <iostream>
#include <vector>
#include <memory>

#define HASH_START 17



class Movie;

typedef std::shared_ptr<Movie> sp_movie;

/**
 * those declartions and typedefs are given to you and should be used in the ex
 */
typedef std::size_t (*hash_func)(const sp_movie& movie);
typedef bool (*equal_func)(const sp_movie& m1,const sp_movie& m2);

std::size_t sp_movie_hash(const sp_movie& movie);

bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2);

class Movie
{
private:
    std::string _movie_name;
    int _year_created;
public:
    Movie(std::string name, int year);
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    bool operator<(const Movie& other)const;
    const std::string& get_name() const;
    int get_year() const;
};


#endif //EX5_MOVIE_H
