#!/usr/local/bin/php

<?php
   if(isset($_FILES['fichier'])){
      $errors= array();
      $file_name = $_FILES['fichier']['name'];
      $file_size =$_FILES['fichier']['size'];
      $file_tmp =$_FILES['fichier']['tmp_name'];
      $file_type=$_FILES['fichier']['type'];
      $file_ext = strtolower(pathinfo($file_name,PATHINFO_EXTENSION));

      $extensions= array("html", "txt", "php");
      
      if(in_array($file_ext,$extensions)=== false){
         $errors[]="extension not allowed";
      }
      
      if(empty($errors)==true){
         move_uploaded_file($file_tmp,"/Users/redwanezafari/Documents/42/Webserv/www/upload/files/".$file_name);
         echo "Success";
      }else{
         print_r($errors);
      }
   }
?>*/

<html>
    <body>
        <?php
            parse_str(file_get_contents("php://stdin"), $_POST);
            echo "POST <br>";

            echo "Welcome " . $_POST["lastName"] . " " . $_POST["firstName"] . "<br>";
            echo "Your message is: " . $_POST["message"];
        ?>
    </body>
</html>