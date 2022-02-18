package bg.sofia.uni.fmi.mjt.cache;

import bg.sofia.uni.fmi.mjt.cache.exception.ItemNotFound;
import bg.sofia.uni.fmi.mjt.cache.storage.Storage;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class LeastRecentlyUsedCacheTest {

    @Mock
    private Storage<String, String> storageMock;
    private LeastRecentlyUsedCache<String, String> LRUCache;

    @BeforeEach
    void setup() {
        LRUCache = new LeastRecentlyUsedCache<>(storageMock, 3);
    }

    @Test
    void testSize() {
        assertEquals(0, LRUCache.size(), "Size of empty cache should be zero");
        LRUCache.put("key", "value");
        assertEquals(1, LRUCache.size(), "Size of cache with 1 element should be 1");
    }

    @Test
    void testClear() {
        LRUCache.put("key", "value");
        LRUCache.clear();
        assertEquals(0, LRUCache.getHitRate(), "Hit rate of a cleared cache should be zero");
        assertEquals(0, LRUCache.size(), "Size of cleared cache should be 0");
        assertFalse(LRUCache.containsKey("key"), "Empty cache shouldn't have any keys");
    }

    @Test
    void testValues() {
        String value1 = "value1";
        String value2 = "value2";
        LRUCache.put("key1", value1);
        LRUCache.put("key2", value2);
        Set<String> actualResult = new HashSet<>(LRUCache.values());
        Set<String> expectedResult = new HashSet<>();
        expectedResult.add(value1);
        expectedResult.add(value2);
        assertEquals(expectedResult, actualResult, "Cache should return the correct values");
    }

    @Test
    void testGetFromCacheNullKey() {
        assertThrows(IllegalArgumentException.class, () -> LRUCache.getFromCache(null),
                "Attempting to get from cache by null key should throw IllegalArgumentException");
    }

    @Test
    void testGetFromCacheNonNullKey() {
        LRUCache.put("key", "value");
        assertEquals("value", LRUCache.getFromCache("key"), "Getting an existing key from cache should return the correct value");
    }

    @Test
    void testPutNullKey() {
        assertThrows(IllegalArgumentException.class, () -> this.LRUCache.put(null, "value"),
                "Putting a null key in cache should throw IllegalArgumentException");
    }

    @Test
    void testPut() {
        LRUCache.put("key", "value");
        assertEquals("value", LRUCache.getFromCache("key"),
                "Putting an element in cache should put the element in the cache");
    }

    @Test
    void testContainsKey() {
        assertFalse(LRUCache.containsKey("key"), "Empty LRU cache should not contain any keys");
        LRUCache.put("key", "value");
        assertTrue(LRUCache.containsKey("key"), "LRUCache should contain the key of an inserted element");
    }

    @Test
    void testEvictFromCache() {
        LRUCache = new LeastRecentlyUsedCache<>(storageMock, 2);
        String key1 = "key1";
        String key2 = "key2";
        LRUCache.put(key1, "value1");
        LRUCache.put(key2, "value2");
        LRUCache.getFromCache(key1);
        LRUCache.getFromCache(key2);
        LRUCache.getFromCache(key1);
        LRUCache.evictFromCache();
        assertFalse(LRUCache.containsKey(key2), "LRU cache should not contain least recently used item after eviction");
        assertNotEquals("value2", this.LRUCache.getFromCache(key2), "Getting from cache an evicted key should return null");
        assertTrue(LRUCache.containsKey(key1), "LRU cache should contain used item after eviction");
        assertEquals("value1", this.LRUCache.getFromCache(key1), "Getting from cache an existing key should return its value");
    }

    // TESTS FOR CACHE BASE
    @Test
    void testGetHitRate() throws ItemNotFound {
        assertEquals(0, this.LRUCache.getHitRate(), "Hit rate of non-used cache should be zero");
        this.LRUCache.put("key", "value");
        this.LRUCache.get("key");
        assertEquals(1, this.LRUCache.getHitRate(), "Hit rate of only successes should be 1");
    }

    @Test
    void testGetNull() {
        assertThrows(IllegalArgumentException.class, () -> LRUCache.get(null));
    }

    @Test
    void testGetFoundInCache() throws ItemNotFound {
        this.LRUCache.put("key", "value");
        assertEquals("value", LRUCache.get("key"),
                "When an item exists in cache, its value should be returned correctly");
        assertEquals(1, LRUCache.getHitRate(), "When get() is successful from cache, the hit rate should increase");
    }

    @Test
    void testGetNotFoundInCache() throws ItemNotFound {
        String key = "key";
        String value = "value";
        when(storageMock.retrieve(key)).thenReturn(value);
        assertEquals(value, LRUCache.get(key),
                "When key is not found in cache, but exists in storage, it should return correct value");
        assertEquals(0, LRUCache.getHitRate(), "When get() is unsuccessful from cache, the hit rate should decrease");
    }

    @Test
    void testAddToCacheNotFoundInCacheAndStorage() {
        when(LRUCache.getFromCache("key")).thenReturn(null);
        when(storageMock.retrieve("key")).thenReturn(null);
        assertThrows(ItemNotFound.class, () -> LRUCache.get("key"), "When a key does not exist neither in cache or storage, ItemNotFound should be thrown");
    }

    @Test
    void testResetHitRate() throws ItemNotFound {
        this.LRUCache.put("key", "value");
        this.LRUCache.get("key");
        this.LRUCache.resetHitRate();
        assertEquals(0, LRUCache.getHitRate());
    }

    @Test
    void testAddToCacheCapacityReached() throws ItemNotFound {
        when(this.storageMock.retrieve("key3")).thenReturn("value3");
        this.LRUCache = new LeastRecentlyUsedCache<>(storageMock, 2);
        this.LRUCache.put("key1", "value1");
        this.LRUCache.put("key2", "value2");
        this.LRUCache.get("key1");
        this.LRUCache.get("key2");
        this.LRUCache.get("key3");
        assertFalse(this.LRUCache.containsKey("key1"));
        assertTrue(this.LRUCache.containsKey("key2"));
        assertTrue(this.LRUCache.containsKey("key3"));
    }
}
