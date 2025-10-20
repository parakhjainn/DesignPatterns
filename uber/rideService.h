#pragma once

#include <iostream>
#include <unordered_map>
#include <queue>
#include "rider.h"
#include "driver.h"
#include "ride.h"

class RideService {
    unordered_map<string, Rider> riders;
    unordered_map<string, Driver> drivers;
    unordered_map<string, Ride> rides;
    queue<Ride> requestedRides;

    RideService() {}

public: 
    static RideService& getInstance() {
        static RideService instance;
        return instance;
    }


    void registerRider(Rider rider) {
        riders.insert({rider.getId(), rider});
    }

    void registerDriver(Driver driver) {
        drivers.insert({driver.getId(), driver});
    }

    // Rider can request a Ride
    // Driver can accept a Ride 
    // Driver completes a Ride 
    // Rider/Driver cancels a ride;

    void requestRide(Rider rider, Location pickup, Location drop) {
        string rideId = "RIDE random id";
        Ride ride(rideId, rider, Driver(), pickup, drop, RideStatus::REQUESTED, 0);

        requestedRides.push(ride);

        // TODO: once we have added the ride, we need to update the drivers
        // TODO: notify the drivers
    }

    void acceptRide(Driver driver, Ride ride) {

        // validations 

        ride.setDriver(driver);
        driver.setStatus(DriverStatus::IN_RIDE);
        ride.setStatus(RideStatus::ACCEPTED);

        // notify the rider
    }


    void completeRide(Ride ride) {
        ride.setStatus(RideStatus::COMPLETED);

        // calculate the fare()
        // process the payment 
        // make driver available
    }

};