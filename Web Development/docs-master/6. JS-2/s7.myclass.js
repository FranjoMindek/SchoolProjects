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

function createNewMyClass(prop2Value) {
  const obj = {};
  obj.prop2 = prop2Value;
  obj.prop1 = "Value";
  obj.method1 = function() { console.log('Method 1') };
  obj.method2 = function() { console.log('Method 2') };
  Object.defineProperty(obj, 'getterName', { get: function() { return obj.prop1; } } );  
  Object.defineProperty(obj, 'setterName', { set: function(prop1) { obj.prop1 = prop1; } } );
  return obj;
}

const exampleObj = createNewMyClass('sampleValue');