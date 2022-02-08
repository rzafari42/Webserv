#!/usr/local/bin/php
<html>
    <body>
        <?php
            $input_data = file_get_contents("php://stdin");
            parse_str($input_data, $_POST);
            echo "POST <br>";

            echo "Welcome " . $_POST["lastName"] . " " . $_POST["firstName"] . "<br>";
            echo "Your message is: " . $_POST["message"];
        ?>
    </body>
</html>
