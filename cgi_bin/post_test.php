#!/mnt/c/Users/simbarre/Documents/42/webserv/cgi_bin/php-cgi7.2
<html>
    <body>
        <?php
            echo "POST <br>";

            echo "Welcome " . $_POST["lastName"] . " " . $_POST["firstName"] . "<br>";
            echo "Your message is: " . $_POST["message"];
        ?>
    </body>
</html>
