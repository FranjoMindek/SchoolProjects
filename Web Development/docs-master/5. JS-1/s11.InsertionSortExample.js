var array = [8, 5, 6, 2, 1, 9];
function insertionSort(array) {
  var i, j;
  var temp;
  for (i = 1; i < array.length; i++) {
    console.log("Korak: " + i);
    temp = array[i];
    for (j = i; j >= 1 && array[j - 1] > temp; j--)
      array[j] = array[j - 1];
    array[j] = temp;
  }
  return array;
}
insertionSort(array);
alert(array);