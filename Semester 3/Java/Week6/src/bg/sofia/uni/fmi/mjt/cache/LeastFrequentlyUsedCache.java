package bg.sofia.uni.fmi.mjt.cache;

import bg.sofia.uni.fmi.mjt.cache.storage.Storage;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class LeastFrequentlyUsedCache<K, V> extends CacheBase<K, V> {

    private final Map<K, V> cacheMap;
    private final Map<K, Integer> keyUses;

    public LeastFrequentlyUsedCache(Storage<K, V> storage, int capacity) {
        super(storage, capacity);
        cacheMap = new HashMap<>(capacity);
        keyUses = new HashMap<>(capacity);
    }

    @Override
    public int size() {
        return this.cacheMap.size();
    }

    @Override
    public Collection<V> values() {
        return this.cacheMap.values();
    }

    @Override
    public void clear() {
        super.resetHitRate();
        cacheMap.clear();
        keyUses.clear();
    }

    protected V getFromCache(K key) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null. Cannot get from cache");
        }
        V result = this.cacheMap.get(key);
        if (result != null) {
            if (keyUses.containsKey(key)) {
                keyUses.put(key, keyUses.get(key) + 1);
            } else {
                keyUses.put(key, 1);
            }
        }
        return result;
    }

    protected V put(K key, V value) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null. Cannot add");
        }
        keyUses.put(key, 1);
        return cacheMap.put(key, value);
    }

    protected boolean containsKey(K key) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null. Cannot check");
        }
        return this.cacheMap.containsKey(key);
    }

    protected void evictFromCache() {
        K evictionKey = getEvictionKey();
        cacheMap.remove(evictionKey);
        keyUses.remove(evictionKey);
    }

    private K getEvictionKey() {
        int minUsageCount = Integer.MAX_VALUE;
        K toBeRemoved = null;
        for (K key : keyUses.keySet()) {
            int usageCount = keyUses.get(key);
            if (usageCount < minUsageCount) {
                toBeRemoved = key;
                minUsageCount = usageCount;
            }
        }
        return toBeRemoved;
    }
}
