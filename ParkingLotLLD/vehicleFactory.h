#include <iostream>
#include <string>
#include "vehicle.h"
#include "vehicleType.h"
#include "car.h"
#include "bike.h"

using namespace std;

class VehicleFactory {
public:
    static Vehicle createVehicle(string licensePlate, VehicleType type) {
        switch (type) {
            case VehicleType::CAR :
                return Car(licensePlate);
            case VehicleType::BIKE : 
                return Bike(licensePlate);
            default:
                throw invalid_argument("Invalid vehicle type");
        }
    }
};