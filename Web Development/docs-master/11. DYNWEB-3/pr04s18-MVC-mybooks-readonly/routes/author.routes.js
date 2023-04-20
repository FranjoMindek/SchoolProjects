var express = require('express');
var router = express.Router();
const repo = require('../repository/books.repo');

// S ([0-9]{1,10}) ćemo se dodatno osigurati da je id 1-10 znamenkasti broj.
router.get('/:id([0-9]{1,10})', function(req, res, next) {
    let id = parseInt(req.params.id);
    let author;
    for (let book of repo.books) {
        if (book.author.id === id) {
            author = book.author;
            break;
        }
    }
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

module.exports = router;