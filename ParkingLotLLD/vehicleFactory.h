#pragma once

#include <memory>
#include <stdexcept>
#include "vehicle.h"
#include "vehicleType.h"
#include "car.h"
#include "bike.h"

using namespace std;

class VehicleFactory {
public:
    static unique_ptr<Vehicle> createVehicle(const string& licensePlate, VehicleType type) {
        switch (type) {
            case VehicleType::CAR:
                return make_unique<Car>(licensePlate);
            case VehicleType::BIKE:
                return make_unique<Bike>(licensePlate);
            default:
                throw invalid_argument("Invalid vehicle type");
        }
    }
};
