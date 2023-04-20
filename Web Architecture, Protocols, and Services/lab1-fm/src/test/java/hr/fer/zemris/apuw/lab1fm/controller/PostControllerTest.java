package hr.fer.zemris.apuw.lab1fm.controller;

import hr.fer.zemris.apuw.lab1fm.model.dto.CreateUpdatePostDTO;
import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@ExtendWith(SpringExtension.class)
class PostControllerTest {

    @Autowired
    PostController postController;

    @Autowired
    CommentController commentController;

    @Test
    @Order(1)
    void getPostsSize() {
        var posts = postController.getPosts().getBody();
        assertEquals(2, posts.size());
    }

    @Test
    @Order(2)
    void getPostsValue() {
        var posts = postController.getPosts().getBody();
        assertEquals("Kako je lijep i suncan dan!", posts.get(0).getPostText());
    }

    @Test
    @Order(3)
    void getPost() {
        var post = postController.getPost(1L).getBody();
        assertEquals(post.getPostId(), 1L);
        assertEquals("Kako je lijep i suncan dan!", post.getPostText());
        // komentari?
    }

    @Test
    @Order(4)
    void createPost() {
        CreateUpdatePostDTO dto = new CreateUpdatePostDTO();
        dto.setPostText("Novi post");
        Post post = postController.createPost(dto).getBody();

        assertNotNull(post);
        assertEquals(dto.getPostText(), post.getPostText());
        assertEquals(3L, post.getPostId());
        assertTrue(post.getComments().isEmpty());
    }

    @Test
    @Order(5)
    void updateExistingPost() {
        CreateUpdatePostDTO dto = new CreateUpdatePostDTO();
        dto.setPostText("Update post");
        var res = postController.updatePost(2L, dto);
        assertEquals(200, res.getStatusCode().value()); // OK

        Post post = postController.getPost(2L).getBody();
        assertNotNull(post);
        assertEquals(dto.getPostText(), post.getPostText());
    }

    @Test
    @Order(6)
    void updateNonExistingPost() {
        CreateUpdatePostDTO dto = new CreateUpdatePostDTO();
        dto.setPostText("Update post");
        var res = postController.updatePost(4L, dto);
        assertEquals(404, res.getStatusCode().value()); // NOT FOUND

        Post post = postController.getPost(4L).getBody();
        assertNull(post);
    }

    @Test
    @Order(7)
    void deletePost() {
        postController.deletePost(1L);
        Post post = postController.getPost(1L).getBody();
        assertNull(post);

        // should cascade delete
        Comment comment = commentController.getComment(1L).getBody();
        assertNull(comment);
    }
}