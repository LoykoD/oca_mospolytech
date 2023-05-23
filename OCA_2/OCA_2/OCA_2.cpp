#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;



struct Cinema
{
	char MovieTitle[64];
	char session[5];
	int Price;
	int countSpectators;
	bool IsEmpty;
};

class Database
{
private:
	Cinema* _data;
	int _databaseSize;
	char* _filePath;
public:
	Database(int databaseSize, string filePath)
	{
		_data = new Cinema[databaseSize];
		_databaseSize = databaseSize;
		_filePath = new char[filePath.length() + 1];
		for (int i = 0; i < 6; i++)
		{
			Clear(i);
		}
	};

	void Clear(int index) // Первая функция очистка, обнуляет поля структуры
	{
		_data[index].Price = -1;
		_data[index].session[5] = { 0 };
		_data[index].countSpectators = -1;
		_data[index].MovieTitle[64] = { 0 };
		_data[index].IsEmpty = true;
	};

	int FindEmpty() // Вторая функция поиска свободной структурной переменной.
	{
		for (int i = 0; i < _databaseSize; i++)
		{
			if (_data[i].IsEmpty == true)
			{
				return(i);
			}
		};
		return(-1);
	}

	void Add(Cinema structure, int index) // Третья функция с добавлением структуры
	{
		_data[index] = structure;
	};

	Cinema DisplayCinema(int index) // Четвертая функция с выводом структуры
	{
		return(_data[index]);
	};

	vector<Cinema> GetAll() // Пятая функция с выводом на экран всех заполненных элементов массива структур.
	{
		vector<Cinema> buffer;
		for (int i = 0; i < _databaseSize; i++)
		{
			if (_data[i].IsEmpty == false)
			{
				buffer.push_back(_data[i]);
			}
		}
		return(buffer);
	};
	// Функция поиска структуры по названию фильма //
	Cinema FindByMovieTitle(string search) // Поиск по названию
	{
		for (int i = 0; i < _databaseSize; i++)
		{
			if (_data[i].IsEmpty)
			{
				continue;
			}
			else
			{
				if (string(_data[i].MovieTitle).find(search) != string::npos)
				{
					return(_data[i]);
				}
			}
		}
	};
	// Функция поиска структуры по цене билета //
	Cinema FindByPrice(int price)
	{
		Cinema buffer;
		int minimum_difference = 9999999999;
		for (int i = 0; i < _databaseSize; i++)
		{
			if (_data[i].IsEmpty == false)
			{
				if (abs(price - _data[i].Price) <= minimum_difference)
				{
					minimum_difference = price - _data[i].Price;
					buffer = _data[i];
				}
			}
			else
				continue;
		}
		return(buffer);
	};
	// Функция поиска структуры по количеству зрителей //
	Cinema FindBycountSpectators(int countSpectators)
	{
		Cinema buffer;
		int minimum_difference = 9999999999;
		for (int i = 0; i < _databaseSize; i++)
		{
			if (_data[i].IsEmpty == false)
			{
				if (abs(countSpectators - _data[i].countSpectators) <= minimum_difference)
				{
					minimum_difference = countSpectators - _data[i].countSpectators;
					buffer = _data[i];
				}
			}
			else
				continue;
		}
		return(buffer);
	};

	/////////////////////////////////////////////////////////////////////////////////////////
	// Седьмая Функция

	template<typename TValue>
	Cinema* FindMin(TValue(*selectorFunction)(Cinema))
	{
		TValue min = selectorFunction(_data[0]);
		int indexOfMinElement = -1;
		for (size_t i = 0; i < _databaseSize; i++)
		{
			if (!_data[i].IsEmpty && selectorFunction(_data[i]) <= min)
			{
				indexOfMinElement = i;
				min = selectorFunction(_data[i]);
			};
		};
		return indexOfMinElement == -1 ? (Cinema*)NULL : &_data[indexOfMinElement];
	}

