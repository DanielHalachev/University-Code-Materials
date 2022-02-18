package bg.sofia.uni.fmi.mjt.investment.wallet.acquisition;

import bg.sofia.uni.fmi.mjt.investment.wallet.asset.Asset;

import java.time.LocalDateTime;

public class AcquisitionClass implements Acquisition {
    private double price;
    private LocalDateTime time;
    private int quantity;
    private final Asset asset;

    public AcquisitionClass(double price, LocalDateTime time, int quantity, Asset asset) {
        this.price = price;
        this.time = time;
        this.quantity = quantity;
        this.asset = asset;
    }

    @Override
    public double getPrice() {
        return this.price;
    }

    @Override
    public LocalDateTime getTimestamp() {
        return this.time;
    }

    @Override
    public int getQuantity() {
        return this.quantity;
    }

    @Override
    public Asset getAsset() {
        return this.asset;
    }
}
