package bg.sofia.uni.fmi.mjt.investment.wallet.asset;

public class Gold extends AssetBase {
    public Gold(String id, String name) {
        super(id, name);
        this.type = AssetType.GOLD;
    }
}
