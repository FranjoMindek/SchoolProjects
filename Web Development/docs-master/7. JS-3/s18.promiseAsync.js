async function f() {
   return 1;
}
    
async function f1() {
   return 1;
}
f1().then(alert);
        
async function f2() {
   return result = await Promise.resolve(1);
}
f2().then(alert);