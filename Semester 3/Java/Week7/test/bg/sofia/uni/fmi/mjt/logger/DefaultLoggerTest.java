package bg.sofia.uni.fmi.mjt.logger;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

public class DefaultLoggerTest {

    private LoggerOptions options;
    private Logger logger;

    @BeforeEach
    void setup() {
        this.options = new LoggerOptions(DummyClass.class, "logs");
        this.options.setShouldThrowErrors(true);
        this.options.setMaxFileSizeBytes(50);
        this.logger = new DefaultLogger(options);
    }

    void clear() {
        if (this.options.getDirectory() == null) {
            return;
        }
        for (File file : Objects.requireNonNull(Path.of(this.options.getDirectory()).toFile().listFiles())) {
            if (!file.isDirectory()) {
                file.delete();
            }
        }
        Path.of(this.options.getDirectory()).toFile().delete();
    }

    @Test
    void testLogNullParameters() {
        assertThrows(IllegalArgumentException.class, () -> this.logger.log(null, LocalDateTime.now(),
                        "message"),
                "Method must throw IllegalArgumentException when called with null parameters");
        assertThrows(IllegalArgumentException.class, () -> this.logger.log(Level.ERROR, null,
                        "message"),
                "Method must throw IllegalArgumentException when called with null parameters");
        assertThrows(IllegalArgumentException.class, () -> this.logger.log(Level.ERROR, LocalDateTime.now(),
                        null),
                "Method must throw IllegalArgumentException when called with null parameters");
        assertThrows(IllegalArgumentException.class, () -> this.logger.log(Level.ERROR, LocalDateTime.now(),
                        ""),
                "Method must throw IllegalArgumentException when called with empty message");
    }

    @Test
    void testLogFail() {
        this.options = new LoggerOptions(DummyClass.class, null);
        this.options.setShouldThrowErrors(false);
        this.options.setMaxFileSizeBytes(50);
        this.logger = new DefaultLogger(options);
        assertThrows(LogException.class, () -> this.logger.log(Level.ERROR, LocalDateTime.now(), "MyError"));
        this.options.setShouldThrowErrors(true);
        assertThrows(LogException.class, () -> this.logger.log(Level.ERROR, LocalDateTime.now(), "MyError"));
    }

    @Test
    void testLogSuccess() throws IOException {
        LocalDateTime date1 = LocalDateTime.now();
        LocalDateTime date2 = date1.plusSeconds(10);
        LocalDateTime date3 = date2.plusSeconds(10);
        LocalDateTime date4 = date2.plusSeconds(10);
        this.logger.log(Level.ERROR, date1, "Log1Message");
        this.logger.log(Level.WARN, date2, "Log2Message");
        this.logger.log(Level.INFO, date3, "Log3Message");
        this.logger.log(Level.DEBUG, date4, "Log4Message");
        String log0 = "[ERROR]|" + date1.format(DateTimeFormatter.ISO_DATE_TIME) + "|bg.sofia.uni.fmi.mjt.logger|Log1Message\n";
        String log1 = "[WARN]|" + date2.format(DateTimeFormatter.ISO_DATE_TIME) + "|bg.sofia.uni.fmi.mjt.logger|Log2Message\n";
        String log2 = "[INFO]|" + date3.format(DateTimeFormatter.ISO_DATE_TIME) + "|bg.sofia.uni.fmi.mjt.logger|Log3Message\n";
        assertEquals(log0, Files.readString(
                        Path.of(this.options.getDirectory(), "logs-0.txt"), StandardCharsets.UTF_8),
                "File of 50B that can contain only one Log should contain that log");
        assertEquals(log1, Files.readString(
                        Path.of(this.options.getDirectory(), "logs-1.txt"), StandardCharsets.UTF_8),
                "File of 50B that can contain only one Log should contain that log");
        assertEquals(log2, Files.readString(
                        Path.of(this.options.getDirectory(), "logs-2.txt"), StandardCharsets.UTF_8),
                "File of 50B that can contain only one Log should contain that log");
        assertEquals(3, Objects.requireNonNull(Path.of(this.options.getDirectory()).toFile().list()).length,
                "Logger options of level INFO should log only files of Levels ERROR, WARN and INFO " +
                        "and because the log size is set to contain only one log, there should be only three files");
        clear();
    }

    @Test
    void testGetOptions() {
        assertEquals(this.options, this.logger.getOptions(), "Options should be the same");
    }
}
