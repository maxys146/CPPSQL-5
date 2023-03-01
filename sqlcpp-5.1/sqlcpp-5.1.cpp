﻿// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>

class Client
{
public:
	void addClient(auto &c, std::string firstname, std::string lastname, std::string email)
	{
		pqxx::work tx{ c };
		std::cout << "Добавляем клиента: " << firstname << "\n";
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('" + tx.esc(firstname) + "', '" + tx.esc(lastname) + "', '" + tx.esc(email) + "')");
		tx.commit();
	}

	// TODO Конструктор
};

int main()
{
	try
	{
		//setlocale(LC_ALL, "ru_RU.UTF-8");
		setlocale(LC_ALL, "Russian");

		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");

		

		Client* client = new Client;
		//std::cout << client->addClient() << std::endl;
		client->addClient(c, "Ivan", "Kukuev", "vanek@example.ru");
		client->addClient(c, "Gennady", "Reptile", "bezzubiy@example.ru");
		client->addClient(c, "Iiiiigor", "Babushkin", "top4eg@example.ru");
		client->addClient(c, "Evlampiy", "4orny", "demon666@example.ru");
		client->addClient(c, "Shamil", "Perviy", "tcar@example.ru");
		


		return 0;
		// Создаем БД
		pqxx::work tx{ c };
		tx.exec("DROP TABLE IF EXISTS public.Phones");
		tx.exec("DROP TABLE IF EXISTS public.Clients");
		tx.exec("CREATE TABLE IF NOT EXISTS public.Clients("
			"id SERIAL PRIMARY KEY, "
			"\"firstname\" VARCHAR NOT NULL,"
			"\"lastname\" VARCHAR NOT NULL,"
			"\"email\" VARCHAR NOT NULL)");
		tx.exec("CREATE TABLE IF NOT EXISTS public.Phones("
			"\"id\" SERIAL PRIMARY KEY,"
			"\"phone\" VARCHAR NOT NULL,"
			"\"client\" INTEGER REFERENCES public.Clients(id))");

		//tx.commit();
		tx.exec("commit;");
	}
	catch (const pqxx::sql_error& e)
	{
		std::cout << "SQL error: " << e.what() << std::endl;
	}
	catch (const pqxx::usage_error e)
	{
		std::cout << "Usage error: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Some error...";
	}
	return 0;
}
