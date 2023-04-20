let persons = ["Mark", "John", "Joe"];

persons.push("Zack"); 
// persons = ["Mark", "John", "Joe", "Zack"]

console.log(persons.pop()); // "Zack" is removed for array
console.log(persons.shift()); // "Mark" is removed from array
console.log(persons.unshift("Mark", "Zack")); 
// output: ["Mark", "Zack", "John", "Joe"]


console.log(persons.slice(1, 3)); // ["Zack", "John"]
console.log(persons.splice(1, 1)); // ["Zack"]
console.log(persons); // ["Mark", "John", "Joe"]

console.log(persons.splice(1, 1, "Travis", "Bill")); // ["John"]
console.log(persons); // ["Mark", "Travis", "Bill" "Joe"]



