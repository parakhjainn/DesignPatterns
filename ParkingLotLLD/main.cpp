#include <iostream>
#include "parkingLotService.h"
#include "level.h"
#include "parkingSpot.h"
#include "models/car.h"
#include "models/bike.h"
#include "factories/vehicleFactory.h"

using namespace std;

int main() {
    // Singleton access
    ParkingLot& lot = ParkingLot::getInstance();
    
    lot.addLevel(new Level(0, 1));
    
    // Create vehicles using factory pattern
    Vehicle* goodCar = VehicleFactory::createVehicle("CAR-123", VehicleType::CAR);
    Vehicle* goodBike = VehicleFactory::createVehicle("BIKE-456", VehicleType::BIKE);

    Vehicle* car = VehicleFactory::createVehicle("CAR-321", VehicleType::CAR);
    
    lot.parkVehicle(goodCar);
    lot.parkVehicle(goodBike);
    
    lot.displayAvailability();
    
    lot.parkVehicle(car);
    
    lot.displayAvailability();
    
    lot.unparkVehicle(goodCar);
    
    lot.displayAvailability();

    lot.parkVehicle(car);

    delete goodCar;
    delete goodBike;
    delete car;
    
    return 0;
}
