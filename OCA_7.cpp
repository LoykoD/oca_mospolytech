////////////// Второй код
#include <iostream>
#include <list>
#include <string.h>
#include <string>
using namespace std;

/*
    Написать программу поиска в ширину, реализующую алгоритм поиска пути на графе между двумя вершинами.

    Результат выдавать перечислением вершин в порядке их обхода.
*/

struct item { //Структура элемента
    int data;
    item* next;
    item* prev;
};


class queue {
private:
    item* first; //Адрес первого элемента списка
    item* last; //Адрес последнего элемента списка
    int count; //Количество элементов в списке
public:
    queue()
    {
        last = NULL;
        first = NULL;
        count = 0;
    }
    void push_back(int a) //Добавление элемента в конец списка
    {
        item* newitem = new item;
        newitem->data = a;
        if (first == NULL)
            first = newitem;
        newitem->next = NULL;
        newitem->prev = last;
        if (last != NULL)
            last->next = newitem;
        last = newitem;
        count++;
    }
    void pop_front() //Удаление елемента из начала очереди
    {
        item* place = first;
        if (place != last) //Если элемент первый, но НЕ последний
        {
            place->next->prev = NULL;
            first = place->next;
        }
        else //Если элемент первый и последний
        {
        first = NULL;
        last = NULL;
        }
        delete place;
        count--;
    }

    int front()
    {
        item* place = first;
        return(place->data);
    }

    int back()
    {
        item* place = last;
        return(place->data);
    }

    bool empty() //Возвращает true если очередь пустая и false если нет
    {
        bool empt;
        if (first == NULL)
            empt = true;
        else
            empt = false;
        return empt;
    }
    int first_data() //Возвращает значение из начала очереди
    {
        return first->data;
    }
};

class breadth_first_search
{
private:
    int start_vertex, end_vertex;
    int** matrix;
    int SizeMatrix;
    queue wait;
    int* min_rast;
    bool* Visited_points;
public:
    // SizeMartix - размер матрицы, _start/end_vertex - начальная и конечная вершины
    breadth_first_search(int _SizeMatrix, int _start_vertex, int _end_vertex)
    {
        SizeMatrix = _SizeMatrix;
        start_vertex = _start_vertex;
        end_vertex = _end_vertex;
        // Создали массив
        matrix = new int* [SizeMatrix];
        for (int i = 0; i < SizeMatrix; i++)
        {
            matrix[i] = new int[SizeMatrix];
        }
        // После чего каждый элемент обнулили
        for (int i = 0; i < SizeMatrix; i++)
        {
            for (int j = 0; j < SizeMatrix; j++)
            {
                matrix[i][j] = 0;
            }
        }

        min_rast = new int[_SizeMatrix]; // min_rast - минимальное расстояние
        Visited_points = new bool[_SizeMatrix]; // Visited_points - посещенные вершины
        for (int i = 0; i < _SizeMatrix; i++)
        {
            min_rast[i] = 0; // Заполняем массив мин.расстояния до каждой вершины изначально нулями
            Visited_points[i] = false; // И массив, который проверяет посещена-ли вершина;
        }
        Visited_points[0] = true; // Т.к первый элемент уже будет всегда посещен
    }

    void FillMatrix(int indexfirst, int indexsecond, int value)
    {
        matrix[indexfirst][indexsecond] = value;
    }

    int ShowMatrixElement(int indexfirst, int indexsecond)
    {
        return(matrix[indexfirst][indexsecond]);
    }

