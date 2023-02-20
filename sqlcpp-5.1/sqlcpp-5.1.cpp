// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>


int main()
{
	pqxx::connection c("host=localhost "
		"port=5432 "
		"dbname=netology05 "
		"user=postgres "
		"password=111111");
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
