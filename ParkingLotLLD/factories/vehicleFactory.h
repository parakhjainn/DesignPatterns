#pragma once

#include <memory>
#include "../models/vehicle.h"
#include "../models/car.h"
#include "../models/bike.h"

using namespace std;

class VehicleFactory {
public:
    // unique_ptr is a smart pointer introduced in C++11 that provides automatic memory management 
    // for dynamically allocated objects. It is defined in the <memory> header and represents 
    // exclusive ownership - only one unique_ptr can own an object at any given time.​
    static Vehicle* createVehicle(const string& licensePlate, VehicleType type) {
        switch (type) {
            case VehicleType::CAR:
                return new Car(licensePlate);
            case VehicleType::BIKE:
                return new Bike(licensePlate);
            default:
                throw invalid_argument("Invalid vehicle type");
        }
    }
};
