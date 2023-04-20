let personMap = new Map([
  [1, "Mark"],
  [2, "John"],
  [3, "Joe"]
]);

personMap.set(4, "Mary");
personMap.delete(2);

for (let personKey of personMap.keys()) {
  console.log(personKey); 
}

for (let personValue of personMap.values()) {
  console.log(personValue); 
}