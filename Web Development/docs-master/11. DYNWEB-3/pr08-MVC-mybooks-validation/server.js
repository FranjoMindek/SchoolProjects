const express = require('express');
const app = express();
var path = require('path');

const homeRouter = require('./routes/home.routes');
const booksRouter = require('./routes/books.routes');
const authorsRouter = require('./routes/authors.routes');

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(express.static(path.join(__dirname, 'public')));

app.use(express.urlencoded({ extended: true }));
app.use('/', homeRouter);
app.use('/books', booksRouter);
app.use('/authors', authorsRouter);


app.listen(3000);