// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>

class Client
{
public:
	void addClient(auto& c, std::string firstname, std::string lastname, std::string email)
	{
		pqxx::work tx{ c };
		std::cout << "Добавляем клиента: " << firstname << "\n";
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('" + tx.esc(firstname) + "', '" + tx.esc(lastname) + "', '" + tx.esc(email) + "')");
		tx.commit();
	}
	void updateClient(auto& c, int clientId, std::string firstname, std::string lastname, std::string email)
	{
		pqxx::work tx{ c };
		std::cout << "Обновляем клиента: " << firstname << "\n";
		tx.exec("UPDATE public.Clients SET firstname = '" + tx.esc(firstname) + "', lastname = '" + tx.esc(lastname) + "', email = '" + tx.esc(email) + "' WHERE id = '" + tx.esc(std::to_string(clientId)) + "'");
		tx.commit();
	}
	void addPhone(auto& c, int clientId, std::string phone)
	{
		pqxx::work tx{ c };
		std::cout << "Добавляем телефон: " << phone << "\n";
		tx.exec("INSERT INTO public.Phones(phone, client) VALUES ('" + tx.esc(phone) + "', '" + tx.esc(std::to_string(clientId)) + "')");
		tx.commit();
	}

	// TODO Конструктор
};

int main()
{
	try
	{
		setlocale(LC_ALL, "ru_RU.UTF-8");
		//setlocale(LC_ALL, "Russian");

		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");

		

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

		tx.commit();



		Client* client = new Client;
		//std::cout << client->addClient() << std::endl;
		client->addClient(c, "Ivan", "Kukuev", "vanek@example.ru");
		client->addClient(c, "Gennady", "Reptile", "bezzubiy@example.ru");
		client->addClient(c, "Iiiiigor", "Babushkin", "top4eg@example.ru");
		client->addClient(c, "Evlampiy", "4orny", "demon666@example.ru");
		client->addClient(c, "Shamil", "Perviy", "tcar@example.ru");

		client->addPhone(c, 1, "12222222");
		client->addPhone(c, 1, "13333333");
		client->addPhone(c, 2, "21111111");
		client->addPhone(c, 2, "22222222");
		client->addPhone(c, 2, "23333333");
		client->addPhone(c, 3, "31111111");
		client->addPhone(c, 4, "41111111");

		client->updateClient(c, 2, "Pupuk", "Perdikov", "PUPUK@example.ru");





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
