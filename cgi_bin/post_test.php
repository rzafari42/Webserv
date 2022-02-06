#!/usr/local/bin/php
<html>
    <body>
        Welcome 
        <?php if(isset($_POST['lastName'])): ?>
            <?php echo $_POST['lastName']; ?>
        <?php endif; ?>
        <?php if(isset($_POST['firstName'])): ?>
            <?php echo $_POST['firstName']; ?>
        <?php endif; ?>
        <?php if(isset($_POST['message'])): ?>
            Message is: <?php echo $_POST['message']; ?>
        <?php endif; ?>
    </body>
</html>