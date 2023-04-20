class MyClass {
  // declared property
  prop1 = "Value";
  // constructor
  constructor(prop2Value) {
     this.prop2 = prop2Value;
  }
  // member methods 
  method1() { console.log('Method 1'); }
  method2() { console.log('Method 2'); }
  //getter method
  get getterName() { return this.prop1}
  //setter method
  set setterName(prop1) { this.prop1 = prop1; }
}