package hr.fer.zemris.apuw.lab1fm.service;

import hr.fer.zemris.apuw.lab1fm.model.entity.Comment;
import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
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
public class PostService {
    private PostRepository postRepository;

    @Transactional
    public List<Post> getPosts() {return this.postRepository.findAll();}

    @Transactional
    public Integer updatePost(Long postId, String postText) {
        return this.postRepository.setPostById(postId, postText);
    }

    @Transactional
    public void deletePost(Long postId) {
        this.postRepository.deleteById(postId);
    }

    @Transactional
    public Post createPost(String postText) {
        Post post = new Post();
        post.setPostText(postText);
        post = this.postRepository.save(post);

        log.info(String.valueOf(post));
        return post;
    }

    public Optional<Post> getPost(Long postId) {
        return this.postRepository.findById(postId);
    }
}
