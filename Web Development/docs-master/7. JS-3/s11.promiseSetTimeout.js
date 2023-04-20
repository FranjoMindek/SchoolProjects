let promise = new Promise(function(resolve, reject) {
    setTimeout(() => {        
        console.log("After 3 seconds - from the promise"); 
        resolve("After 3 seconds - msg from promise to then")
    }, 
    3000);
});
promise.then(
  function(result) { console.log(result) },
  function(error) { /* handle an error */ }
);
console.log("Program continues with other tasks...");