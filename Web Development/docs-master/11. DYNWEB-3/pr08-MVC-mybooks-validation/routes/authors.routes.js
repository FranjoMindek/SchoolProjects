var express = require('express');
var router = express.Router();
const repo = require('../repository/books.repo');


router.get('/', function(req, res, next) {
    res.render('authors', {
        title: 'List of authors',
        authors: repo.authors
    });
});

// S ([0-9]{1,10}) ćemo se dodatno osigurati da je id 1-10 znamenkasti broj.
router.get('/:id([0-9]{1,10})', function(req, res, next) {
    let id = parseInt(req.params.id);
    let author = repo.getAuthor(id);
    if (author) {
        res.render('author', {
            title: 'Info for ' + author,
            author: author
        });
    } else {
        res.status(404)
            .send("Are you guessing?");
    }
});
router.get('/add', function(req, res, next) {
    res.render('addAuthor', { title: "Add author" });
});
router.post('/add', function(req, res, next) {
    console.log(req.body);
    try {
        let newAuthor = repo.addAuthor(
            req.body.firstName,
            req.body.lastName,
            new Date(req.body.DOB),
            req.body.gender
        );
        res.redirect('/authors');
    } catch (err) {
        res.render('addAuthor', {
            title: "Add author",
            error: JSON.stringify(err)
        });
    }

});
module.exports = router;