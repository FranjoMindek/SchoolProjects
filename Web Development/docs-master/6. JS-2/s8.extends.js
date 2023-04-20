class MyClass1{
  constructor() { console.log('BASE CONSTRUCTOR'); }
  method1() { console.log('Method 1') }
}

class MyClass2 extends MyClass1{
  constructor() { 
    super();
  }

  method1() { 
    super.method1();
  }

  method2() { console.log('Method 2') }
}