package bg.sofia.uni.fmi.mjt.rentalservice;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;
import bg.sofia.uni.fmi.mjt.rentalservice.service.RentalService;
import bg.sofia.uni.fmi.mjt.rentalservice.vehicle.Bicycle;
import bg.sofia.uni.fmi.mjt.rentalservice.vehicle.Car;
import bg.sofia.uni.fmi.mjt.rentalservice.vehicle.Scooter;
import bg.sofia.uni.fmi.mjt.rentalservice.vehicle.Vehicle;

import java.time.LocalDateTime;

public class Runner {
    public static void main(String[] args) {
        Vehicle[] otherVehicles = {
                new Car("c1", new Location(1, 1)),
                new Bicycle("b1", new Location(10, 5)),
                new Scooter("s1", new Location(7, 3)),
                new Car("c2", new Location(1, 12)),
                new Bicycle("b2", new Location(4, 4)),
                new Scooter("s2", new Location(5, 6)),
                new Car("c3", new Location(17, -5)),
                new Bicycle("b3", new Location(-2, -9)),
        };

        RentalService otherRs = new RentalService(otherVehicles);

        System.out.println(otherRs.rentUntil(new Car("c1", new Location(0, 0)), LocalDateTime.now().plusMinutes(10)));
        System.out.println(otherRs.findNearestAvailableVehicleInRadius("CAR", new Location(1, 1), 11).getId());
    }
}
