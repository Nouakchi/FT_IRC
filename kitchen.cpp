#include <iostream>


int main()
{

    int i = 0;
    std::string str("olala");
    while (str[i++])
    {
        std::cout << str[i] << std::endl;
    }
    
    // std::string res;
    // setUnsetflags("+it-lk+o", res);
	// std::cout << res << std::endl;
    // return 0;
}