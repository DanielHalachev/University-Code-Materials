package bg.sofia.uni.fmi.mjt.rentalservice.service;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;
import bg.sofia.uni.fmi.mjt.rentalservice.vehicle.Vehicle;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

public class RentalService implements RentalServiceAPI {
    public RentalService(Vehicle[] vehicles) {
        this.vehicles = vehicles;
    }

    int vehicleExists(Vehicle vehicle) {
        if (vehicle == null) {
            return -1;
        }
        for (int i = 0; i < this.vehicles.length; i++) {
            if (this.vehicles[i].getId().equals(vehicle.getId())) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public double rentUntil(Vehicle vehicle, LocalDateTime until) {
        int i = vehicleExists(vehicle);
        if (i == -1 || vehicle.getEndOfReservationPeriod().isAfter(LocalDateTime.now()) || until.isBefore(LocalDateTime.now())) {
            return -1.0;
        }
        this.vehicles[i].setEndOfReservationPeriod(until);
        long intervalInSeconds = ChronoUnit.SECONDS.between(LocalDateTime.now(), until);
        long intervalInMinutes = intervalInSeconds / 60;
        if (intervalInSeconds % 60 > 0) {
            ++intervalInMinutes;
        }
        return intervalInMinutes * vehicle.getPricePerMinute();
    }

    @Override
    public Vehicle findNearestAvailableVehicleInRadius(String type, Location location, double maxDistance) {
        if (vehicles.length == 0) {
            return null;
        }
        int i = 0;
        while (this.vehicles[i].vehicleIsUnavailable() || !this.vehicles[i].getType().equals(type)) {
            i++;
            if (i >= vehicles.length) {
                return null;
            }
        }
        double minDistance = this.vehicles[i].getLocation().distance(location);
        Vehicle nearest = vehicles[i];
        for (; i < this.vehicles.length; i++) {
            if (this.vehicles[i].vehicleIsUnavailable() || !this.vehicles[i].getType().equals(type)) {
                continue;
            }
            if (this.vehicles[i].getLocation().distance(location) < minDistance) {
                nearest = this.vehicles[i];
                minDistance = this.vehicles[i].getLocation().distance(location);
            }
        }
        if (minDistance > maxDistance) {
            return null;
        }
        return nearest;
    }

    private Vehicle[] vehicles;
}
