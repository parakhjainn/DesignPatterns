// 3

#pragma once

#include <string>
#include <unordered_map>
#include "movie.h"
#include "theatre.h"
#include "seat.h"

using namespace std;

class Show {
private:
    string id;
    Movie movie;
    Theatre theatre;
    string startTime; // can be used chrono library for actual time
    string endTime; // same chrono
    unordered_map<string, Seat> seats;

public:
    Show(const string& id, const Movie& movie, const Theatre& theatre, 
         const string& st, const string& et,
         const unordered_map<string, Seat>& seats)
        : id(id), movie(movie), theatre(theatre), 
          startTime(st), endTime(et), seats(seats) {}

    string getId() const {
        return id;
    }

    Movie getMovie() const {
        return movie;
    }

    string getEndTime() const {
        return endTime;
    }

    string getStartTime() const {
        return startTime;
    }
};