	/*template<size_t I>
	Cinema* FindMin(int fieldNumber)
	{
		Cinema buffer;
		int indexOfMin;
		for (int i = 0; i < _databaseSize; i++)
		{
			buffer = _data[i];
			auto value = get<fieldNumber>(tie(buffer.MovieTitle, buffer.Price, buffer.countSpectators));
			cout << value;
		}
		return(buffer);
	}*/
	// Сортировка по возрастанию
	void SortBy(int fieldnumber)
	{
		switch (fieldnumber)
		{
		case(1):
			/*for (int i = 0; i < _databaseSize - 1; i++)
				for (int j = 0; j < _databaseSize - i - 1; j++)
					if (_data[j].MovieTitle > _data[j + 1].MovieTitle)
					{
						Cinema buffer;
						buffer = _data[j];
						_data[j] = _data[j + 1];
						_data[j + 1] = buffer;
					}*/
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.MovieTitle < p2.MovieTitle;
				});
			break;
		case(2):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.Price < p2.Price;
				});
			break;
		case(3):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.countSpectators < p2.countSpectators;
				});
			break;
		case(4):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.session < p2.session;
				});
			break;
		default:
			break;
		}
	}
	// Сортировка по убыванию
	void SortByDescending(int fieldnumber)
	{
		switch (fieldnumber)
		{
		case(1):
			/*for (int i = 0; i < _databaseSize - 1; i++)
				for (int j = 0; j < _databaseSize - i - 1; j++)
					if (_data[j].MovieTitle > _data[j + 1].MovieTitle)
					{
						Cinema buffer;
						buffer = _data[j];
						_data[j] = _data[j + 1];
						_data[j + 1] = buffer;
					}*/
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.MovieTitle > p2.MovieTitle;
				});
			break;
		case(2):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.Price > p2.Price;
				});
			break;
		case(3):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.countSpectators > p2.countSpectators;
				});
			break;
		case(4):
			sort(_data, _data + _databaseSize, [](const Cinema& p1, const Cinema& p2)
				{
					return p1.session > p2.session;
				});
			break;
		default:
			break;
		}
	};

	// Функция 10 чтение файла с содержимым бд
	void Restore() {
		FILE* file;
		fopen_s(&file, _filePath, "rb");

		for (size_t i = 0; i < _databaseSize; i++)
			fread(&_data[i], sizeof(Cinema), 1, file);

		fclose(file);
	}

	// 11. Функция записи в файл содержимого базы данных (массива структурных элементов).
	void Save() {
		FILE* file;
		fopen_s(&file, "data.bin", "wb");

		for (size_t i = 0; i < _databaseSize; i++)
			fwrite(&_data[i], sizeof(Cinema), 1, file);

		fclose(file);
	}
	/*template<typename TValue>
	Cinema* FindMin(TValue(*selectorFunction)(Cinema))
	{
		TValue min = selectorFunction(_data[0]);
		int indexOfMinElement = -1;
		for (size_t i = 0; i < _databaseSize; i++)
		{
			if (!_data[i].IsEmpty && selectorFunction(_data[i]) <= min)
			{
				indexOfMinElement = i;
				min = selectorFunction(_data[i]);
			};
		};
		return indexOfMinElement == -1 ? (Cinema&)NULL : &_data[indexOfMinElement];
	}*/

};

