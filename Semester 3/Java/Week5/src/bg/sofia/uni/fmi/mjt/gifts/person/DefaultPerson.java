package bg.sofia.uni.fmi.mjt.gifts.person;

import bg.sofia.uni.fmi.mjt.gifts.exception.WrongReceiverException;
import bg.sofia.uni.fmi.mjt.gifts.gift.Gift;

import java.util.*;

public class DefaultPerson<I> implements Person<I> {

    List<Gift<?>> gifts;
    private final I id;

    public DefaultPerson(I id) {
        this.id = id;
        this.gifts = new ArrayList<>();
    }

    @Override
    public Collection<Gift<?>> getNMostExpensiveReceivedGifts(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("Cannot return a negative amount of gifts");
        }
        this.gifts.sort((giftLeft, giftRight) -> Double.compare(giftRight.getPrice(), giftLeft.getPrice()));
        if (this.gifts.size() <= n) {
            return List.copyOf(this.gifts);
        }
        return List.copyOf(this.gifts.subList(0, n));
    }

    @Override
    public Collection<Gift<?>> getGiftsBy(Person<?> person) {
        if (person == null) {
            throw new IllegalArgumentException("Cannot get gifts from a null person");
        }
        List<Gift<?>> giftsFromPerson = new ArrayList<>();
        for (Gift<?> gift : this.gifts) {
            if (gift.getSender().equals(person)) {
                giftsFromPerson.add(gift);
            }
        }
        return List.copyOf(giftsFromPerson);
    }

    @Override
    public I getId() {
        return this.id;
    }

    @Override
    public void receiveGift(Gift<?> gift) {
        if (gift == null) {
            throw new IllegalArgumentException("Cannot receive null gift");
        }
        if (!gift.getReceiver().equals(this)) {
            throw new WrongReceiverException("Gift received by wrong person");
        }
        this.gifts.add(gift);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DefaultPerson<?> that = (DefaultPerson<?>) o;
        return getId().equals(that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }
}
