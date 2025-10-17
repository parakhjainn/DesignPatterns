// 7

#pragma once

#include <iostream>
#include "movie.h"

using namespace std;

// Search Interface will be extended by Catalog etc
class Search {
public:
    virtual ~Search() = default;

    virtual vector<Movie*> searchMovieTitle(const string& title) = 0;
    virtual vector<Movie*> searchMovieGenre(const string& genre) = 0;
};