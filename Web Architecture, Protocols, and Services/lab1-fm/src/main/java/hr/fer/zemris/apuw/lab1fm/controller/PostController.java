package hr.fer.zemris.apuw.lab1fm.controller;

import hr.fer.zemris.apuw.lab1fm.model.dto.CreateUpdateCommentDTO;
import hr.fer.zemris.apuw.lab1fm.model.dto.CreateUpdatePostDTO;
import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
import hr.fer.zemris.apuw.lab1fm.repository.PostRepository;
import hr.fer.zemris.apuw.lab1fm.service.PostService;
import lombok.AllArgsConstructor;
import lombok.Getter;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.net.URI;
import java.util.List;
import java.util.Optional;

@AllArgsConstructor
@RestController
@RequestMapping("api/")
public class PostController {
    private PostService postService;

    @GetMapping("posts")
    public ResponseEntity<List<Post>> getPosts() {
        return new ResponseEntity<>(this.postService.getPosts(), HttpStatus.OK);
    }

    @GetMapping("posts/{postId}")
    public ResponseEntity<Post> getPost(@PathVariable Long postId) {
        Optional<Post> postOptional = this.postService.getPost(postId);
        return postOptional.map(post -> new ResponseEntity<>(post, HttpStatus.OK)).orElseGet(() -> new ResponseEntity<>(null, HttpStatus.NOT_FOUND));
    }

    @PostMapping("posts")
    public ResponseEntity<Post> createPost(@RequestBody CreateUpdatePostDTO postDTO) {
        Post post = this.postService.createPost(postDTO.getPostText());

        HttpHeaders headers = new HttpHeaders();
        headers.setLocation(URI.create("http://localhost:8080/api/posts/" + post.getPostId()));

        return new ResponseEntity<>(post, headers, HttpStatus.CREATED);
    }

    @PutMapping("posts/{postId}")
    public ResponseEntity<?> updatePost(@PathVariable Long postId, @RequestBody CreateUpdatePostDTO postDTO) {
        Integer rowsUpdated = this.postService.updatePost(postId, postDTO.getPostText());
        if (rowsUpdated.equals(0)) return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @DeleteMapping("posts/{postId}")
    public ResponseEntity<?> deletePost(@PathVariable Long postId) {
        this.postService.deletePost(postId);
        return new ResponseEntity<>(HttpStatus.OK);
    }

}
