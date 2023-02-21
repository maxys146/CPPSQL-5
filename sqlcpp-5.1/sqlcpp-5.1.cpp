// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>

class Client
{
public:
	void addClient(std::string asd)
	{
		std::cout << "Добавляем клиента: " << asd << "\n";
		//return 1324;
	}

	// TODO Конструктор
};

int main()
{
	try
	{
		//setlocale(LC_ALL, "ru_RU.UTF-8");
		setlocale(LC_ALL, "Russian");

		Client* client = new Client;
		//std::cout << client->addClient() << std::endl;
		client->addClient("Курочкин");

		return 0;

		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");

		// Создаем БД
		pqxx::work tx{ c };
		//tx.exec("DROP TABLE IF EXISTS public.Phones");
		//tx.exec("DROP TABLE IF EXISTS public.Clients");
		tx.exec("CREATE TABLE IF NOT EXISTS public.Clients("
			"id SERIAL PRIMARY KEY, "
			"\"firstname\" VARCHAR NOT NULL,"
			"\"lastname\" VARCHAR NOT NULL,"
			"\"email\" VARCHAR NOT NULL)");
		tx.exec("CREATE TABLE IF NOT EXISTS public.Phones("
			"\"id\" SERIAL PRIMARY KEY,"
			"\"phone\" VARCHAR NOT NULL,"
			"\"client\" INTEGER REFERENCES public.Clients(id))");

		tx.commit();





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
