package hr.fer.zemris.apuw.lab1fm.repository;

import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

@Repository
public interface PostRepository extends JpaRepository<Post, Long> {

    @Modifying
    @Query("UPDATE Post p SET p.postText = ?2 WHERE p.postId = ?1")
    Integer setPostById(Long commentId, String commentText);
}
