let object1 = new Object();
let object2 = {};

let person = {
  OIB: "12345678912345",
  name: "Pero",
  surname: "Perić",
  "home city": "Zagreb",
  sex: "M",
};

person.age = 20;
console.log(person.age);
delete person.age;
console.log(person.age);

person["home city"] = "Osijek";
let homeCityProp = "home city";
person[homeCityProp] = "Split";

let nationality = "Croatian";
let personExtended = {
  OIB: "12345678912345",
  name: "Pero",
  surname: "Perić",
  "home city": "Zagreb",
  nationality,
};

console.log(personExtended.nationality);
nationality = "German";
console.log(personExtended.nationality);

let existsNationality = personExtended.nationality !== undefined;
let existsNationality2 = "nationality" in personExtended;

console.log("Printing all properties of the personExtended variable:");
for (let key in personExtended) {
  console.log(
    "Key: " +
      key +
      " Value: " +
      personExtended[key] +
      " Type: " +
      typeof personExtended[key]
  );
}

let simpleAssignment = person;
let personClone = Object.assign({}, person);

let person1 = {
  OIB: "12345678912345",
  name: "Pero",
  surname: "Perić",
};

console.log(person1);
for (let value of Object.values(person1)) {
  console.log(value);
}

let person2 = {
  OIB: "12345678912346",
  name: "Krešo",
  surname: "Kumek",
};

let allPersons = {
  firstPerson: person1,
  secondPerson: person2,
};
person1 = null;
person2 = null;
allPersons = null;

let OIBvalue1 = "123";
let OIBvalue2 = "1234";
let propName1 = "OIB";
let propName2 = "OIB";
person1 = {};
person1[propName1] = OIBvalue1;
person1[propName2] = OIBvalue2;
let propNameSymbol1 = Symbol("OIB");
let propNameSymbol2 = Symbol("OIB");
person2 = {};
person2[propNameSymbol1] = OIBvalue1;
person2[propNameSymbol2] = OIBvalue2;
console.log("Printing person1[propName1]: " + person1[propName1]);
console.log("Printing person1[propName2]: " + person1[propName2]);
console.log("Printing person2[propNameSymbol1]: " + person2[propNameSymbol1]);
console.log("Printing person2[propNameSymbol2]: " + person2[propNameSymbol2]);
