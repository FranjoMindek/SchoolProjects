var express = require('express');
var router = express.Router();
const repo = require('../repository/books.repo');


// Primijentite da je ovo ukupni "/books" path jer je ova ruta 
// mapirana na /books u server.js
router.get('/', function(req, res, next) {
    res.render('books', {
        title: 'My books',
        books: repo.books
    });
});

module.exports = router;