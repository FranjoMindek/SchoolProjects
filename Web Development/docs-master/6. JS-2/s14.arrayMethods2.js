let persons = ["Mark", "John", "Joe"];

console.log(persons.concat("Zack")); // ["Mark", "John", "Joe", "Zack"]
console.log(persons.indexOf("Joe")); // 2
console.log(persons.includes("Zack")); // false

console.log(persons.filter(person => person.includes("o"))); // ["John", "Joe"]
console.log(persons.findIndex(person => person.includes("o"))); // 1