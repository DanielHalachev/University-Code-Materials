package bg.sofia.uni.fmi.mjt.rentalservice.vehicle;

import bg.sofia.uni.fmi.mjt.rentalservice.location.Location;

import java.time.LocalDateTime;
import java.util.Objects;

public abstract class VehicleBase implements Vehicle {
    protected Location location;
    protected String id;
    protected LocalDateTime endTimeOfRent;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        VehicleBase that = (VehicleBase) o;
        return getId().equals(that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    public VehicleBase(String id, Location location) {
        this.id = id;
        this.location = location;
        this.endTimeOfRent = LocalDateTime.now();
    }

    @Override
    public boolean vehicleIsUnavailable() {
        return !this.endTimeOfRent.isBefore(LocalDateTime.now());
    }

    @Override
    public String getId() {
        return this.id;
    }

    @Override
    public Location getLocation() {
        return this.location;
    }

    @Override
    public LocalDateTime getEndOfReservationPeriod() {
        if (this.endTimeOfRent.isBefore(LocalDateTime.now())) {
            return LocalDateTime.now();
        }
        return this.endTimeOfRent;
    }

    @Override
    public void setEndOfReservationPeriod(LocalDateTime until) {
        this.endTimeOfRent = until;
    }
}
