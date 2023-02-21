// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>


int main()
{
	try
	{
		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");
	}
	catch (const pqxx::sql_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
	std::cout << "Some error.." << std::endl;

	}
	return 0;
}
