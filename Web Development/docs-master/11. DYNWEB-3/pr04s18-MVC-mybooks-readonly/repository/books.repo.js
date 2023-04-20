const Author = require('./../models/author.model');
const Book = require('./../models/book.model');
class BookRepository {
    constructor() {
        this.books = [];
        this.seedBooks();
    }
    seedBooks() {
        this.books.push(
            new Book('Code Complete',
                new Author(100, 'Steve', 'McConnel', new Date('1965-07-10'), 'm'), "English",
                'Microsoft Press; 2nd edition',
                '0735619670'
            ));
        this.books.push(
            new Book('JavaScript: The Good Parts',
                new Author(101, 'Douglas', 'Crockford', new Date('1955-01-01'), 'm'), "English",
                `O'Reilly Media`,
                '9780596517748'
            ));
        this.books.push(
            new Book(`The Hitchhiker's Guide to the Galaxy`,
                new Author(201, 'Douglas', 'Adams', new Date('1952-03-11'), 'm'), "English",
                'Del Rey; Reissue edition',
                '1535185554'
            ));
        this.books.push(
            new Book(`The Bell Jar`,
                new Author(202, 'Sylvia', 'Plath', new Date('1932-10-27'), 'f'), "English",
                'Harper Perennial Modern Classics;',
                '0060837020'
            ));
    }
}



const repoInstance = new BookRepository();

module.exports = repoInstance;