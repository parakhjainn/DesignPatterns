#include <iostream>
#include <memory>
#include "parkingLotService.h"
#include "level.h"
#include "parkingSpot.h"
#include "vehicle.h"
#include "vehicleType.h"
#include "bike.h"
#include "car.h"
#include "vehicleFactory.h"

using namespace std;

int main() {
    // Singleton access
    ParkingLot& lot = ParkingLot::getInstance();
    
    lot.addLevel(make_unique<Level>(0, 1));
    
    // Create vehicles using factory pattern
    auto goodCar = VehicleFactory::createVehicle("abc", VehicleType::CAR);
    auto goodBike = VehicleFactory::createVehicle("def", VehicleType::BIKE);

    auto car = VehicleFactory::createVehicle("abc", VehicleType::CAR);
    
    cout << "=== Initial Parking ===\n";
    lot.parkVehicle(goodCar.get());
    lot.parkVehicle(goodBike.get());
    
    cout << "\n=== Display Availability ===\n";
    lot.displayAvailability();
    
    cout << "\n=== park car ===\n";
    lot.parkVehicle(car.get());
    
    cout << "\n=== Display After parking ===\n";
    lot.displayAvailability();
    
    cout << "\n=== unpark goodCar ===\n";
    lot.unparkVehicle(goodCar.get());
    
    cout << "\n=== Final Display ===\n";
    lot.displayAvailability();

    cout << "\n=== after unpark goodCar, now park car ===\n";
    lot.parkVehicle(car.get());
    
    return 0;
}
