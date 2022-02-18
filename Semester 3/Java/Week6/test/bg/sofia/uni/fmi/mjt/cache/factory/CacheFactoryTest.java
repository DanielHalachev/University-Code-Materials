package bg.sofia.uni.fmi.mjt.cache.factory;

import bg.sofia.uni.fmi.mjt.cache.LeastFrequentlyUsedCache;
import bg.sofia.uni.fmi.mjt.cache.LeastRecentlyUsedCache;
import bg.sofia.uni.fmi.mjt.cache.storage.Storage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(MockitoExtension.class)
public class CacheFactoryTest<K, V> {

    @Mock
    private Storage<K, V> storageMock;

    @Test
    void testGetInstanceCustomCapacityLessThanZero() {
        assertThrows(IllegalArgumentException.class, () -> CacheFactory.getInstance(storageMock, -1, EvictionPolicy.LEAST_FREQUENTLY_USED), "Capacity less than zero should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> CacheFactory.getInstance(storageMock, -1, EvictionPolicy.LEAST_RECENTLY_USED), "Capacity less than zero should throw IllegalArgumentException");
    }

    @Test
    void testGetInstanceCustomCapacityPolicy() {
        assertTrue(CacheFactory.getInstance(storageMock, 1000, EvictionPolicy.LEAST_FREQUENTLY_USED) instanceof LeastFrequentlyUsedCache, "Expected LeastFrequentlyUsedCache");
        assertTrue(CacheFactory.getInstance(storageMock, 1000, EvictionPolicy.LEAST_RECENTLY_USED) instanceof LeastRecentlyUsedCache, "Expected LeastRecentlyUsedCache");
    }


    @Test
    void testGetInstanceDefaultCapacityPolicy() {
        assertTrue(CacheFactory.getInstance(storageMock, EvictionPolicy.LEAST_FREQUENTLY_USED) instanceof LeastFrequentlyUsedCache, "Expected LeastFrequentlyUsedCache");
        assertTrue(CacheFactory.getInstance(storageMock, EvictionPolicy.LEAST_RECENTLY_USED) instanceof LeastRecentlyUsedCache, "Expected LeastRecentlyUsedCache");
    }
}
