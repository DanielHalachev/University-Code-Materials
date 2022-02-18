package bg.sofia.uni.fmi.mjt.cache;

import bg.sofia.uni.fmi.mjt.cache.storage.Storage;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;

public class LeastRecentlyUsedCache<K, V> extends CacheBase<K, V> {

    public static final float LOAD_FACTOR = 0.75f;
    private final Map<K, V> cacheMap;

    public LeastRecentlyUsedCache(Storage<K, V> storage, int capacity) {
        super(storage, capacity);
        this.cacheMap = new LinkedHashMap<>(capacity, LOAD_FACTOR, true);
    }

    @Override
    public int size() {
        return cacheMap.size();
    }

    @Override
    public void clear() {
        super.resetHitRate();
        cacheMap.clear();
    }

    @Override
    public Collection<V> values() {
        return this.cacheMap.values();
    }

    protected V getFromCache(K key) {
        if (key == null) {
            throw new IllegalArgumentException("Cannot get from cache by null key");
        }
        return cacheMap.get(key);
    }

    protected V put(K key, V value) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null. Cannot put");
        }
        return cacheMap.put(key, value);
    }

    protected boolean containsKey(K key) {
        if (key == null) {
            throw new IllegalArgumentException("Key is null. Cannot check");
        }
        return cacheMap.containsKey(key);
    }

    protected void evictFromCache() {
        var it = cacheMap.keySet().iterator();
        if (it.hasNext()) {
            it.next();
            it.remove();
        }
    }
}