package bg.sofia.uni.fmi.mjt.investment.wallet;

import bg.sofia.uni.fmi.mjt.investment.wallet.acquisition.Acquisition;
import bg.sofia.uni.fmi.mjt.investment.wallet.acquisition.AcquisitionClass;
import bg.sofia.uni.fmi.mjt.investment.wallet.asset.Asset;
import bg.sofia.uni.fmi.mjt.investment.wallet.exception.InsufficientResourcesException;
import bg.sofia.uni.fmi.mjt.investment.wallet.exception.OfferPriceException;
import bg.sofia.uni.fmi.mjt.investment.wallet.exception.UnknownAssetException;
import bg.sofia.uni.fmi.mjt.investment.wallet.exception.WalletException;
import bg.sofia.uni.fmi.mjt.investment.wallet.quote.Quote;
import bg.sofia.uni.fmi.mjt.investment.wallet.quote.QuoteService;

import java.time.LocalDateTime;
import java.util.*;

public class InvestmentWallet implements Wallet {
    private double balance;
    private final QuoteService quoteService;
    private List<Acquisition> acquisitions;
    private Map<Asset, Integer> assets;

    InvestmentWallet(QuoteService quoteService) {
        this.balance = 0;
        this.quoteService = quoteService;
        this.acquisitions = new ArrayList<>();
        this.assets = new HashMap<>();
    }

    @Override
    public double deposit(double cash) {
        if (cash < 0) {
            throw new IllegalArgumentException("Cannot deposit negative cash");
        }
        this.balance += cash;
        return this.balance;
    }

    @Override
    public double withdraw(double cash) throws InsufficientResourcesException {
        if (cash < 0) {
            throw new IllegalArgumentException("Cannot withdraw negative cash");
        }
        if (this.balance - cash < 0) {
            throw new InsufficientResourcesException("Not enough resources to withdraw");
        }
        this.balance -= cash;
        return this.balance;
    }

    @Override
    public Acquisition buy(Asset asset, int quantity, double maxPrice) throws WalletException {
        if (quantity < 0 || maxPrice < 0 || asset == null) {
            throw new IllegalArgumentException("Negative or null data");
        }
        Quote quote = this.quoteService.getQuote(asset);
        if (quote == null) {
            throw new UnknownAssetException("No defined quote for this asset");
        }
        if (quote.askPrice() > maxPrice) {
            throw new OfferPriceException("The price of the asset is higher than the maxPrice");
        }
        if (quote.askPrice() * quantity > this.balance) {
            throw new InsufficientResourcesException("Not enough balance for transaction");
        }
        this.acquisitions.add(new AcquisitionClass(quote.askPrice(), LocalDateTime.now(), quantity, asset));
        this.balance -= quote.askPrice() * quantity;
        if (this.assets.containsKey(asset)) {
            this.assets.put(asset, this.assets.get(asset) + quantity);
        } else {
            this.assets.put(asset, quantity);
        }
        return this.acquisitions.get(this.acquisitions.size() - 1);
    }

    @Override
    public double sell(Asset asset, int quantity, double minPrice) throws WalletException {
        // check if input is correct
        if (quantity < 0 || minPrice < 0 || asset == null) {
            throw new IllegalArgumentException("Negative or null data");
        }
        // get the quote
        Quote quote = this.quoteService.getQuote(asset);
        // put the code in try block so that if any of the following exceptions are thrown,
        // the method will throw new IllegalArgumentException because of them

        if (quote == null) {
            throw new UnknownAssetException("No defined quote for this asset");
        }
        if (quote.bidPrice() < minPrice) {
            throw new OfferPriceException("The price of the asset is lower than the minPrice");
        }
        // if there are no assets of the requested type, throw exception
        if (!this.assets.containsKey(asset) || this.assets.get(asset) < quantity) {
            throw new InsufficientResourcesException("Not enough asset quantity to sell");
        }
        this.assets.put(asset, this.assets.get(asset) - quantity);
        double deal = quote.bidPrice() * quantity;
        this.balance += deal;
        return deal;
    }

    @Override
    public double getValuation() {
        double totalSum = 0;
        try {
            for (Map.Entry<Asset, Integer> entry : this.assets.entrySet()) {
                totalSum += getValuation(entry.getKey());
            }
            return totalSum;
        } catch (UnknownAssetException ex) {
            return 0;
        }
    }

    @Override
    public double getValuation(Asset asset) throws UnknownAssetException {
        if (asset == null) {
            throw new IllegalArgumentException("Asset is null.");
        }
        double amount;
        amount = this.assets.getOrDefault(asset, 0);
        if (amount == 0) {
            throw new UnknownAssetException("Asset is not in wallet");
        }
        Quote quote = this.quoteService.getQuote(asset);
        if (quote == null) {
            throw new UnknownAssetException("No such asset exists in Quote Service");
        }
        return amount * quote.bidPrice();
    }

    @Override
    public Asset getMostValuableAsset() {
        double evaluation = -1;
        Map.Entry<Asset, Integer> maxEntry = null;
        try {

            for (Map.Entry<Asset, Integer> entry : this.assets.entrySet()) {
                double temp = getValuation(entry.getKey());
                if (temp > evaluation) {
                    maxEntry = entry;
                    evaluation = temp;
                }
            }
            return maxEntry.getKey();
        } catch (UnknownAssetException ex) {
            return null;
        }
    }

    @Override
    public Collection<Acquisition> getAllAcquisitions() {
        return List.copyOf(this.acquisitions);
    }

    @Override
    public Set<Acquisition> getLastNAcquisitions(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("Cannot return collection of negative amounts of acquisitions");
        }
        if (n >= this.acquisitions.size()) {
            return Set.copyOf(this.acquisitions);
        }
        List<Acquisition> temp = this.acquisitions.subList(this.acquisitions.size() - n, this.acquisitions.size());
        return Set.copyOf(temp);
    }
}