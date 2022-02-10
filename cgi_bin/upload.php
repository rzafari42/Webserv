<<<<<<< HEAD
#!/mnt/c/Users/simbarre/Documents/42/webserv/cgi_bin/php-cgi7.2
=======
#!/usr/local/bin/php

>>>>>>> a859f0bcf72d6a7cbda5fdae579dcd780445dc8d
<?php
   if(isset($_FILES['fichier'])){
      $errors= array();
      $file_name = $_FILES['fichier']['name'];
      $file_size =$_FILES['fichier']['size'];
      $file_tmp =$_FILES['fichier']['tmp_name'];
      $file_type=$_FILES['fichier']['type'];
      // $file_ext=strtolower(end(explode('.',$_FILES['fichier']['name'])));
      $file_ext = strtolower(pathinfo($file_name,PATHINFO_EXTENSION));

      $extensions= array("html", "txt", "php");

      if(in_array($file_ext,$extensions)=== false){
         $errors[]="extension not allowed";
      }

      if(empty($errors)==true){
         move_uploaded_file($file_tmp,"/mnt/c/Users/simbarre/Documents/42/webserv/YoupiBanane".$file_name);
         echo "Success";
      }else{
         print_r($errors);
      }
   }
?>
