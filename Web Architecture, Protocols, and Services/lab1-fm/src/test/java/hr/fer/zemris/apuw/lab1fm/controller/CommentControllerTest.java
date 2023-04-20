package hr.fer.zemris.apuw.lab1fm.controller;

import hr.fer.zemris.apuw.lab1fm.model.dto.CreateUpdateCommentDTO;
import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import org.assertj.core.api.Assertions;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit.jupiter.SpringExtension;

@SpringBootTest()
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@ExtendWith(SpringExtension.class)
class CommentControllerTest {

    @Autowired
    private CommentController commentController;

    @Test
    @Order(1)
    void getCommentsSize() {
        var comments = commentController.getComments();
        Assertions.assertThat(comments.getBody()).hasSize(3);
    }

    @Test
    @Order(2)
    void getCommentsValue() {
        var comments = commentController.getComments();
        Assertions.assertThat(comments.getBody().get(0).getCommentText()).isEqualTo("Bome puno sunca ima!");
    }

    @Test
    @Order(3)
    void getComment() {
        var comment = commentController.getComment(3L);
        var commentBody = comment.getBody();
        Assertions.assertThat(commentBody.getCommentId()).isEqualTo(3L);
        Assertions.assertThat(commentBody.getCommentText()).isEqualTo("Ja najvise ljesnjak volim!");
    }

    @Test
    @Order(4)
    void getCommentsByPostId() {
        var comments = commentController.getCommentsByPostId(2L).getBody();
        Assertions.assertThat(comments).hasSize(2);
    }

    @Test
    @Order(5)
    void createComment() {
        CreateUpdateCommentDTO dto = new CreateUpdateCommentDTO();
        dto.setCommentText("Testiram!");
        var response = commentController.createComment(1L, dto);

        Comment comment = commentController.getComment(response.getBody().getCommentId()).getBody();
        Assertions.assertThat(comment).isNotNull();
        Assertions.assertThat(comment.getCommentText()).isEqualTo("Testiram!");
    }

    @Test
    @Order(6)
    void updateComment() {
        CreateUpdateCommentDTO dto = new CreateUpdateCommentDTO();
        dto.setCommentText("Novo");
        commentController.updateComment(1L, dto);

        Comment comment = commentController.getComment(1L).getBody();
        Assertions.assertThat(comment.getCommentText()).isEqualTo("Novo");
    }

    @Test
    @Order(7)
    void deleteComment() {
        commentController.deleteComment(2L);

        Comment comment = commentController.getComment(2L).getBody();
        Assertions.assertThat(comment).isNull();
    }
}