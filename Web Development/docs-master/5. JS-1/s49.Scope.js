function Scope() {
  if (true) {
    var a = 10;
    let b = 20;
    const c = 30;
    console.log("Printing variables a, b i c in if's scope: ", a, b, c);
    function exampleBS() {
      console.log("Printing variables a, b and c in exampleBS's scope (exampleBS is nested under if): ", a, b, c);
    }
    exampleBS();
  }
  console.log("Variable a in scope of the function Scope: ", a);
  console.log("Variable b in scope of the function Scope: ", b);
  console.log("Variable c in scope of the function Scope: ", c);
}

Scope();
