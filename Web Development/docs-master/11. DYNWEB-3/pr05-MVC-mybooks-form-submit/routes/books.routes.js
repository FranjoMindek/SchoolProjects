var express = require('express');
var router = express.Router();
const repo = require('../repository/books.repo');


// Primijentite da je ovo ukupni "/books" path jer je ova ruta 
// mapirana na /books u server.js
router.get('/', function (req, res, next) {
    res.render('books', {
        title: 'My books',
        books: repo.books,
        repo: repo
    });
});

router.get('/add', function (req, res, next) {
    let model =  {
        title: 'Add book',
        authorsSelect: {
            name: "author",
            list: repo.authors.map(x => ({
                value: x.id,
                name: x.toString()
            }))
        },
        languagesSelect: {
            name: "language",
            list: repo.languages.map(x => ({
                value: x.abbrev,
                name: x.langName
            })),
            selected: "en"
        }
    };
    console.log(JSON.stringify(model,undefined,2));
    res.render('addBook', model);
});


router.post('/add', function (req, res, next) {
    console.log(req.body);
    try {
        let newBook = repo.addBook(
            req.body.title,
            repo.getAuthor(parseInt(req.body.author)),
            req.body.language,
            req.body.publisher,
            req.body.ISBN
        );
        res.redirect('/books');
    } catch (err) {
        res.render('addBook', {
            title: "Add books",
            error: JSON.stringify(err)
        });
    }

});

module.exports = router;