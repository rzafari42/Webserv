#!/usr/bin/php
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
