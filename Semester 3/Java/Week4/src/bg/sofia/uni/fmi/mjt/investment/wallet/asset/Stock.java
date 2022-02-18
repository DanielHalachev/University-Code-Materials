package bg.sofia.uni.fmi.mjt.investment.wallet.asset;

public class Stock extends AssetBase {
    public Stock(String id, String name) {
        super(id, name);
        this.type = AssetType.STOCK;
    }
}
