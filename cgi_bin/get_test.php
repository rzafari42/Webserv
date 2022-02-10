#!/mnt/c/Users/simbarre/Documents/42/webserv/cgi_bin/php-cgi7.2
<html>
    <body>
        <?php
            echo "GET <br>";

            echo "Welcome " . $_GET["lastName"] . " " . $_GET["firstName"] . "<br>";
            echo "Your message is: " . $_GET["message"];
        ?>
    </body>
</html>
