#include <iostream>


int main()
{
    std::string res;
    setUnsetflags("+it-lk+o", res);
	std::cout << res << std::endl;
    return 0;
}