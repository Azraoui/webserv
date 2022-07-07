<?php
if (isset($_POST['user']))
{
  $name = $_POST['user'];
  // $name2 = $_POST['fname2'];
  // $name3 = $_POST['fname3'];
}

if (empty($name)) {
  echo "Name is empty";
} else {
  echo $name;
}
?>