package hr.fer.zemris.apuw.lab1fm.model.entity;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import jakarta.persistence.*;
import lombok.*;
import org.hibernate.Hibernate;

import java.util.Objects;

@Entity
@Getter
@Setter
@NoArgsConstructor
public class Comment {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Setter(AccessLevel.NONE)
    private Long commentId;

    @Column(nullable = false)
    private String commentText;

    @JsonIgnoreProperties({"hibernateLazyInitializer", "handler", "comments"})
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "post_post_id", nullable = false)
    private Post post;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        Comment that = (Comment) o;
        return commentId != null && Objects.equals(this.commentId, that.commentId);
    }

    @Override
    public int hashCode() {
        return getClass().hashCode();
    }

    @Override
    public String toString() {
        return commentText;
    }

}
