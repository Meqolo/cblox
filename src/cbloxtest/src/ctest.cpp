#include <iostream>
#include <cblox/user.h>

using json = nlohmann::json;

int main()
{
	//json data = {};
	//data["Hello"] = "Hi";
	json data = cblox::User::getFriends(93082239);
    std::cout << data; 

}