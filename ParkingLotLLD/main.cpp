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
    
    // make_unique is a utility function template introduced in C++14 that creates and returns a 
    // unique_ptr to a dynamically allocated object. It provides a safer, cleaner, and more modern 
    // alternative to manually using the new operator with unique_ptr constructors.
    lot.addLevel(make_unique<Level>(0, 1));
    
    // Create vehicles using factory pattern
    auto goodCar = VehicleFactory::createVehicle("CAR-123", VehicleType::CAR);
    auto goodBike = VehicleFactory::createVehicle("BIKE-456", VehicleType::BIKE);

    auto car = VehicleFactory::createVehicle("CAR-321", VehicleType::CAR);
    
    lot.parkVehicle(goodCar.get());
    lot.parkVehicle(goodBike.get());
    
    lot.displayAvailability();
    
    lot.parkVehicle(car.get());
    
    lot.displayAvailability();
    
    lot.unparkVehicle(goodCar.get());
    
    lot.displayAvailability();

    lot.parkVehicle(car.get());
    
    return 0;
}
