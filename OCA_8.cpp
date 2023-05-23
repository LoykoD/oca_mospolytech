#include <iostream>
#include <list>
#include <string.h>
#include <string>
using namespace std;

/*
    Написать программу поиска в глубину с использованием стека, реализующую алгоритм поиска пути на не взвешенном графе между двумя вершинами.

    Результат выдавать перечислением вершин в порядке их обхода.
*/


class stack
{
private:
    int _size;
    int _storage[1000];
public:
    stack()
    {
        _size = 0;
        for (int i = 0;i < 1000;i++)
        {
            _storage[i] = 0;
        }
    }

    void push_front(int ch)
    {
        if (_size != 0)
        {
            for (int i = _size; i >= 0; i--)
                _storage[i] = _storage[i - 1];
            _storage[0] = ch;
            _size += 1;
        }
        else
        {
            _storage[0] = ch;
            _size += 1;
        }
    }

    int pop()
    {
        int b = _storage[0];
        _size--;
        for (int i = 0; i < _size; i++)
            _storage[i] = _storage[i + 1];
        return(b);
    }

    int show_pop()
    {
        return(_storage[0]);
    }

    int size()
    {
        return(_size);
    }
private:
};



class breadth_first_search
{
private:
    int start_vertex, end_vertex;
    int** matrix;
    int SizeMatrix;
    list<int> queue;
    int* min_rast;
    bool* Visited_points;
    stack _stack;
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
        Visited_points[0] = false; // Т.к первый элемент уже будет всегда посещен
    }

    void FillMatrix(int indexfirst, int indexsecond, int value)
    {
        matrix[indexfirst][indexsecond] = value;
    }

    int ShowMatrixElement(int indexfirst, int indexsecond)
    {
        return(matrix[indexfirst][indexsecond]);
    }

    string Processing()
    {
        int* rang = new int[SizeMatrix];
        for (int i = 0; i < SizeMatrix; i++)
        {
            rang[i] = 0;
        }
        _stack.push_front(0); // Записали в очередь стартовую хрень.
        rang[0] = 0;
        Visited_points[0] = false; // Первый элемент считается не посещенным
        while (_stack.size() != 0)
        {
            //cout << " Размер стека - " <<  _stack.size() << endl;

            int current_top = _stack.show_pop(); // Запомнили текущий элемент, после чего убираем его из стека
            _stack.pop();

            //cout << " Текущий элемент: " << current_top << endl;
           // cout << " Ранг current_top =" << rang[current_top] << endl;
            //cout << " current_top до цикла: " << current_top << endl;

            if (Visited_points[current_top] == false)
            {
                for (int i = end_vertex - start_vertex; i >= current_top; i--)
                {
                    //cout << end_vertex - start_vertex;
                    if ((i != current_top) && (matrix[current_top][i] != 0))
                    {
                        //cout << " Поместили в стек: " << i << endl;
                        _stack.push_front(i);
                        rang[i] = rang[current_top] + 1;
                        //cout << " current_top = " << current_top << endl;
                        //cout << " matrix[current_top][i] = " << matrix[current_top][i] << endl;
                        //cout << i << endl;
                    }
                }
                ////// Поместили вершины
                //cout << "rang _stack.show_pop() = " << _stack.show_pop() << " rang[current_top]+1 = " << rang[current_top] + 1 << endl;
               // rang[_stack.show_pop()] = rang[current_top] + 1;
                Visited_points[current_top] = true; // Вершину отметили как посещенную
            }
        }
        return(Show_shortest_way(rang));
    }

    string Show_shortest_way(int* mas)
    {
        string answer = ""; // Создали пустую строку
        int buffer = -1;
        answer += to_string(0 + start_vertex) + " "; // Добавили первый элемент (голову)
        for (int i = 1; i < SizeMatrix; i++) // Прошлись по заполненному массиву длин
        {
            if (mas[i]-mas[i-1] == 1)
            {
                answer += to_string(i + start_vertex) + " "; // Заполнили строчку
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
    
    // Тестовая матрица //
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
            if (MatrixIsFill)
            {
                cout << " Обход до конечной: " << test.Processing();
            }
            else
            {
                cout << " Матрица не заполнена!";
            }
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