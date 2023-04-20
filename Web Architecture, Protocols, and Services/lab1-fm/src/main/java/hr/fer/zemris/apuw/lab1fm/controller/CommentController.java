package hr.fer.zemris.apuw.lab1fm.controller;

import hr.fer.zemris.apuw.lab1fm.model.dto.CreateUpdateCommentDTO;
import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import hr.fer.zemris.apuw.lab1fm.service.CommentService;
import lombok.AllArgsConstructor;
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
public class CommentController {
    private CommentService commentService;

    @GetMapping("comments")
    public ResponseEntity<List<Comment>> getComments() {
        return new ResponseEntity<>(this.commentService.getComments(), HttpStatus.OK);
    }

    @GetMapping("comments/{commentId}")
    public ResponseEntity<Comment> getComment(@PathVariable Long commentId) {
        Optional<Comment> commentOptional = this.commentService.getComment(commentId);
        return commentOptional.map(comment -> new ResponseEntity<>(comment, HttpStatus.OK)).orElseGet(() -> new ResponseEntity<>(null, HttpStatus.NOT_FOUND));
    }

    @GetMapping("posts/{postId}/comments")
    public ResponseEntity<List<Comment>> getCommentsByPostId(@PathVariable Long postId) {
        return new ResponseEntity<>(this.commentService.getCommentsByPostId(postId), HttpStatus.OK);
    }

    @PostMapping("posts/{postId}/comments")
    public ResponseEntity<Comment> createComment(@PathVariable Long postId, @RequestBody CreateUpdateCommentDTO commentDTO) {
        Comment comment = this.commentService.createComment(postId, commentDTO.getCommentText());

        HttpHeaders headers = new HttpHeaders();
        headers.setLocation(URI.create("http://localhost:8080/api/comments/" + comment.getCommentId()));

        return new ResponseEntity<>(comment, headers, HttpStatus.CREATED);
    }

    @PutMapping("comments/{commentId}")
    public ResponseEntity<?> updateComment(@PathVariable Long commentId, @RequestBody CreateUpdateCommentDTO commentDTO) {
        Integer rowsUpdated = this.commentService.updateComment(commentId, commentDTO.getCommentText());
        if (rowsUpdated.equals(0)) return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @DeleteMapping("comments/{commentId}")
    public ResponseEntity<?>  deleteComment(@PathVariable Long commentId) {
        this.commentService.deleteComment(commentId);
        return new ResponseEntity<>(HttpStatus.OK);
    }

}



//    @PostMapping("comments")
//    public ResponseEntity<Comment> createComment(@RequestBody CreateCommentDTO commentDTO) {
//        Comment comment = this.commentService.createComment(commentDTO);
//
//        HttpHeaders headers = new HttpHeaders();
//        headers.setLocation(URI.create("http://localhost:8080/api/comments/" + comment.getCommentId()));
//
//        return new ResponseEntity<>(comment, headers, HttpStatus.OK);
//    }
