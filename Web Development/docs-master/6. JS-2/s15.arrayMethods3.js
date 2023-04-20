let persons = ["Mark", "John", "Joe"];

persons.forEach(person => {
    console.log(person);
});
// Output:
// "Mark"
// "John"
// "Joe"


console.log(persons.map(person => { 
    console.log(person.split("o"));
}));
// Output:
// ["Mark"]
// ["J", "hn"]
// ["J", "e"]

console.log(persons.join("=>"));
// "Mark => John => Joe"
