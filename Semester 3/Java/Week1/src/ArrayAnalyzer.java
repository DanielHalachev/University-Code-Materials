public class ArrayAnalyzer {
    public static boolean isMountainArray(int[] array) {
        // cannot analyze array of length less than 3
        if (array.length < 3) {
            return false;
        }
        // get the maximum element to partition the array into two parts
        int maxElement = array[0];
        int maxIndex = 0;
        for (int i = 1; i < array.length; i++) {
            if (maxElement < array[i]) {
                maxElement = array[i];
                maxIndex = i;
            }
            // cannot have two max elements
            else if (maxElement == array[i]) {
                return false;
            }
        }
//        // if the peek of the mountain is the end, then there is no mountain
//        if (maxIndex == 0 || maxIndex == array.length - 1) {
//            return true;
//        }
        // check left side
        for (int i = 1; i <= maxIndex; i++) {
            if (array[i - 1] >= array[i]) {
                return false;
            }
        }
        // check right side
        for (int i = maxIndex; i < array.length - 1; i++) {
            if (array[i] <= array[i + 1]) {
                return false;
            }
        }
        // if everything's fine, say true
        return true;
    }

}
