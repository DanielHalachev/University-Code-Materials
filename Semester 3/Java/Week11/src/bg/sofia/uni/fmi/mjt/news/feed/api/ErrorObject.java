package bg.sofia.uni.fmi.mjt.news.feed.api;

// a class, which would represent the object, returned by the server in case of a failed request
public class ErrorObject {

    public static final String API_KEY_DISABLED = "apiKeyDisabled";
    public static final String API_KEY_MISSING = "apiKeyMissing";
    public static final String API_KEY_EXHAUSTED = "apiKeyExhausted";
    public static final String API_KEY_INVALID = "apiKeyInvalid";
    public static final String PARAMETER_INVALID = "parameterInvalid";
    public static final String PARAMETERS_MISSING = "parametersMissing";
    public static final String RATE_LIMITED = "rateLimited";
    public static final String SOURCES_TOO_MANY = "sourcesTooMany";
    public static final String SOURCE_DOES_NOT_EXIST = "sourceDoesNotExist";
    public static final String UNEXPECTED_ERROR = "unexpectedError";

    private final String status;
    private final String code;
    private final String message;

    public ErrorObject(String status, String code, String message) {
        this.status = status;
        this.code = code;
        this.message = message;
    }

    public String getStatus() {
        return status;
    }

    public String getCode() {
        return code;
    }

    public String getMessage() {
        return message;
    }
}
