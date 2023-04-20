let firstOperandNumAdd = 1;
let secondOperandNumAdd = 2;
let resultNumAdd = firstOperandNumAdd + secondOperandNumAdd;
console.log(
  "Adding(+) two variables (vals: 1, 2) of Number type. Result: " +
    resultNumAdd +
    " #Variable type: " +
    typeof resultNumAdd
);

let firstOperandString = "1";
let secondOperandString = "2";
let resultString = firstOperandString + secondOperandString;
console.log(
  "Adding(+) two variable of String type (vals: 1, 2). Result: " +
    resultString +
    " #Variable type: " +
    typeof resultString
);

let firstOperandMixed = 1;
let secondOperandMixed = 2;
let thirdOperandMixed = "3";
let resultMixed = firstOperandMixed + secondOperandMixed + thirdOperandMixed;
console.log(
  "Adding(+) two variables of Number type (vals: 1, 2) and one of String type (val: 3). Result: " +
    resultMixed +
    " #Variable type: " +
    typeof resultMixed
);

let firstOperandNumberMixed2 = 1;
let secondOperandStringMixed2 = "3";
let resultSubtractionMixed2 =
  firstOperandNumberMixed2 - secondOperandStringMixed2;
console.log(
  "Subtracting(-) one variable of String type (val: 3) from one variable of Number type (val: 1). Result: " +
    resultSubtractionMixed2 +
    " #Variable type: " +
    typeof resultSubtractionMixed2
);

let firstOperandStringComp = "a";
let secondOperandStringComp = "A";
let resultStringComp = firstOperandStringComp > secondOperandStringComp;
console.log(
  "Comparing two variables of String type (vals: a, A) with >. Result: " +
    resultStringComp +
    " #Variable type: " +
    typeof resultStringComp
);

let firstOperandStringComp2 = "Java";
let secondOperandStringComp2 = "JavaScript";
let resultStringComp2 = firstOperandString > secondOperandString;
console.log(
  "Comparing two variables of String type (vals: Java, JavaScript) with >. Result: " +
    resultStringComp2 +
    " #Variable type: " +
    typeof resultStringComp2
);

let firstOperandMixComp = 1;
let secondOperandMixComp = "20";
let resultMixComp = firstOperandMixComp > secondOperandMixComp;
console.log(
  "Comparing one variable of Number type (val: 1) and one of String type (val: 20) with >. Result: " +
    resultMixComp +
    " #Variable type: " +
    typeof resultMixComp
);

let firstOperandBoolean = true;
let secondOperandNumber = 0;
let resultBoolNumComp = firstOperandBoolean != secondOperandNumber;
console.log(
  "Comparing one variable of Boolean type (val: true) and one of Number type (val: 0) with !=. Result: " +
    resultBoolNumComp +
    " #Variable type: " +
    typeof resultBoolNumComp
);

let firstOperand = 1;
let secondOperand = "1";
let resultNumString = firstOperand === secondOperand;
console.log(
  "Comparing one variable of Number type (val: 1) and one of String type (val: 1) with  ===. Result: " +
    resultNumString +
    " #Variable type: " +
    typeof resultNumString
);

let firstOperandBooleanCompOper = true;
let secondOperandNumberCompOper = 0;
let resultBoolNumCompOper =
  firstOperandBooleanCompOper !== secondOperandNumberCompOper;
console.log(
  "Comparing one variable of Boolean type (val: true) and one of Number type (val: 0) with !==. Result: " +
    resultBoolNumCompOper +
    " #Variable type: " +
    typeof resultBoolNumCompOper
);

let firstOperandAndOper = 1;
let secondOperandAndOper = 0;
let resultAndOper = firstOperandAndOper && secondOperandAndOper;
console.log(
  "Using && between two variables of Number type (vals: 1, 0). Result: " +
    resultAndOper +
    " #Variable type: " +
    typeof resultAndOper
);

let firstOperandOrOper = 1;
let secondOperandOrOper = 0;
let resultOrOper = firstOperandOrOper || secondOperandOrOper;
console.log(
  "Using || between two variables of Number type (vals: 1, 0). Result: " +
    resultOrOper +
    " #Variable type: " +
    typeof resultOrOper
);

let firstOperandNegNum = 1;
let resultNegNum = !firstOperandNegNum;
console.log(
  "Negating one variable of Number type (val: 1). Result: " +
    resultNegNum +
    " #Variable type: " +
    typeof resultNegNum
);

let firstOperandNegStr = "0";
let resultNegStr = !firstOperandNegStr;
console.log(
  "Negating one variable of String type (val: 0). Result: " +
    resultNegStr +
    " #Variable type: " +
    typeof resultNegStr
);

let t = 30;
let isBoilingTemp = t >= 100 ? true : false;
console.log(
  "Ternary operator (t >= 100) ? true : false for t=30: " + isBoilingTemp
);
