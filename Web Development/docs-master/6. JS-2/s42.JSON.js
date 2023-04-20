// Skip undefined and functions
let skip = { undef: undefined, func: () => {} };
console.log(JSON.stringify(skip));

// Circular
let a = { a: "a" };
let b = { a: a };
a.b = b;

console.log(JSON.stringify(a));