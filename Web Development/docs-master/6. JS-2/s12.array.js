let persons = ["Mark", "John", "Joe"];

persons[2] = "Susan";
persons[1] = function() { console.log("Hello from an array!") };
persons[1]();

for (let person of persons) {
  console.log(person); 
}