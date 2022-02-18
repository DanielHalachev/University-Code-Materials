package bg.sofia.uni.fmi.mjt.logger;

import java.io.BufferedReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class DefaultLogParser implements LogParser {

    public static final int LEVEL_POSITION = 0;
    public static final int TIMESTAMP_POSITION = 1;
    public static final int PACKAGE_POSITION = 2;
    public static final int MESSAGE_POSITION = 3;
    Path path;

    public DefaultLogParser(Path logsFilePath) {
        this.path = logsFilePath;
    }

    List<Log> readLogs() {
        List<Log> logs = new ArrayList<>();
        try (BufferedReader reader = Files.newBufferedReader(this.path)) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] data = line.split("\\|");
                logs.add(
                        new Log(Level.valueOf(data[LEVEL_POSITION].substring(1, data[LEVEL_POSITION].length() - 1)),
                                LocalDateTime.parse(data[TIMESTAMP_POSITION]),
                                data[PACKAGE_POSITION],
                                data[MESSAGE_POSITION]));
            }
        } catch (Exception e) {
            return logs;
        }
        return logs;
    }

    @Override
    public List<Log> getLogs(Level level) {
        if (level == null) {
            throw new IllegalArgumentException("Level is null. Cannot proceed");
        }
        List<Log> logsOfLevel = new ArrayList<>();
        for (Log l : readLogs()) {
            if (l.level().equals(level)) {
                logsOfLevel.add(l);
            }
        }
        return List.copyOf(logsOfLevel);
    }

    @Override
    public List<Log> getLogs(LocalDateTime from, LocalDateTime to) {
        if (from == null || to == null) {
            throw new IllegalArgumentException("One or more timeframe bounds is null. Cannot proceed");
        }
        List<Log> logsOfLevel = new ArrayList<>();
        for (Log l : readLogs()) {
            if (l.timestamp().isAfter(from) && l.timestamp().isBefore(to)) {
                logsOfLevel.add(l);
            }
        }
        return List.copyOf(logsOfLevel);
    }

    @Override
    public List<Log> getLogsTail(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("N is negative. Cannot proceed");
        }
        if (n >= readLogs().size()) {
            return List.copyOf(readLogs());
        }
        return List.copyOf(readLogs().subList(readLogs().size() - n, readLogs().size()));
    }
}
