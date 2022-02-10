#!/usr/bin/php
<html>
    <body>
        <?php
            echo "POST <br>";
            echo "QUERY_STRING->" . $_SERVER['QUERY_STRING'] . "<br><br>";
            $queries = array();
            parse_str($_SERVER['QUERY_STRING'], $queries);
        
            echo "Welcome " . $queries["lastName"] . " " . $queries["firstName"] . "<br>"; 
            echo "Your message is: " . $queries["message"];
        ?>
    </body>
</html>
