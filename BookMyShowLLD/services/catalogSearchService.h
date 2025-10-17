// 8

#pragma once

#include <iostream>
#include "movie.h"

using namespace std;

class Catalog : public Search {
public:
    unordered_map<string, vector<Movie*>> movieTitles;
    unordered_map<string, vector<Movie*>> movieGenres;

    vector<Movie*> searchMovieTitle(const string& title) override {
        return movieTitles[title];
    }

    vector<Movie*> searchMovieGenre(const string& genre) override {
        return movieGenres[genre];
    }
};
