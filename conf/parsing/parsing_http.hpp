#ifndef PARSING_HTTP_HPP
# define PARSING_HTTP_HPP
# include <iostream>
# include <fstream>
# include <vector>

class request{
    public:
        request();
        ~request();
        request(const request & src);
        request & operator=(const request &src);

    private:
        std::string Method;
        std::string Location;
        std::string Accept-Charset;
        std::string Accept-Encoding;
        std::string Authorization;
        std::string Content-Type;
        std::string Content-Length;
        std::string Date;
        std::string Host;
};

#endif