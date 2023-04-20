package hr.fer.zemris.apuw.lab1fm.service;

import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
import hr.fer.zemris.apuw.lab1fm.repository.CommentRepository;
import hr.fer.zemris.apuw.lab1fm.repository.PostRepository;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
@Slf4j
public class CommentService {
    private CommentRepository commentRepository;
    private PostRepository postRepository;

    @Transactional
    public List<Comment> getComments() {
        return this.commentRepository.findAll();
    }

    @Transactional
    public Optional<Comment> getComment(Long commentId) {
        return this.commentRepository.findById(commentId);
    }

    @Transactional
    public List<Comment> getCommentsByPostId(Long postId) {
        Optional<Post> post = this.postRepository.findById(postId);
        List<Comment> list = null;
        if (post.isPresent()) list = post.get().getComments();
        return list;
    }

    @Transactional
    public Comment createComment(Long postId, String commentText) {
        Post parentPost = postRepository.getReferenceById(postId);

        Comment comment = new Comment();
        comment.setCommentText(commentText);
        comment.setPost(parentPost);
        comment = this.commentRepository.save(comment);

        log.info(String.valueOf(comment));
        return comment;
    }

    @Transactional
    public Integer updateComment(Long commentId, String commentText) {
        return this.commentRepository.setCommentById(commentId, commentText);
    }

    @Transactional
    public void deleteComment(Long commentId) {
        this.commentRepository.deleteById(commentId);
    }

}
