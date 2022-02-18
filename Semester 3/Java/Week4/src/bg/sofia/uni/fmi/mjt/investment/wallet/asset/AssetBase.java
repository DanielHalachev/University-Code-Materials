package bg.sofia.uni.fmi.mjt.investment.wallet.asset;

public abstract class AssetBase implements Asset {
    protected String name;
    protected String id;
    protected AssetType type;

    public AssetBase(String id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public String getId() {
        return this.id;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public AssetType getType() {
        return this.type;
    }
}
