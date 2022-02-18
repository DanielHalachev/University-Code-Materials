package bg.sofia.uni.fmi.mjt.rentalservice.vehicle;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;

public class Bicycle extends VehicleBase {
    public Bicycle(String id, Location location) {
        super(id, location);
    }

    @Override
    public double getPricePerMinute() {
        return 0.20;
    }

    @Override
    public String getType() {
        return "BICYCLE";
    }
}