    void Processing()
    {
        wait.push_back(0);
        min_rast[0] = 0;
        int k = 1;
        while (wait.empty() == false)
        {
            Visited_points[wait.front()] = true; // Текущую вершину от которой ищем связи помечаем посещенной
            for (int i = k; i <= end_vertex; i++)
            {
                if ((matrix[wait.front()][i] != 0) && (Visited_points[i] == false))
                {
                    if (wait.back() != i)
                    {
                        wait.push_back(i); // Добавили вершину в очередь, которую нужно будет посетить
                        //cout << " Добавили: " << i << endl;
                        min_rast[i] = min_rast[wait.front()] + 1; // Текущее мин.расстояние = мин.расстояние из вершины с которой пришли + 1
                    }
                }
            }
            //cout << endl;
            //queue.unique(); // Удаляем повторные вершины, можно наверное как-то и без этого, но не додумав
            //cout << wait.front() << endl;
            wait.pop_front(); // Удаляем первый элемент списка, после чего уходим
            k += 1; // k - отвечает за начальный элемент от которого шагаем в матрице, чтоб не делать одни и те-же действия несколько раз
        }
    }

    string Show_shortest_way()
    {
        string answer = ""; // Создали пустую строку
        int buffer = -1;
        for (int i = 0; i < SizeMatrix; i++) // Прошлись по заполненному массиву длин
        {
            if (min_rast[i] - buffer == 1)
            {
                answer += to_string(i + start_vertex) + " "; // Заполнили строчку
                buffer = min_rast[i];
            }
        }
        return(answer); // Вернули ответ
    }

};


