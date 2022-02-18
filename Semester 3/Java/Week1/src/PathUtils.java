public class PathUtils {
    public static String getCanonicalPath(String path) {
        // remove unnecessary slashes
        path = path.replaceAll("///*", "/");
        // remove first slash so that first element of array is not empty
        path = path.replaceFirst("/", "");
        // store each directory into an array element
        String[] directories = path.split("/");
        // build the string
        StringBuilder builder = new StringBuilder();
        // scan each directory and act accordingly
        for (String directory : directories) {
            // necessary check in case the last directory is /./
            if (directory.equals(".")) {
                continue;
            }
            // remove one of the previous directories in the resulting string
            if (directory.equals("..")) {
                int lastSlashIndex = builder.lastIndexOf("/");
                if (lastSlashIndex != -1) {
                    builder.delete(lastSlashIndex, builder.length());
                }
                // if everything is normal, just append
            } else {
                builder.append("/").append(directory);
            }
        }
        // in case it's an empty directory, return "/"
        if (builder.toString().equals("")) {
            return "/";
        }
        // finally, return the resulting string
        return builder.toString();
    }

}
