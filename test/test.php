<?php
if (isset($_GET['user']))
{
  $name = $_GET['user'];
  // $name2 = $_POST['fname2'];
  // $name3 = $_POST['fname3'];
}

if (empty($name)) {
  echo "Name is empty";
} else {
  echo $name;
}
?>