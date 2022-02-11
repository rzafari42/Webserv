#!/usr/bin/php-cgi
<html>
    <body>
        <?php
            parse_str(getenv('QUERY_STRING'), $_GET);
            echo "GET <br>";
            
            echo "Welcome " . $_GET["lastName"] . " " . $_GET["firstName"] . "<br>"; 
            echo "Your message is: " . $_GET["message"];
        ?>
    </body>
</html>