int main() {
    setlocale(LC_ALL, "rus");
    cout << "Введите начальную вершину: ";
    int start_vertex, end_vertex;
    cin >> start_vertex;
    cout << "Введите конечную вершину: ";
    cin >> end_vertex;
    int N = abs(end_vertex - start_vertex + 1);
    breadth_first_search test(N, start_vertex, end_vertex);

    test.FillMatrix(0, 0, 0);
    test.FillMatrix(0, 0, 0);
    test.FillMatrix(0, 1, 1);
    test.FillMatrix(0, 2, 1);
    test.FillMatrix(0, 3, 1);
    test.FillMatrix(0, 4, 0);
    test.FillMatrix(0, 5, 0);
    test.FillMatrix(0, 6, 0);
    test.FillMatrix(0, 7, 0);
    test.FillMatrix(1, 0, 1);
    test.FillMatrix(1, 1, 0);
    test.FillMatrix(1, 2, 0);
    test.FillMatrix(1, 3, 0);
    test.FillMatrix(1, 4, 1);
    test.FillMatrix(1, 5, 0);
    test.FillMatrix(1, 6, 0);
    test.FillMatrix(1, 7, 0);
    test.FillMatrix(2, 0, 1);
    test.FillMatrix(2, 1, 0);
    test.FillMatrix(2, 2, 0);
    test.FillMatrix(2, 3, 0);
    test.FillMatrix(2, 4, 1);
    test.FillMatrix(2, 5, 1);
    test.FillMatrix(2, 6, 0);
    test.FillMatrix(2, 7, 0);
    test.FillMatrix(3, 0, 1);
    test.FillMatrix(3, 1, 0);
    test.FillMatrix(3, 2, 0);
    test.FillMatrix(3, 3, 0);
    test.FillMatrix(3, 4, 0);
    test.FillMatrix(3, 5, 1);
    test.FillMatrix(3, 6, 0);
    test.FillMatrix(3, 7, 0);
    test.FillMatrix(4, 0, 0);
    test.FillMatrix(4, 1, 1);
    test.FillMatrix(4, 2, 1);
    test.FillMatrix(4, 3, 0);
    test.FillMatrix(4, 4, 0);
    test.FillMatrix(4, 5, 0);
    test.FillMatrix(4, 6, 1);
    test.FillMatrix(4, 7, 0);
    test.FillMatrix(5, 0, 0);
    test.FillMatrix(5, 1, 0);
    test.FillMatrix(5, 2, 1);
    test.FillMatrix(5, 3, 1);
    test.FillMatrix(5, 4, 0);
    test.FillMatrix(5, 5, 0);
    test.FillMatrix(5, 6, 1);
    test.FillMatrix(5, 7, 0);
    test.FillMatrix(6, 0, 0);
    test.FillMatrix(6, 1, 0);
    test.FillMatrix(6, 2, 0);
    test.FillMatrix(6, 3, 0);
    test.FillMatrix(6, 4, 1);
    test.FillMatrix(6, 5, 1);
    test.FillMatrix(6, 6, 0);
    test.FillMatrix(6, 7, 1);
    test.FillMatrix(7, 0, 0);
    test.FillMatrix(7, 1, 0);
    test.FillMatrix(7, 2, 0);
    test.FillMatrix(7, 3, 0);
    test.FillMatrix(7, 4, 0);
    test.FillMatrix(7, 5, 0);
    test.FillMatrix(7, 6, 1);
    test.FillMatrix(7, 7, 0);

    /*matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[0][3] = 1;
    matrix[0][4] = 0;
    matrix[0][5] = 0;
    matrix[0][6] = 0;
    matrix[0][7] = 0;
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 0;
    matrix[1][3] = 0;
    matrix[1][4] = 1;
    matrix[1][5] = 0;
    matrix[1][6] = 0;
    matrix[1][7] = 0;
    matrix[2][0] = 1;
    matrix[2][1] = 0;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 1;
    matrix[2][5] = 1;
    matrix[2][6] = 0;
    matrix[2][7] = 0;
    matrix[3][0] = 1;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 0;
    matrix[3][4] = 0;
    matrix[3][5] = 1;
    matrix[3][6] = 0;
    matrix[3][7] = 0;
    matrix[4][0] = 0;
    matrix[4][1] = 1;
    matrix[4][2] = 1;
    matrix[4][3] = 0;
    matrix[4][4] = 0;
    matrix[4][5] = 0;
    matrix[4][6] = 1;
    matrix[4][7] = 0;
    matrix[5][0] = 0;
    matrix[5][1] = 0;
    matrix[5][2] = 1;
    matrix[5][3] = 1;
    matrix[5][4] = 0;
    matrix[5][5] = 0;
    matrix[5][6] = 1;
    matrix[5][7] = 0;
    matrix[6][0] = 0;
    matrix[6][1] = 0;
    matrix[6][2] = 0;
    matrix[6][3] = 0;
    matrix[6][4] = 1;
    matrix[6][5] = 1;
    matrix[6][6] = 0;
    matrix[6][7] = 1;
    matrix[7][0] = 0;
    matrix[7][1] = 0;
    matrix[7][2] = 0;
    matrix[7][3] = 0;
    matrix[7][4] = 0;
    matrix[7][5] = 0;
    matrix[7][6] = 1;
    matrix[7][7] = 0;*/
    char command_char;
    bool MatrixIsFill = true;
    cout << "Команды: \n 0 - Заполнить матрицу \n 1 - Вывести матрицу \n 2 - Найти кратчайший путь до конечной вершины и вывести маршрут \n 3 - Завершить программу \n Введите команду: ";
    cin >> command_char;
    while (command_char != 3)
    {
        switch (command_char)
        {
        case('0'):
            cout << "Заполните матрицу, 1 - путь имеется, 0 - пути нет: ";
            for (int i = start_vertex; i <= end_vertex; i++)
                for (int j = i + 1; j <= end_vertex; j++)
                {
                    cout << "Введите расстояние: " << i << " - " << j << " : ";
                    int ch;
                    cin >> ch;
                    test.FillMatrix(i - start_vertex, j - start_vertex, ch);
                    test.FillMatrix(j - start_vertex, i - start_vertex, ch);
                }
            MatrixIsFill = true;
            cout << " Введите команду: ";
            cin >> command_char;
            break;
        case('1'):
            if (MatrixIsFill)
            {
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        cout << test.ShowMatrixElement(i, j) << " ";
                    }
                    cout << endl;
                };
            }
            else
            {
                cout << " Ошибка, матрица не существует!";
            }

            cout << " Введите команду: ";
            cin >> command_char;
            break;
        case('2'):
        {
            test.Processing();
            cout << " Обход до конечной: " << test.Show_shortest_way();
            cout << endl << " Введите команду: ";
            cin >> command_char;
            break;
        }
        case('3'):
            command_char = 3;
            break;
        default:
            cout << " Введена некорректная команда :(, попробуйте снова: ";
            cin >> command_char;
            break;
        }
    }

    return 0;
}