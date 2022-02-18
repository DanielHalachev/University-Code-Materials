public class WeatherForecaster {
    public static int[] getsWarmerIn(int[] temperatures) {
        // O(N^2) solution
//        int[] output = new int[temperatures.length];
//        for (int i = 0; i < temperatures.length - 1; i++) {
//            if (temperatures[i] < temperatures[i + 1]) {
//                output[i] = 1;
//            } else if (temperatures[i] > temperatures[i + 1]) {
//                int j = i + 2;
//                while (temperatures[i] > temperatures[j]) {
//                    output[i]++;
//                    j++;
//                }
//            }
//        }
//        return output;
        // O(N) solution
        // create array to hold result
        int[] result = new int[temperatures.length];
        // scan the upward trend, where it breaks it will be zero
        for (int i = 0; i < temperatures.length - 1; i++) {
            if (temperatures[i] < temperatures[i + 1]) {
                result[i]++;
            }
        }
        // temp variable to hold different things
        // first it will hold how many zeroes we have
        int temp = 0;
        for (int i = 0; i < temperatures.length; i++) {
            if (result[i] == 0) {
                temp++;
            }
        }
        if (temp == 1) {
            return result;
        }
        // create array to store [temperature][index]
        int[][] indexes = new int[temp - 1][2];
        // temp will now be a counter to go through the zeroes array
        temp = 0;
        for (int i = 0; i < temperatures.length - 1; i++) {
            if (result[i] == 0) {
                indexes[temp][0] = temperatures[i];
                indexes[temp][1] = i;
                temp++;
            }
        }
        // temp will now hold the difference in the zero spots
        temp = 0;
        while (temp < indexes.length) {
            // we should search only on the right of the index in question
            int i = indexes[temp][1];
            // keep on moving right until we find a match
            while (i < temperatures.length) {
                // in case we find a match
                if (temperatures[i] > indexes[temp][0]) {
                    result[indexes[temp][1]] = i - indexes[temp][1];
                    break;
                    // in case we dont
                } else {
                    i++;
                }
            }
            // go on to the next problematic index
            temp++;
        }
        return result;
    }
}
