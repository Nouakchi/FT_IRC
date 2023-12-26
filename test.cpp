#include <iostream>
#include <sstream>

int main(){
    std::string s = "geeks for geeks geeks "
               "contribution placements";

    std::string word;

    std::stringstream ss(s);
    while (ss >> word)
        std::cout << word << std::endl;
}