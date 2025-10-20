#pragma once

#include <iostream>
#include <string>
#include "rider.h"
#include "driver.h"

using namespace std;

enum class RideStatus {
    REQUESTED,
    ACCEPTED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

// Notes
// Either we could have full reference or id reference for other classes like Rider/Driver
class Ride {
    string id;
    Rider rider;
    Driver driver; 
    Location pickup;
    Location drop;
    RideStatus status;
    int fare; // can be double but keeping int for simplicity;

public:
    Ride () {}

    Ride(string id, Rider rider, Driver driver, Location pickup, Location drop, RideStatus status, int fare) {
        this ->id = id;
        this ->rider = rider;
        this ->driver = driver;
        this ->pickup = pickup;
        this ->drop = drop;
        this ->status = status;
        this ->fare = fare;
    }

    string getId() {
        return id;
    }

    Rider getRider() {
        return rider;
    }

    Driver getDriver() {
        return driver;
    }

    Location getPickup() {
        return pickup;
    }

    Location getDrop() {
        return drop;
    }

    RideStatus getStatus() {
        return status;
    }

    int getFare() {
        return fare;
    }

    void setStatus(RideStatus status) {
        this ->status = status;
    }

    void updateFare(int fare) {
        this ->fare = fare;
    }

    void updatePickup(Location pickup) {
        this ->pickup = pickup;
    }

    void updateDrop(Location drop) {
        this ->drop = drop;
    }

    void setDriver(Driver driver) {
        this ->driver = driver;
    }
};