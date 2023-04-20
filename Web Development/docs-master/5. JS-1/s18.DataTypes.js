let numPeople = 32;
numPeople = "Thirty two";
let numCars = 12;
let taxRate = 0.25;
const bigInt = 49875894375984375437534987439857938457594375984374839075483975743987534958n;
let doubleQuotes = "String 1";
let singleQuotes = "String 2";

let backTickQuotes = `value plus tax amounts to ${1000 * 1.25}`;
console.log(
  "String 'value plus tax amounts to ' with an expression ${1000 * 1.25}:" +
    backTickQuotes +
    " #Result type: " +
    typeof backTickQuotes
);

let isCompleted = true;
let hasStopped = false;
let currentTime = null;

let undefinedVariable;
console.log(
  "Undefined variable printed: " +
    undefinedVariable +
    " #Result type: " +
    typeof undefinedVariable
);

let currentTemperature = 22;
currentTemperature = undefined;
console.log(
  "A variable set to undefined value print: " +
    currentTemperature +
    " #Result type: " +
    typeof currentTemperature
);
console.log(
  "Boolean variable (val: true) printed: " +
    isCompleted +
    " #Result type: " +
    typeof isCompleted
);

let firstOperand = "1";
let secondOperand = "3";
console.log(
  "Two strings (vals: 1 and 3) multiplied with *: " +
    firstOperand * secondOperand +
    " #Result type: " +
    typeof (firstOperand * secondOperand)
);

let isCompletedString = "1";
let isCompletedBoolean = Boolean(isCompletedString);
console.log(
  "String (val: 1) converted to Boolean, then printed: " +
    isCompletedBoolean +
    " #Result type: " +
    typeof isCompletedBoolean
);
let isCompletedNumber = Number(isCompletedString);
console.log(
  "String (val: 1) converted to Number, then printed: " +
    isCompletedNumber +
    " #Result type: " +
    typeof isCompletedBoolean
);
let isCompletedStringNaN = "1abc";
let isCompletedNumberNaN = Number(isCompletedStringNaN);
console.log(
  "String (val: 1abc) converted to Number ends as NaN, then printed: " +
    isCompletedNumberNaN +
    " #Result type: " +
    typeof isCompletedNumberNaN
);
