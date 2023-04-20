function doubleErr(value) {
  value *= 2;
}

let result = doubleErr(4);
console.log(result);

function addNoValue2(value1, value2) {
  console.log(value1);
  console.log(value2);
  let result = value1 + value2;
  return result;
}
//regular function call
let resultAdd = addNoValue2(1);
console.log(resultAdd);

function addDefault(value1, value2 = 0) {
  let result = value1 + value2;
  return result;
}
//function call with one parameter taking defaultValue
let resultAddDefault = addDefault(1);
console.log(resultAddDefault);

function getDefault() {
  return 0;
}
function add(value1, value2 = getDefault()) {
  let result = value1 + value2;
  return result;
}
//function call with one parameter taking defaultValue from a function
resultDefFunc = add(1);
console.log(resultDefFunc);

let double = function (value) {
  return value * 2;
};
let square = function (value) {
  return value * value;
};
function changeArray(array, changeFunction) {
  for (let i = 0; i < array.length; i++) {
    array[i] = changeFunction(array[i]);
  }
  return array;
}
let doubleArray = changeArray([1, 2, 3, 4], double);
console.log(
  "Array [1,2,3,4] after call to changeArray with the double function as parameter. Result: " +
    doubleArray
);
let squareArray = changeArray([1, 2, 3, 4], square);
console.log(
  "Array [1,2,3,4] after call to changeArray with the square function as parameter. Result: " +
    squareArray
);

let doubleArrayAnn = changeArray([1, 2, 3, 4], function (value) {
  return value * 2;
});
console.log(
  "Array [1,2,3,4] after call to changeArray with the _anonymous_ double function as parameter. Result: " +
    doubleArrayAnn
);
let squareArrayAnn = changeArray([1, 2, 3, 4], function (value) {
  return value ** 2;
});
console.log(
  "Array [1,2,3,4] after call to changeArray with the _anonymous_ square function as parameter. Result: " +
    squareArrayAnn
);

let squareLambda = (value) => value * value;

console.log(square.prototype);
