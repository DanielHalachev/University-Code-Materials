package bg.sofia.uni.fmi.mjt.investment.wallet.asset;

public class Fiat extends AssetBase {
    public Fiat(String id, String name) {
        super(id, name);
        this.type = AssetType.FIAT;
    }
}
