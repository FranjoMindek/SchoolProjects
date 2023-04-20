const AuthorClass =
    class Author {
        constructor(id, firstName, lastName, DOB, gender) {
            this.id = id;
            this.firstName = firstName;
            this.lastName = lastName;
            this.DOB = DOB;
            this.gender = gender;
        }
        get age() {
            return (new Date()).getFullYear() - this.DOB.getFullYear();
        }
        get formattedAuthor() {
            return ((this.gender == 'm') ? 'Mr. ' : 'Mrs.') +
                this.firstName +
                ' ' + this.lastName +
                ` (${this.age})`;
        }
    };
AuthorClass.prototype.toString = function() {
    return this.formattedAuthor;
}
module.exports = AuthorClass;