

#include <iostream>
#include <fstream>
#include <ios>

std::ofstream& f()
{
    std::ofstream ofs;
    ofs << "olaaa";
    return ofs;
}
int main()
{
    std::ofstream ofs = f();
    
}