package bg.sofia.uni.fmi.mjt.gifts.gift;

import bg.sofia.uni.fmi.mjt.gifts.person.Person;

import java.util.Collection;
import java.util.List;

public class BirthdayGift<T extends Priceable> implements Gift<T> {

    private final Person<?> sender;
    private final Person<?> receiver;
    private final Collection<T> items;

    public BirthdayGift(Person<?> sender, Person<?> receiver, Collection<T> items) {
        this.sender = sender;
        this.receiver = receiver;
        this.items = items;
    }

    @Override
    public Person<?> getSender() {
        return this.sender;
    }

    @Override
    public Person<?> getReceiver() {
        return this.receiver;
    }

    @Override
    public double getPrice() {
        double total = 0;
        for (T item : this.items) {
            total += item.getPrice();
        }
        return total;
    }

    @Override
    public void addItem(T t) {
        if (t == null) {
            throw new IllegalArgumentException("Item t is null. Cannot add.");
        }
        this.items.add(t);
    }

    @Override
    public boolean removeItem(T t) {
        if (this.items.contains(t)) {
            this.items.remove(t);
            return true;
        }
        return false;
    }

    @Override
    public Collection<T> getItems() {
        return List.copyOf(this.items);
    }

    @Override
    public T getMostExpensiveItem() {
        T mostExpensive = null;
        for (T item : this.items) {
            if (mostExpensive == null || item.getPrice() > mostExpensive.getPrice()) {
                mostExpensive = item;
            }
        }
        return mostExpensive;
    }
}
