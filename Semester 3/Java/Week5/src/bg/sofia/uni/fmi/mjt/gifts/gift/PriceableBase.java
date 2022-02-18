package bg.sofia.uni.fmi.mjt.gifts.gift;

public class PriceableBase implements Priceable {

    private final double price;

    public PriceableBase(double price) {
        this.price = price;
    }

    @Override
    public double getPrice() {
        return this.price;
    }
}
