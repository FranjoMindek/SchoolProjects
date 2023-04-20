class InsertionSort {
  //class-specific code (removed for brevity)

  set Size(newSizeValue) {
    if(newSizeValue > this.size){
      throw new RangeError("New value cannot be larger than the current size!");
    }
    else this.size = size;
  }       
}

try{
  let oneSort = new InsertionSort(100);
  oneSort.sort();
  oneSort.Size = 101;
} catch(err){
  if(err instanceof RangeError)
      console.log(err.name + ": " + err.message);
  else console("A sorting error has occured!");
}
