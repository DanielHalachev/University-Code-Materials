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
import static org.mockito.ArgumentMatchers.anyInt;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.when;

@ExtendWith(MockitoExtension.class)
public class LeastFrequentlyUsedCacheTest {

    @Mock
    private Storage<String, String> storageMock;
    private LeastFrequentlyUsedCache<String, String> LFUCache;

    @BeforeEach
    void setup() {
        LFUCache = new LeastFrequentlyUsedCache<>(storageMock, 5);
    }

    @Test
    void testSize() {
        assertEquals(0, LFUCache.size(), "Size of empty cache should be zero");
        LFUCache.put("fake key", " fake value");
        assertEquals(1, LFUCache.size(), "Size of cache with 1 element should be one");
    }

    @Test
    void testValues() {
        String value1 = "value1";
        String value2 = "value2";
        LFUCache.put("key1", value1);
        LFUCache.put("key2", value2);
        Set<String> actualResult = new HashSet<>(LFUCache.values());
        Set<String> expectedResult = new HashSet<>();
        expectedResult.add(value1);
        expectedResult.add(value2);
        assertEquals(expectedResult, actualResult, "Cache should return the correct values");
    }

    @Test
    void testClear() {
        LFUCache.put("fake key", "fake value");
        LFUCache.clear();
        assertEquals(0, LFUCache.getHitRate(), "Clearing the cache should make the hit rate zero");
        assertEquals(0, LFUCache.size(), "Clearing the cache should empty its data");
        assertFalse(LFUCache.containsKey("fake key"),
                "When searching for an element of a cache that has been cleared, it should not exist in it");
    }

    @Test
    void getFromCacheNullKey() {
        assertThrows(IllegalArgumentException.class, () -> LFUCache.getFromCache(null),
                "Trying to get value of null should throw an IllegalArgumentException");
    }

    @Test
    void getFromCache() {
        LFUCache.put("fake key", "fake value");
        assertEquals("fake value", LFUCache.getFromCache("fake key"),
                "Cache should return the correct value, corresponding to a key");
    }

    @Test
    void testPutNullKey() {
        assertThrows(IllegalArgumentException.class, () -> this.LFUCache.getFromCache(null),
                "Getting by null key should throw exception");
    }

    @Test
    void testPut() {
        LFUCache.put("fake key", "fake value");
        assertTrue(this.LFUCache.containsKey("fake key"),
                "After putting in cache, the key should be contained it it");
        assertEquals("fake value", LFUCache.getFromCache("fake key"),
                "Cache should return the correct value, corresponding to a key");
    }

    @Test
    void testContainsKey() {
        LFUCache.put("key", "value");
        assertTrue(LFUCache.containsKey("key"), "Cache should contain the key, if it has been put");
    }

    @Test
    void testContainsKeyNull() {
        assertThrows(IllegalArgumentException.class, () -> this.LFUCache.containsKey(null),
                "Checking for existence of null key should throw exception");
    }

    @Test
    void testEvictFromCache() {
        LFUCache = new LeastFrequentlyUsedCache<>(storageMock, 2);
        LFUCache.put("key1", "value1");
        LFUCache.put("key2", "value2");
        LFUCache.getFromCache("key1");
        LFUCache.getFromCache("key2");
        LFUCache.getFromCache("key1");
        LFUCache.evictFromCache();
        assertTrue(LFUCache.containsKey("key1"), "Eviction from cache should keep the most used element");
        assertFalse(LFUCache.containsKey("key2"), "Eviction from cache should remove the least used element");
    }

    @Test
    void testAddToCacheCapacityReached() throws ItemNotFound {
        when(this.storageMock.retrieve("key3")).thenReturn("value3");
        this.LFUCache = new LeastFrequentlyUsedCache<>(storageMock, 2);
        this.LFUCache.put("key1", "value1");
        this.LFUCache.put("key2", "value2");
        this.LFUCache.get("key1");
        this.LFUCache.get("key2");
        this.LFUCache.get("key2");
        this.LFUCache.get("key3");// this should cause an eviction
        assertFalse(this.LFUCache.containsKey("key1"));
        assertTrue(this.LFUCache.containsKey("key2"));
        assertTrue(this.LFUCache.containsKey("key3"));
        assertEquals(2, this.LFUCache.size());
    }
}
