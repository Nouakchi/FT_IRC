#include <iostream>
#include <sstream>
#include <vector>

// std::string skipSpaces(std::string input)
// {
// 	std::istringstream iss(input);
// 	std::string output;
// 	std::string str;
// 	int i = 0;

// 	while (getline(iss, str, ' '))
// 	{
// 		if (!str.empty()) // what is the prolem if i add protection or removing it 
// 			std::cout << str +" ";
// 		// if (iss.eof())
// 		// 	output += str;
// 		// else
// 		// 	output += str + " ";
// 	}
// 	return output;
// }
std::string skipSpaces(std::string input)
{
    std::istringstream iss(input);
    std::string output;
    std::string str;
    int i = 0;

    while (getline(iss, str, ' ')) {
        if (!str.empty()) {
            output += str;
            if (!iss.eof()) {
                output += " ";
            }
        }
    }
    return output;
}
void splitString(const std::string& input, std::vector<std::string>& tokens)
{
    std::istringstream iss(input);
    std::string token;
	std::string realname;

    while (std::getline(iss, token, ' ')) {
		if (token[0] == ':')
			break;
		else 
        	tokens.push_back(token);
    }
	if (token[0] == ':')
	{
		std::getline(iss, realname,'\n');
		token = token.substr(1) + " "+ skipSpaces(realname);
		tokens.push_back(token);
	}
}

int main() {
    // Example: Splitting a string by spaces
    std::string input = "USER john localhost irc.example.com :J   ohn     Doe alal";

    std::vector<std::string> tokens;
    splitString(input, tokens);

	std::cout << tokens.size() << std::endl<< std::endl<< std::endl;
    // Display the tokens
    std::cout << "Tokens:" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << "[" << i << "] " << tokens[i] << std::endl;
    }

    return 0;
}
