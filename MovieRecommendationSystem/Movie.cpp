
#include "Movie.h"

#include <utility>
#define HASH_START 17
#define RES_MULT 31

/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie& movie){
    std::size_t res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
    return !(*m1 < *m2) && !(*m2 < *m1);
}

Movie::Movie(std::string name, int year):_movie_name{std::move(name)},_year_created{year}{}

const std::string& Movie::get_name() const {
    return _movie_name;
}

int Movie::get_year() const {
    return _year_created;
}

bool Movie::operator<(const Movie& other) const {
    if (_year_created == other._year_created) {
        return _movie_name < other._movie_name;
    }
    return _year_created < other._year_created;
}

std::ostream& operator<<(std::ostream& os, const Movie &movie) {
    os << movie.get_name() << "(" << movie.get_year() << ")" << std::endl;
    return os;
}