void DisplayStruct(Cinema cinema)
{
	cout << endl << "------------------------------------------------------" << endl;
	cout << " Название фильма: " << cinema.MovieTitle << endl;
	cout << " Время сеанса: " << cinema.session << endl;
	cout << " Стоимость билета: " << cinema.Price << endl;
	cout << " Количество зрителей: " << cinema.countSpectators << endl;
	cout << "------------------------------------------------------" << endl;
}
int main()
{
	int databaseSize;
	string databaseName;
	setlocale(LC_ALL, "rus");
	cout << "Введите размер базы данных: ";
	cin >> databaseSize;
	cout << "Введите название базы данных: ";
	cin >> databaseName;
	Database* database = new Database(databaseSize, databaseName);
	cout << "Команды: \n Очистить структуру - c\n Найти свободную структуру - f\n Заполнить структуру - p\n Вывести структуру по индексу - e\n Вывести все заполненные структуры - g\n Поиск с заданным значением поля - k\n Поиск в массиве минимальноый структуры по полю - y\n Сортировка в порядке возрастания по индексу поля - r\n Сортировка в порядке убывания по индексу поля - b\n Прочитать файл - 1\n Записать содержимое БД в файл - 2\n \nВведите команду: ";
	char command;
	cin >> command;
	while (command != 'z')
	{
		switch (command)
		{
		case('c'): // Очистка структуры | Первая функция
			cout << "Введите индекс структуры: ";
			int indexstruct;
			cin >> indexstruct;
			try
			{
				database->Clear(indexstruct);
				cout << " Успешно!\n";
			}
			catch (int a)
			{
				perror("[Ошибка очистки структуры]");
			};
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('f'): // Найти свободную структуру | Вторая функция
			int freeIndex;
			freeIndex = database->FindEmpty();
			if (freeIndex != -1)
			{
				cout << " Свободный индекс структуры: " << freeIndex << endl;
			}
			else
			{
				cout << " Все структуры заполнены!" << endl;
			}
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('p'): // Заполнить поля структуры и передать в бд | Третья функция
			if (database->FindEmpty() != -1)
			{
				Cinema fillStruct;
				cout << "Введите название фильма: ";
				cin >> fillStruct.MovieTitle;
				cout << "Введите время сеанса: ";
				cin >> fillStruct.session;
				cout << "Введите стоимость билета: ";
				cin >> fillStruct.Price;
				cout << "Введите количество зрителей: ";
				cin >> fillStruct.countSpectators;
				fillStruct.IsEmpty = false;
				database->Add(fillStruct, database->FindEmpty());
			}
			else
			{
				cout << "Структура переполнена!\n";
			}
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('e'): // Четвертая функция вывода полей
			cout << "Введите индекс структуры: ";
			int indexStruct;
			cin >> indexStruct;
			DisplayStruct(database->DisplayCinema(indexStruct));
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('g'): // Вывести все заполненные структуры = ); | Пятая функция
		{
			vector<Cinema> AllSession = database->GetAll();
			for (int i = 0; i < AllSession.size(); i++)
			{
				DisplayStruct(AllSession[i]);
				/*cout << endl << "------------------------------------------------------" << endl;
				cout << " Название фильма: " << AllSession[i].MovieTitle << endl;
				cout << " Время сеанса: " << AllSession[i].session << endl;
				cout << " Стоимость билета: " << AllSession[i].Price << endl;
				cout << " Количество зрителей: " << AllSession[i].countSpectators << endl;
				cout << "------------------------------------------------------" << endl;*/
			}
		}
		cout << " Введите команду: ";
		cin >> command;
		break;
		case('k'): // Шестая функция поиска по заданным значениями
		{
			char find_command;
			cout << " Поиск по названию фильма - f\n Поиск по цене билета - p\n Поиск по количеству зрителей - c\n Введите букву: ";
			cin >> find_command;
			switch (find_command)
			{
			case('f'):
			{
				cout << "Введите название: ";
				string NameCinema;
				cin >> NameCinema;
				if (database->FindByMovieTitle(NameCinema).MovieTitle[0] != '0')
				{
					DisplayStruct(database->FindByMovieTitle(NameCinema));
				}
				else
					cout << "Фильм не найден" << endl;
				break;
			}
			break;
			case('p'):
				cout << "Введите стоимость билета: ";
				int priceTicket;
				cin >> priceTicket;
				cout << "Ближайший подходящий фильм по введенной стоимости: " << endl;
				DisplayStruct(database->FindByPrice(priceTicket));
				break;
			case('c'):
				cout << "Введите количество зрителей: ";
				int countSpectors;
				cin >> countSpectors;
				cout << " Ближайший подходящий фильм по введенному количеству зрителей: " << endl;
				DisplayStruct(database->FindBycountSpectators(countSpectors));
				break;
			default:
				cout << "Неизвестная команда";
				break;
			};
			cout << " Введите команду: ";
			cin >> command;
			break;
		}
		case('y'): // Седьмая функция с поиском минимального значения поля
		{
			cout << " Первое поле - Название\n Второе поле - Цена \n Третье поле - Количество зрителей\n Четвертое поле - время сеанса\n ";
			cout << "Введите номер поля: ";
			int fieldNumber;
			cin >> fieldNumber;
			if ((fieldNumber == 1) || (fieldNumber == 4))
			{
				Cinema* minByName = database->FindMin<string>([](Cinema p)
					{
						return string(p.MovieTitle);
					});
				if (fieldNumber == 1)
				{
					cout << "Минимальный по названию: " << endl;
					Cinema* minByName = database->FindMin<string>([](Cinema p)
						{
							return string(p.MovieTitle);
						});
					DisplayStruct(*minByName);
				}
				else
				{
					cout << "Минимальный по продолжительности: " << endl;
					Cinema* minBySession = database->FindMin<string>([](const Cinema p)
						{
							return string(p.session);
						});
					DisplayStruct(*minBySession);
				}
			}
			else
			{
				if (fieldNumber == 2)
				{
					Cinema* minByPrice = database->FindMin<int>([](const Cinema p)
						{
							return p.Price;
						});
					DisplayStruct(*minByPrice);
				}
				else
				{
					Cinema* minBycountSpectators = database->FindMin<int>([](const Cinema p)
						{
							return p.countSpectators;
						});
					DisplayStruct(*minBycountSpectators);
				};
			};
		};
		cout << " Введите команду: ";
		cin >> command;
		break;
		case('r'): // Восьмая функция с сортировкой в порядке возрастания
			cout << " Первое поле - Название\n Второе поле - Цена \n Третье поле - Количество зрителей\n Четвертое поле - время сеанса\n ";
			cout << "Введите номер поля: ";
			int fieldNumber_2;
			cin >> fieldNumber_2;
			database->SortBy(fieldNumber_2);
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('b'): // Девятая функция с сортировкой в порядке убывания
			cout << " Первое поле - Название\n Второе поле - Цена \n Третье поле - Количество зрителей\n Четвертое поле - время сеанса\n ";
			cout << "Введите номер поля: ";
			int fieldNumber_3;
			cin >> fieldNumber_3;
			database->SortByDescending(fieldNumber_3);
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('1'): // Десятая функция с чтением файла
			database->Restore();
			cout << " Введите команду: ";
			cin >> command;
			break;
		case('2'): // Одиннадцатая функция с сохранением файла
			database->Save();
			cout << " Введите команду: ";
			cin >> command;
			break;
		default:
			cout << "che?" << endl;
			cin >> command;
			break;
		};
	};

	//Database* database = new Database(10, "db");
	//Cinema cinemaDate;
	//int index = 5;

	//database->Add(cinemaDate,index);
	/*FILE* fp;
	fp = fopen("t.txt", "r");
	if (fp == NULL)
	{
		perror("Ошибка открытия файла\n");
		exit(0);
	}*/
	return(0);
}