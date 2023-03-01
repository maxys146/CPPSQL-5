// sqlcpp-5.1.cpp: определяет точку входа для приложения.
//

#include "sqlcpp-5.1.h"
#include <pqxx/pqxx>

class Client
{
public:
	void addClient(auto &c, std::string asd)
	{
		pqxx::work tx{ c };
		std::cout << "Добавляем клиента: " << asd << "\n";
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Ivan 2', 'Kukuev', 'vanek@example.ru')");
		tx.commit();
		

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

		//return 0;

		pqxx::connection c("host=localhost "
			"port=5432 "
			"dbname=netology05 "
			"user=postgres "
			"password=111111");

		

		Client* client = new Client;
		//std::cout << client->addClient() << std::endl;
		client->addClient(c, "Курочкин");
		client->addClient(c, "Курочкин");
		


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

		// Заполняем БД тестовыми данными
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Ivan', 'Kukuev', 'vanek@example.ru')");
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Gennady', 'Reptile', 'bezzubiy@example.ru')");
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Iiiiigor', 'Babushkin', 'top4eg@example.ru')");
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Evlampiy', '4orny', 'demon666@example.ru')");
		tx.exec("INSERT INTO public.Clients(firstname, lastname, email) VALUES ('Shamil', 'Perviy', 'tcar@example.ru')");
		tx.commit();



	}
	catch (const pqxx::sql_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const pqxx::usage_error e)
	{
		std::cout << "Some error.. " << e.what() << std::endl;
	}
	return 0;
}
