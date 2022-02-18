package bg.sofia.uni.fmi.mjt.logger;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

public class DefaultLogParserTest {

    private LogParser parser;
    private final Path path = Path.of("logs", "logs-0.txt");
    private List<Log> allLogs;

    @BeforeAll
    static void createFile() throws IOException {
        new File("logs").mkdirs();
        List<String> lines = Arrays.asList(
                "[ERROR]|2021-10-03T19:56:16.191679144|bg.sofia.uni.fmi.mjt.logger|LogMessage1",
                "[WARN]|2021-11-03T19:56:16.191679144|bg.sofia.uni.fmi.mjt.logger|LogMessage2",
                "[INFO]|2021-12-03T19:56:16.191679144|bg.sofia.uni.fmi.mjt.logger|LogMessage3",
                "[DEBUG]|2021-12-03T19:56:16.191679144|bg.sofia.uni.fmi.mjt.logger|LogMessage4");
        Path file = Paths.get("logs", "logs-0.txt");
        Files.write(file, lines, StandardCharsets.UTF_8);
    }

    @AfterAll
    static void deleteFile() {
        for (File file : Objects.requireNonNull(Path.of("logs").toFile().listFiles())) {
            if (!file.isDirectory()) {
                file.delete();
            }
        }
        Path.of("logs").toFile().delete();
    }

    @BeforeEach
    void setup() {
        LocalDateTime[] dates = new LocalDateTime[4];
        dates[0] = LocalDateTime.parse("2021-10-03T19:56:16.191679144");
        dates[1] = LocalDateTime.parse("2021-11-03T19:56:16.191679144");
        dates[2] = LocalDateTime.parse("2021-12-03T19:56:16.191679144");
        dates[3] = LocalDateTime.parse("2021-12-03T19:56:16.191679144");
        Level[] enums = new Level[4];
        enums[0] = Level.ERROR;
        enums[1] = Level.WARN;
        enums[2] = Level.INFO;
        enums[3] = Level.DEBUG;
        this.allLogs = new ArrayList<>();
        for (int i = 0; i < 4; i++) {
            this.allLogs.add(new Log(enums[i], dates[i], "bg.sofia.uni.fmi.mjt.logger", "LogMessage" + (i + 1)));
        }
        this.parser = new DefaultLogParser(path);
    }

    @Test
    void testGetLogsNullParameters() {
        assertThrows(IllegalArgumentException.class, () -> this.parser.getLogs(null),
                "Calling getLogs with null parameter should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.parser.getLogs(null, LocalDateTime.now()),
                "Calling getLogs with null parameter should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.parser.getLogs(LocalDateTime.now(), null),
                "Calling getLogs with null parameter should throw IllegalArgumentException");
        assertThrows(IllegalArgumentException.class, () -> this.parser.getLogsTail(-1),
                "Calling getLogsTail with negative parameter for number should throw IllegalArgumentException");
    }

    @Test
    void testEmptyReturn(){
        this.parser=new DefaultLogParser(null);
        assertEquals(new ArrayList<Log>(), this.parser.getLogs(Level.INFO));
    }
    @Test
    void testGetLogsByLevel() {
        List<Log> expectedLogs = new ArrayList<>();
        expectedLogs.add(this.allLogs.get(2));
        assertIterableEquals(expectedLogs, this.parser.getLogs(Level.INFO));
    }

    @Test
    void testGetLogsByTime() {
        LocalDateTime d1 = LocalDateTime.parse("2021-09-03T19:56:06.191679144");
        LocalDateTime d2 = LocalDateTime.parse("2021-12-03T19:56:06.191679144");
        List<Log> expectedLogs = this.allLogs.stream()
                .filter(log -> log.timestamp().isAfter(d1) && log.timestamp().isBefore(d2))
                .toList();
        assertIterableEquals(expectedLogs, this.parser.getLogs(d1, d2));
    }

    @Test
    void testGetLogsTail() {
        List<Log> expectedLogs = new ArrayList<>();
        expectedLogs.add(this.allLogs.get(2));
        expectedLogs.add(this.allLogs.get(3));
        assertIterableEquals(expectedLogs, this.parser.getLogsTail(2));
        expectedLogs.clear();
        expectedLogs.add(this.allLogs.get(0));
        expectedLogs.add(this.allLogs.get(1));
        expectedLogs.add(this.allLogs.get(2));
        expectedLogs.add(this.allLogs.get(3));
        assertIterableEquals(expectedLogs, this.parser.getLogsTail(5));
    }
}
