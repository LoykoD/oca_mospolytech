#include <iostream>
using namespace std;

class stack
{
public:
    int* start_mas, * end_mas, * vertex_mas, * start_array;
    stack(int n)
    {
        int *mas = new int[n];
        start_mas = mas;
        end_mas = (start_mas + 1);
        start_array = start_mas;
        vertex_mas = start_mas + n;
    }
    void push(int ch)
    {
      *end_mas = ch;
      start_mas = end_mas;
      end_mas = end_mas + 1;
    }

    int pop()
    {
      int extracted_number = *start_mas;
      *start_mas = 0;
      start_mas = start_mas - 1;
      end_mas = end_mas - 1;
      return(extracted_number);
    }

    bool stack_empty()
    {
        if (start_mas > start_array)
        {
            return(false);
        }
        else
        {
            return(true);
        }
    }

    bool stack_full()
    {
        if (end_mas <= vertex_mas)
        {
            return(false);
        }
        else
        {
            return(true);
        }
    }

private:
};

int main()
{
    int lenght_stack;
    setlocale(LC_ALL, "Russian");
    cout << "Введите размер стека: ";
    cin >> lenght_stack;
    stack stack(lenght_stack);
    char command_char = 'a';
    cout << "Тестирование программы\nКоманды:\n'p' - добавить элемент в стек\n'd' - исключить элемент из стека\n's' - остановить программу\nВведите букву:\n";
    cin >> command_char;
    while (command_char != 's')
    {
        switch (command_char)
        {
        case('p'):
            if (stack.stack_full() == false)
            {
                cout << "Введите добавляемое значение: " << endl;
                int added_number;
                cin >> added_number;
                stack.push(added_number);
                cout << "Добавили элемент " << added_number << " в стек" << endl;
                cin >> command_char;
                break;
            }
            else
            {
                cout << "Стек полностью заполнен!" << endl;
                cin >> command_char;
                break;
            }
        case('d'):
            if (stack.stack_empty() == true)
            {
                cout << "Стек пуст!" << endl;
                cin >> command_char;
                break;
            }
            else
            {
                int numberFromStack = stack.pop();
                cout << "Извлекли элемент " << numberFromStack << " из стека" << endl;
                cin >> command_char;
                break;
            }
        case('s'):
            break;
        default:
            cout << "Введена некорректная буква!" << endl << "Команды : \n'p' - добавить элемент в стек\n'd' - исключить элемент из стека\n's' - остановить программу\nВведите букву : \n";
            cin >> command_char;
            break;
        };
    }
    return(0);
}