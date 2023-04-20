console.log("1");
setTimeout(() => {
    console.log("2");
}, 1000);
console.log("3");


console.log("A");
setTimeout(() => {
    console.log("B");
}, 0);
console.log("C");