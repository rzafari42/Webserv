REQUEST: 
GET /upload.html HTTP/1.1
Host: localhost:8080
Connection: keep-alive
sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="98", "Google Chrome";v="98"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
DNT: 1
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.80 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: fr-FR,fr;q=0.9,en-GB;q=0.8,en;q=0.7,en-US;q=0.6






FINALE RESPONSE: 
HTTP/1.1 200 OK
Cache-Control: no-cache, private
Content-type: text/html
Content-Length: 596
Content-Language: fr
date: Thu, 10 Feb 2022 16:08:23 GMT

<!DOCTYPE html>

<html>
    <head>
        <meta charset="utf-8"/>
        <title>Webserv - Upload</title>
        <link rel="stylesheet" href="upload_style.css">
    </head>
    <body>
        <header>
            <h1>Upload</h1>
            <nav>
                <ul>
                    <li><a href="index.html">Home</a></li>
                </ul>
            </nav>
        </header>
        <form action="upload.php" method="POST" enctype="multipart/form-data">
            <input type="file" name="fichier" id="file"/>
            <input type="submit"/>
         </form>
    </body>
</html>
closing connection
REQUEST: 
GET /upload_style.css HTTP/1.1
Host: localhost:8080
Connection: keep-alive
sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="98", "Google Chrome";v="98"
DNT: 1
sec-ch-ua-mobile: ?0
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.80 Safari/537.36
sec-ch-ua-platform: "macOS"
Accept: text/css,*/*;q=0.1
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: no-cors
Sec-Fetch-Dest: style
Referer: http://localhost:8080/upload.html
Accept-Encoding: gzip, deflate, br
Accept-Language: fr-FR,fr;q=0.9,en-GB;q=0.8,en;q=0.7,en-US;q=0.6






FINALE RESPONSE: 
HTTP/1.1 200 OK
Cache-Control: no-cache, private
Content-type: text/css
Content-Length: 1517
Content-Language: fr
date: Thu, 10 Feb 2022 16:08:23 GMT

body
{
    font-family: 'Source Sans Pro', sans-serif;
    color: #000000;
    background-color: rgba(216, 216, 216, 0.904);
    height: 600px;
    margin-top: 60px;
    margin-bottom: 60px;
    font-size: 18px;
    font-weight: bolder;
    letter-spacing: 3px;
}

header
{
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

header h1
{
    font-size: 60px;
    filter: drop-shadow(2px 2px 0px grey);
}

header nav
{
    position: absolute;
    top: 8%;
    left: 0%;
}

header li
{
    margin-left: 40px;
    list-style-type: none;
}

header a
{
    color: black;
    text-decoration: none;
}

form
{
    display: flex;
    flex-direction: column;
    justify-content:center;
    align-items: center;
    padding: 0;
}

form input
{
    background-color: #E8E8E8;
    border-color: #E8E8E8;
    border: none;
    border-radius: 4px;
    filter: drop-shadow(2px 2px 2px rgba(0, 0, 0, 0.25));
    outline: none;
    height: auto;
    width: auto;
}

#file
{
    border:  none;
    margin-bottom: 25px;

}


#send
{

    margin-left: auto;
    margin-right: auto;
    color: #E8E8E8;
    font-weight: bold;
    background-color: rgba(0, 0, 0, 0.904);
    filter: none;
    height: 30px;
    width: 90px;
    font-size: 20px;
    letter-spacing: 2px;
    border-radius: 8px;
    box-shadow: 0px 4px 3px rgb(160, 160, 160);
    top: 15px;
}

#send:hover
{
    cursor: pointer;
}

#send:active
{
    border: none;
    transform: translateY(2px);
    box-shadow: none;
}
closing connection
REQUEST: 
POST /upload.php HTTP/1.1
Host: localhost:8080
Connection: keep-alive
Content-Length: 197
Cache-Control: max-age=0
sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="98", "Google Chrome";v="98"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
Origin: http://localhost:8080
Upgrade-Insecure-Requests: 1
DNT: 1
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryJ8haG7Btf7k9zBFt
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.80 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: http://localhost:8080/upload.html
Accept-Encoding: gzip, deflate, br
Accept-Language: fr-FR,fr;q=0.9,en-GB;q=0.8,en;q=0.7,en-US;q=0.6


Content: ||




FINALE RESPONSE: 
HTTP/1.1 500 Internal Server Error
Cache-Control: no-cache, private
Content-type: text/html
Content-Length: 220
Content-Language: fr
date: Thu, 10 Feb 2022 16:08:29 GMT

<!DOCTYPE html>    
<html>
    <head>
        <meta charset="utf-8"/>
        <title>500 Internal Server Error</title></head>
    <body>
        <center><h1>500</br>Internal Server Error</h1></center>
    </body>
</html>
closing connection
REQUEST: 

