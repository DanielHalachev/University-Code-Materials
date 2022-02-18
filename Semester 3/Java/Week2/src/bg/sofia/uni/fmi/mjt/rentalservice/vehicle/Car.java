package bg.sofia.uni.fmi.mjt.rentalservice.vehicle;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;

public class Car extends VehicleBase {

    public Car(String id, Location location) {
        super(id, location);
    }

    @Override
    public double getPricePerMinute() {
        return 0.50;
    }

    @Override
    public String getType() {
        return "CAR";
    }
}
