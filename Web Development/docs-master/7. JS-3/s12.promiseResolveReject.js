let promise = new Promise(function(resolve, reject){
    let randomNumber = Math.floor(Math.random() * 10);
    console.log(randomNumber);
    if(randomNumber%2==1){
        setTimeout(() => {
           resolve("An odd random number was generated."); 
        }, 5000);
    }
    else{
        setTimeout(() => {
           reject("An even random number was generated."); 
        }, 1000);
    }
});

/*
promise.then(
    function(){ console.log("This appears if resolve is called!");},
    function(){ console.log("This appears if reject is called!");}
);

promise = new Promise(function(resolve, reject){
    let randomNumber = Math.floor(Math.random() * 10);
    console.log(randomNumber);
    if(randomNumber%2==1){
        setTimeout(() => {
           resolve("An odd random number was generated."); 
        }, 5000);
    }
    else{
        setTimeout(() => {
           reject(new Error("This is generated from the promise executor!")); 
        }, 1000);
    }
});

promise.catch(
    function(error){ console.log(error);}
);

*/
promise = new Promise(function(resolve, reject){
    let randomNumber = Math.floor(Math.random() * 10);
    console.log(randomNumber);
    if(randomNumber%2==1){
        setTimeout(() => {
           resolve("An odd random number was generated."); 
        }, 5000);
    }
    else{
        setTimeout(() => {
           reject(new Error("This is generated from the promise executor!")); 
        }, 1000);
    }
});

/*
promise.catch(
    function(error){ console.log(error);}
).then(
    function(result){ console.log("Resolve:" + result) },
    function(result){ console.log("Reject:" + result) }
);

*/

promise.catch(
    function(error){ 
        console.log(error);
        return new Promise(function(resolve, reject){
            reject(error);
        });
})
.then(
    function(result){ console.log("Resolve:" + result) },
    function(result){ console.log("Reject:" + result) }
);
