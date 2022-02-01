#!/bin/bash
INDEX=`ls -1 $1 | sed "s/^.*/      <li\>\<a\ href=\"&\"\>&\<\\/a\>\<\\/li\>/"`

echo "<html>
    <head>
        <meta charset="utf-8"/>
        <title>Webserv -  Index of $2</title>
    </head>
    <body>
     <h2>Index of $2</h2>
     <hr>
    <ul>
       $INDEX
    </ul>
  </body>
</html>"