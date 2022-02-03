<?php
    echo "salut";
    if (isset($_POST['lastName']))
    {
        echo $_POST['lastName'];
    }
    if (isset($_POST['firstName']))
    {
        echo $_POST['firstName'];
    }
?>