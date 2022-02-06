#!/usr/local/bin/php
<html>
    <body>
        <?php echo "The query string is: ".$_SERVER['QUERY_STRING']; ?> </br>
        <?php echo "Method: ".$_SERVER['REQUEST_METHOD']; ?> </br>
        <?php echo "Protocol: ".$_SERVER['SERVER_PROTOCOL']; ?> </br>

        Welcome 
        <?php if(isset($_GET['lastName'])): ?>
            <?php echo $_GET['lastName']; ?>
        <?php endif; ?>
        <?php if(isset($_GET['firstName'])): ?>
            <?php echo $_GET['firstName']; ?>
        <?php endif; ?>
        <?php if(isset($_GET['message'])): ?>
            Message is: <?php echo $_GET['message']; ?>
        <?php endif; ?>
    </body>
</html>