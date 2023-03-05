// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>

class Client
{
public:
	Client(auto& c)
	{
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

	}
	void addClient(auto& c, std::string firstname, std::string lastname, std::string email)
	{
		pqxx::work tx{ c };
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('" + tx.esc(firstname) + "', '" + tx.esc(lastname) + "', '" + tx.esc(email) + "')");
		tx.commit();
	}
	void updateClient(auto& c, int clientId, std::string firstname, std::string lastname, std::string email)
	{
		pqxx::work tx{ c };
		tx.exec("UPDATE public.Clients SET firstname = '" + tx.esc(firstname) + "', lastname = '" + tx.esc(lastname) + "', email = '" + tx.esc(email) + "' WHERE id = '" + tx.esc(std::to_string(clientId)) + "'");
		tx.commit();
	}
	void deleteClient(auto& c, int clientId)
	{
		pqxx::work tx{ c };
		tx.exec("DELETE FROM public.Clients WHERE id = '" + tx.esc(std::to_string(clientId)) + "'");
		tx.commit();
	}
	void findClient(auto& c, std::string searchLine)
	{
		pqxx::work tx{ c };
		std::cout << "Searching: " << searchLine << "\n";
		for (auto [client_id, firstname, lastname, email, phone] : tx.query<int, std::string, std::string, std::string, std::string>("SELECT clients.id, clients.firstname, clients.lastname, clients.email, phones.phone FROM phones LEFT JOIN clients ON phones.client = clients.id "
			"WHERE ("
			"clients.firstname LIKE '" + tx.esc(searchLine) + "' OR "
			"clients.lastname LIKE '" + tx.esc(searchLine) + "' OR "
			"clients.email LIKE '" + tx.esc(searchLine) + "' OR "
			"phones.phone LIKE '" + tx.esc(searchLine) + "') "
			"ORDER BY id"))
		{
			std::cout << client_id << ". " << firstname << " " << lastname << ", <" << email << ", <" << phone << ">\n";


		}
		tx.commit();
	}
	void addPhone(auto& c, int clientId, std::string phone)
	{
		pqxx::work tx{ c };
		tx.exec("INSERT INTO public.Phones(phone, client) VALUES ('" + tx.esc(phone) + "', '" + tx.esc(std::to_string(clientId)) + "')");
		tx.commit();
	}
	void deletePhone(auto& c, int clientId)
	{
		pqxx::work tx{ c };
		tx.exec("DELETE FROM public.Phones WHERE client = '" + tx.esc(std::to_string(clientId)) + "'");
		tx.commit();
	}
};

void viewData(auto& c, std::string name)
{
	std::cout << "\t\t--== " << name << " ==--" << "\n";
	pqxx::work tx{ c };
	for (auto [client_id, firstname, lastname, email] : tx.query<int, std::string, std::string, std::string>("SELECT id, firstname, lastname, email FROM public.Clients ORDER BY id"))
	{
		std::cout << client_id << ". " << firstname << " " << lastname << ", <" << email << ">\n";
		for (auto [phone_id, phone] : tx.query<int, std::string>("SELECT id, phone FROM public.Phones WHERE client = '" + tx.esc(std::to_string(client_id)) + "'"))
		{
			std::cout << "\t\t\t\t\t" << phone << "\n";
		}
	}
	std::cout << "-------------------------------------------------" << std::endl << std::endl;
}

int main()
{
	try
	{
		setlocale(LC_ALL, "ru_RU.UTF-8"); // Работает норм с БД
		//setlocale(LC_ALL, "Russian"); // Работает норм в консоли

		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");


		Client* client = new Client(c);
		client->addClient(c, "Ivan", "Kukuev", "vanek@example.ru");
		client->addClient(c, "Gennady", "Reptile", "bezzubiy@example.ru");
		client->addClient(c, "Iiiiigor", "Babushkin", "top4eg@example.ru");
		client->addClient(c, "Evlampiy", "4orny", "demon666@example.ru");
		client->addClient(c, "Shamil", "Perviy", "tcar@example.ru");

		client->addPhone(c, 1, "+12222222");
		client->addPhone(c, 1, "+13333333");
		client->addPhone(c, 2, "+21111111");
		client->addPhone(c, 2, "+22222222");
		client->addPhone(c, 2, "+23333333");
		client->addPhone(c, 3, "+31111111");
		client->addPhone(c, 4, "+66666666");
		
		viewData(c, "SOURCE DATA");

		client->updateClient(c, 2, "Pupuk", "Perdikov", "PUPUK@example.ru");

		viewData(c, "MOD DATA");

		client->deletePhone(c, 3);

		viewData(c, "Delete Phone");

		client->deleteClient(c, 3);

		viewData(c, "Delete Client");

		client->findClient(c, "%I%");
		client->findClient(c, "%or%");
		client->findClient(c, "%2%");


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
