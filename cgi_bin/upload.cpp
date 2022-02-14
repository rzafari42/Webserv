#include <iostream>
#include <string>
#include <stdio.h>      /* printf */
#include <stdlib.h> 

int main() {
    std::cout << getenv("BODY") << std::endl;
    return 0;
}