var express = require('express');
var router = express.Router();
const repo = require('../repository/books.repo');
const {
    check,
    body,
    validationResult
} = require('express-validator');

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
    let model = {
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
    console.log(JSON.stringify(model, undefined, 2));
    res.render('addBook', model);
});


router.post('/add', [
    body('title')
    .not().isEmpty()
    .trim()
    .escape(),
    body('author')
    .not().isEmpty()
    .toInt(),
    check('language')
    .trim()
    .isLength({
        min: 2,
        max: 2
    }),
    body('publisher')
    .not().isEmpty()
    .trim()
    .escape(),
    body('ISBN')
    .not().isEmpty()
    .trim()
    .custom(value => {
        return validateISBN(value)
    }).withMessage('ISBN must be a 10 or 13 digit number that confirms to the standard: https://en.wikipedia.org/wiki/International_Standard_Book_Number')
], function (req, res, next) {
    const errors = validationResult(req);
    if (!errors.isEmpty()) {
        // res.status(422).send(
        //     JSON.stringify(errors.array())
        // );
        res.render('addBook', {
            title: "Add book (error)",
            error: JSON.stringify(errors.array())
        });
    } else {
        console.log(req.body);
        try {
            let newBook = repo.addBook(
                req.body.title,
                repo.getAuthor(req.body.author),
                req.body.language,
                req.body.publisher,
                req.body.ISBN
            );
            res.redirect('/books');
        } catch (err) {
            res.render('addBook', {
                title: "Add book",
                error: JSON.stringify(err)
            });
        }
    }
});

// Napravio https://repl.it/@mekterovic/LovelySilkyGame tko se hoće igrati
function validateISBN(ISBN) {
    if (ISBN) {
        console.log('validating ', ISBN);
        let sum = 0;
        if (ISBN.length === 10) {
            for (let i = 0; i < 9; ++i) {
                sum += parseInt(ISBN.charAt(i)) * (10 - i);
            }
            if ((sum % 11 === 10 && ISBN.charAt(9) === 'X') ||
                sum % 11 == parseInt(ISBN.charAt(9))) {
                return true;
            }
        } else if (ISBN.length === 13) {
            for (let i = 0; i < 12; ++i) {
                sum += parseInt(ISBN.charAt(i)) * (i % 2 ? 3 : 1);
            }
            let cd = sum % 10 == 0 ? 0 : 10 - sum % 10;
            if (cd == parseInt(ISBN.charAt(12))) {
                return true;
            }
        }
    }
    return false;
}



module.exports = router;