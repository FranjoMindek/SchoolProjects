let person = {
  OIB: "12345678912345",
  name: "Pero",
  surname: "Perić",
  "home city": "Zagreb"
};
personJSON = JSON.stringify(person);
console.log(personJSON);
let personFromJSON = JSON.parse(personJSON);