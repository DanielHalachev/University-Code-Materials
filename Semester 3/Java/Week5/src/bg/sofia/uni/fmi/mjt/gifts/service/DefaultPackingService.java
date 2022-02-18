package bg.sofia.uni.fmi.mjt.gifts.service;

import bg.sofia.uni.fmi.mjt.gifts.gift.BirthdayGift;
import bg.sofia.uni.fmi.mjt.gifts.gift.Gift;
import bg.sofia.uni.fmi.mjt.gifts.gift.Priceable;
import bg.sofia.uni.fmi.mjt.gifts.person.Person;

import java.util.Collection;
import java.util.List;

public class DefaultPackingService<T extends Priceable> implements PackingService<T> {

    public DefaultPackingService() {

    }

    @Override
    public Gift<T> pack(Person<?> sender, Person<?> receiver, T item) {
        if (sender == null || receiver == null || item == null) {
            throw new IllegalArgumentException("The Sender, The receiver or the Item is null.");
        }
        return new BirthdayGift<>(sender, receiver, List.of(item));
    }

    @Override
    public Gift<T> pack(Person<?> sender, Person<?> receiver, T... items) {
        if (sender == null || receiver == null) {
            throw new IllegalArgumentException("The Sender or the receiver is null.");
        }
        for (T item : items) {
            if (item == null) {
                throw new IllegalArgumentException("One or more of the items to pack is null");
            }
        }
        return new BirthdayGift<>(sender, receiver, List.of(items));
    }

    @Override
    public Collection<T> unpack(Gift<T> gift) {
        if (gift == null) {
            throw new IllegalArgumentException("Gift is null");
        }
        return List.copyOf(gift.getItems());
    }
}
