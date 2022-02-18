package bg.sofia.uni.fmi.mjt.logger;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DefaultLogger implements Logger {

    private final LoggerOptions loggerOptions;
    private int counter = 0;

    public DefaultLogger(LoggerOptions options) {
        this.loggerOptions = options;
    }

    public boolean verifySize() {
        return !(this.getCurrentFilePath().toFile().length() >=
                this.loggerOptions.getMaxFileSizeBytes());
    }

    Path generateDestination() {
        if (this.getCurrentFilePath().toFile().exists() && !verifySize()) {
            this.counter++;
        }
        return Path.of(this.loggerOptions.getDirectory(), ("logs-" + counter + ".txt"));
    }

    @Override
    public void log(Level level, LocalDateTime timestamp, String message) {
        if (level == null || timestamp == null || message == null) {
            throw new IllegalArgumentException("One of the parameters is null");
        }
        if (message.equals("")) {
            throw new IllegalArgumentException("Message is empty");
        }
        if (this.loggerOptions.getMinLogLevel().compareTo(level) < 0) {
            return;
        }
        if (this.loggerOptions.getDirectory() == null) {
            throw new LogException("Directory is null");
        }
        Path.of(this.loggerOptions.getDirectory()).toFile().mkdirs();
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(generateDestination().toFile(), true))) {
            final char separator = '|';
            String str = "[" + level + "]" + separator +
                    timestamp.format(DateTimeFormatter.ISO_DATE_TIME) + separator +
                    loggerOptions.getClazz().getPackageName() + separator +
                    message + System.lineSeparator();
            writer.write(str);
            writer.flush();
        } catch (Exception e) {
            if (this.loggerOptions.shouldThrowErrors()) {
                throw new LogException("Operation was not successful", e);
            }
        }
    }

    @Override
    public LoggerOptions getOptions() {
        return this.loggerOptions;
    }

    @Override
    public Path getCurrentFilePath() {
        return Path.of(this.loggerOptions.getDirectory(), "logs-" + counter + ".txt");
    }
}
