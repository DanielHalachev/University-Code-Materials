package bg.sofia.uni.fmi.mjt.rentalservice.vehicle;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;

public class Scooter extends VehicleBase {

    public Scooter(String id, Location location) {
        super(id, location);
    }

    @Override
    public double getPricePerMinute() {
        return 0.30;
    }

    @Override
    public String getType() {
        return "SCOOTER";
    }
}
