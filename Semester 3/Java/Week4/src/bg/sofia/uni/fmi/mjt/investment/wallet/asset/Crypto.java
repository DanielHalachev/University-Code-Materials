package bg.sofia.uni.fmi.mjt.investment.wallet.asset;

public class Crypto extends AssetBase {
    public Crypto(String id, String name) {
        super(id, name);
        this.type = AssetType.CRYPTO;
    }
}
