function insertionSort(array) {
  var i, j;
  var temp;
  for (i = 1; i < array.length; i++) {
    temp = array[i];
    for (j = i; j >= 1 && array[j - 1] > temp; j--) array[j] = array[j - 1];
    array[j] = temp;
  }
  return array;
}
