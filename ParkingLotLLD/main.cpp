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

int main() {
    // Singleton access
    ParkingLot& lot = ParkingLot::getInstance();

    // Give ownership of the Level to the lot
    lot.addLevel(std::make_unique<Level>(0, 1));

    // Polymorphic objects: use smart pointers, not values (avoid slicing)
    auto car   = std::make_unique<Car>("abc");
    auto bike  = std::make_unique<Bike>("abc");

    // Factory pattern returning unique_ptr<Vehicle>
    auto goodCar  = VehicleFactory::createVehicle("abc", VehicleType::CAR);
    auto goodBike = VehicleFactory::createVehicle("cde", VehicleType::BIKE);

    // Park vehicles using non-owning raw pointers (observers)
    lot.parkVehicle(goodCar.get());
    lot.parkVehicle(goodBike.get());

    // Attempt to park a different car
    lot.parkVehicle(car.get()); // may fail if no spot or type mismatch
    lot.displayAvailability();

    lot.unparkVehicle(goodCar.get());
    lot.displayAvailability();

    lot.parkVehicle(car.get());

    return 0;
}
