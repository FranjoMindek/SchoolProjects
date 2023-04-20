package hr.fer.zemris.apuw.lab1fm.repository;


import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

@Repository
public interface CommentRepository extends JpaRepository<Comment, Long> {

    @Modifying
    @Query("UPDATE Comment c SET c.commentText = ?2 WHERE c.commentId = ?1")
    Integer setCommentById(Long commentId, String commentText);
}
