package bg.sofia.uni.fmi.mjt.rentalservice.location;

import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

public class Location {

    private final double x;
    private final double y;

    public Location(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double distance(Location other) {
        return sqrt(pow((this.x - other.x), 2) + pow((this.y - other.y), 2));
    }
}
