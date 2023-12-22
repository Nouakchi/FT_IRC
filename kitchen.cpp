

#include <iostream>

int main()
{
	char buff[10] = "oal";
	std::string str = "POP";
	str.append(buff);
	std::cout << str;
}