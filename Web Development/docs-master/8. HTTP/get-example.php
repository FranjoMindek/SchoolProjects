<?php
  // The global $_POST variable allows you to access the data sent with the POST method by name
  // To access the data sent with the GET method, you can use $_GET
  $first = htmlspecialchars($_GET['first']);
  $last  = htmlspecialchars($_GET['last']);

  echo  'Hello ', $first, ' ', $last, '!';
?>