const Author = require('./../models/author.model');
const Book = require('./../models/book.model');
class BookRepository {
    constructor() {
        this.seedRepo();
    }
    addBook(title, author, language, publisher, ISBN) {
        this.books.push(
            new Book(title, author, language, publisher, ISBN)
        );
    }
    addAuthor(firstName, lastName, DOB, gender) {
        let newId = this.authors[this.authors.length - 1].id + 1;
        let newAuthor = new Author(newId, firstName, lastName, DOB, gender);
        this.authors.push(newAuthor);
        return newAuthor;
    }
    getLanguage(lang) {
        let language = this.languages.find(l => l.abbrev === lang);
        return language && language.langName || 'unknown?';
    }
    getAuthor(id) {
        for (let a of this.authors) {
            if (a.id === id) return a;
        }
        return null;
    }
    /************ Seeding repo below: ****************/
    seedRepo() {
        this.seedAuthors();
        this.seedBooks();
        this.seedLanguages();
    }
    seedAuthors() {
        this.authors = [];
        this.authors.push(new Author(100, 'Steve', 'McConnel', new Date('1965-07-10'), 'm'));
        this.authors.push(new Author(101, 'Douglas', 'Crockford', new Date('1955-01-01'), 'm'));
        this.authors.push(new Author(201, 'Douglas', 'Adams', new Date('1952-03-11'), 'm'));
        this.authors.push(new Author(202, 'Sylvia', 'Plath', new Date('1932-10-27'), 'f'));
    }
    seedBooks() {
        this.books = [];
        this.addBook('Code Complete', this.getAuthor(100), 'en',
            'Microsoft Press; 2nd edition',
            '0735619670'
        );
        this.addBook('JavaScript: The Good Parts', this.getAuthor(101), 'en',
            `O'Reilly Media`,
            '9780596517748'
        );
        this.addBook(`The Hitchhiker's Guide to the Galaxy`, this.getAuthor(201), 'en',
            'Del Rey; Reissue edition',
            '1535185554'
        );
        this.addBook(`The Bell Jar`, this.getAuthor(202), 'en',
            'Harper Perennial Modern Classics;',
            '0060837020'
        );
    }
    seedLanguages() {
        this.languages = [{
            abbrev: "en",
            langName: "English"
        }, {
            abbrev: "hr",
            langName: "Croatian"
        }];
    }

}



const repoInstance = new BookRepository();

module.exports = repoInstance;