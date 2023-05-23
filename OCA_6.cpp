#include <iostream>
#include <fstream>
using namespace std;

/*
    Написать алгоритм Дейкстры.

    Граф задается в файле в виде матрицы. done
    Входные данные: начальная и конечная вершина. done
    После завершения обхода графа результат должен быть записан в файл путем добавления строки в формате:
        начальная вершина, done
        конечная вершина, done
        промежуточные вершины от начальной до конечной. done
    Исходный граф должен содержать не менее 10-ти вершин и 30-ти связей между ними.
*/

class Graph
{
private:
    int** link_matrix;
    int* min_distance;
    int* tops;
    int minindex, min;
    int lenght_mas;
    bool min_distanceIsTrue = false;
    int _start_top;
    int _end_top;
public:
    ofstream file;

    Graph(int start_top, int end_top)
    {
        file.open("test.txt");
        file << start_top << "\n" << end_top << "\n";

        _start_top = start_top;
        _end_top = end_top;
        lenght_mas = end_top- start_top + 1;
        link_matrix = new int* [lenght_mas];
        min_distance = new int[lenght_mas];
        tops = new int[lenght_mas];
        for (int i = 0; i < lenght_mas; i++)
        {
            link_matrix[i] = new int[lenght_mas];
            min_distance[i] = 99999999; // Изначально мин расст оч большое, беск
            tops[i] = 1;
        }

        for (int i = 0; i < lenght_mas; i++)
        {
            for (int j = 0; j < lenght_mas; j++)
            {
                link_matrix[i][j] = 0;
            }
        }
        min_distance[0] = 0; // Первый элемент не имеет расстояния до него
    }

    int show_matrix(int i, int j)
    {
        return(link_matrix[i][j]);
    }

    void push_matrix(int i, int j, int value)
    {
        link_matrix[i][j] = value;
        link_matrix[j][i] = value;
    }

    void find_min_distance()
    {
        do
        {
            minindex = 99999999;
            min = 99999999;
            for (int i = 0; i < lenght_mas; i++)
            {
                if ((tops[i] == 1) && (min_distance[i] < min)) // находим первую вершину и ищем наим.расстояние, запоминая значение в переменной min
                {
                    min = min_distance[i];
                    minindex = i;
                }
            }

            if (minindex != 99999999)
            {
                for (int i = 0; i < lenght_mas; i++)
                {
                    if (link_matrix[minindex][i] > 0)
                    {
                        int temp = min + link_matrix[minindex][i];
                        if (temp < min_distance[i])
                        {
                            min_distance[i] = temp; // сделали свап местами, если temp меньше мин.дистанции в текущей вершине ( нашли ход ближе к пункту )
                        }
                    }
                }
                tops[minindex] = 0; // посетили вершину и отметили ее посещенной
                file << minindex+_start_top << " ";
            }
        } while (minindex < 99999999); // do while - потому что сначала инициализируем

        min_distanceIsTrue = true;
    };

    int min_distance_return(int top)
    {
        if (min_distanceIsTrue == false)
        {
            find_min_distance();
        }
        return(min_distance[top-_start_top]);
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");
    bool GraphIsExists = false;
    int length_graph;
    int start_top, end_top;
    cout << " Введите начальную вершину: ";
    cin >> start_top;
    cout << " Введите конечную вершину: ";
    cin >> end_top;

    length_graph = end_top - start_top + 1;
    Graph test(start_top,end_top);

    cout << "Команды:\n 1 - заполнить граф\n 2 - показать матрицу графа\n 3 - вывод мин.расстояния до определенной вершины\n 0 - завершить программу\n Введите команду: ";
    char command;
    cin >> command;
    while (command != 0)
    {
        switch (command)
        {
        case('1'):
        {
            for (int i = start_top; i <= end_top; i++) // Заполнение матрицы
            {
                test.push_matrix(i-start_top, i-start_top, 0);
                for (int j = i + 1; j <= end_top; j++)
                {
                    cout << "Введите расстояние " << i << " - " << j << " : ";
                    int buf;
                    cin >> buf;
                    test.push_matrix(i-start_top, j-start_top, buf);
                }
            }
            GraphIsExists = true;

            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('2'):
        {
            if (GraphIsExists)
            {
                for (int i = 0; i < length_graph; i++) // Вывод матрицы
                {
                    for (int j = 0; j < length_graph; j++)
                        cout << test.show_matrix(i, j);
                    cout << endl;
                }
            }
            else
            {
                cout << " Граф не был создан!\n";
            }
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('3'):
            if (GraphIsExists)
            {
                cout << " Введите номер вершины: ";
                int vertex_number;
                cin >> vertex_number;
                if (vertex_number + 1 < length_graph)
                {
                    cout << " Неверный номер вершины";
                }
                else
                {
                    cout << " Мин расст до введенной вершины: " << test.min_distance_return(vertex_number) << endl;
                }
            }
            else
            {
                cout << " Граф не был создан!\n";
            }
            cout << " Введите команду: ";
            cin >> command;
            break;
        case('0'):
            command = 0;
            break;
        default:
            cout << "Неизвестная команда :<" << endl;
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
    }
}