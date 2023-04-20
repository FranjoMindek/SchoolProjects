class InsertionSort {
  constructor(size) {
    this.size = size;
    this.array = this.generateRandomBigArray(size);
  } 

  generateRandomBigArray(size){
    let array = [];
    while(size > 0){
        array.push(Math.random()*1000);
        size --;
    }
    return array;
  }

  get Size() { return this.size;}

  set Size(newSizeValue) {
    if(newSizeValue > this.size){
      console.log("Error! This class does not allow increasing size without enlarging the array");
    }
    else
      this.size = size;
  }
}