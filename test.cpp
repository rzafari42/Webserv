#include <iostream>
#include <fstream>

int main()
{
    std::ifstream ifs("test.txt");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    if (content[0] == '\r' && content[1] == '\n')
        std::cout << "CRLF found" << std::endl;
    if (content.empty() == true)
        std::cout << "NO CONTENT" << std::endl;
    else
        std::cout << "FILE IS NOT EMPTY" << std::endl;
    return 0;
}