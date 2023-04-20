package hr.fer.zemris.apuw.lab1fm.controller;

import hr.fer.zemris.apuw.lab1fm.model.entity.Post;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class DocumentationController {
    @GetMapping("/")
    public ResponseEntity<?> returnDocumentation() {
        String documentation = """
                <p>
                    Dokumentacija za 1. labos iz APUW:
                </p>
                <p>
                    Dostupan je API za 2 vrste resursa to su objave (posts) i komentari (comments).
                </p>
                <p>
                    Svi pozivi prema API-ju imaju prefix 'api/'
                </p>
                <p>
                    Posts:
                    <ul>
                        <li>
                            <p>GET api/posts</p>
                            <p>Dohvaca sve objace</p>
                        </li>
                        <li>
                            <p>GET api/posts/{postId}</p>
                            <p>Dobaca objavu preko ID-ja</p>
                        </li>
                        <li>
                            <p>POST api/posts</p>
                            <p>Stvara novu objavu</p>
                        </li>
                        <li>
                            <p>PUT api/posts/{postId}</p>
                            <p>Azurira postojecu objavu (ne omogucujemo PUT stvaranje)</p>
                        </li>
                        <li>
                            <p>DELETE api/posts/{postId}</p>
                            <p>Brise postojecu objavu</p>
                        </li>
                    </ul>
                </p>
                <p>
                    Comments:
                    <ul>
                        <li>
                            <p>GET api/comments</p>
                            <p>Dohvaca sve komentare</p>
                        </li>
                        <li>
                            <p>GET api/comments/{commentId}</p>
                            <p>Dohvaca komentar preko ID-ja</p>
                        </li>
                        <li>
                            <p>GET api/posts/{postId}/comments</p>
                            <p>Dohvaca sve komentare objave</p>
                        </li>
                        <li>
                            <p>POST api/posts/{postId}/comments</p>
                            <p>Stvara novi komentar</p>
                        </li>
                        <li>
                            <p>PUT api/comments/{commentId}</p>
                            <p>Azurira postojeci komentar (ne omogucuje PUT stvaranje)</p>
                        </li>
                        <li>
                            <p>DELETE api/comments/{commentId}</p>
                            <p>Brise postojeci komentar</p>
                        </li>
                    </ul>
                </p>
                """;
        return new ResponseEntity<>(documentation, HttpStatus.OK);
    }
}
