#pragma once

class Location {
    // Note to myself: 
    // This should be double but keeping int for simplicity sake, Call it out in an interview
    int latitude;
    int longitude;

public: 
    Location() {}

    Location(int latitude_, int longitude_) : latitude(latitude_), longitude(longitude_) {}

};