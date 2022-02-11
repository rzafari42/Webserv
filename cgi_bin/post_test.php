#!/Users/redwanezafari/Documents/42/Webserv/cgi_bin/php-cgi7.2
<html>
    <body>
        <?php
            parse_str(getenv('QUERY_STRING'), $_POST);
            echo "POST <br>";

            echo "Welcome " . $_POST["lastName"] . " " . $_POST["firstName"] . "<br>";
            echo "Your message is: " . $_POST["message"];
        ?>
    </body>
</html>
