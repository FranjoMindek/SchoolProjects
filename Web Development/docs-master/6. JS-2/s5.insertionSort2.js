class InsertionSort {
  sort(){
    for (let i = 1; i < this.array.length; i++) {
      let temp = this.array[i];
      let j = i;
      for (; j >= 1 && this.array[j - 1] > temp; j--)
        this.array[j] = this.array[j - 1];
      this.array[j] = temp;
    }
    return this.array;
  }
}

let oneSort = new InsertionSort(500000);
oneSort.sort();