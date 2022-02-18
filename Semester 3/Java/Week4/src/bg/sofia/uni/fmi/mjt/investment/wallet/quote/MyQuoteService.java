package bg.sofia.uni.fmi.mjt.investment.wallet.quote;

import bg.sofia.uni.fmi.mjt.investment.wallet.asset.Asset;

import java.util.HashMap;
import java.util.Map;

public class MyQuoteService implements QuoteService {
    private Map<Asset, Quote> database;

    public MyQuoteService(HashMap<Asset, Quote> data) {
        this.database = new HashMap<>(data);
    }

    @Override
    public Quote getQuote(Asset asset) {
        if (asset == null) {
            throw new IllegalArgumentException("Asset is null");
        }
        return this.database.getOrDefault(asset, null);
    }
}
