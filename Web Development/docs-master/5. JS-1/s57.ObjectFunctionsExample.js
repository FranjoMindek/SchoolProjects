function ObjectFunctionsExample() {
  var obj = {
    count: 10,
    countAfterThreeSeconds: function () {
      setTimeout(() => {
        this.count++;
        console.log(this.count);
      }, 3000);
    },
  };
  obj.countAfterThreeSeconds();
}

ObjectFunctionsExample();
