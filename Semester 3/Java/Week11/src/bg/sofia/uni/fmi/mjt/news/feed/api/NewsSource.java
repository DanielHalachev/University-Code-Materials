package bg.sofia.uni.fmi.mjt.news.feed.api;

import java.util.Objects;

// the class, which would represent the source object of an article
public class NewsSource {

    private final String id;
    private final String name;

    public NewsSource(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        NewsSource that = (NewsSource) o;
        return getId().equals(that.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }
}
