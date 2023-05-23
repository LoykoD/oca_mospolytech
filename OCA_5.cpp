
#include <iostream>
#include <fstream>
using namespace std;

/*
    В предыдущую программу по работе с деревом добавить метод удаления элемента.
   
    Операции по работе с деревом:
        Добавить элемент done
        Поиск элемента done
        Обход дерева done
        Удаление элемента done
*/

class Tree
{
private:
    class Branch
    {
    public:
        Branch* left; // Указатель соответственно на левую/правую вершину
        Branch* right;
        int data;

        Branch(int data, Branch* leftBranch = nullptr, Branch* rigthBranch = nullptr)
        {
            this->data = data;
            this->left = leftBranch;
            this->right = rigthBranch;
        }
    };

    void save(Branch*& _Branch) // Рекурсия для поиска
    {
        if (NULL == _Branch)
            return;
        cout << _Branch->data;
        fout << _Branch->data << "\n";
        save(_Branch->left); // Сначала копаем влево, потом вправо
        save(_Branch->right);
    }

    Branch* root; // Корень
    int count_roots; // Счетчик вершин
public:
    ofstream fout; // обозначили сразу штучку для файла, создать файл в функции с рекурсией как-то не удалось, выдает ошибку при передаче в функцию save вторым аргументом файл.
    Tree()
    {
        root = nullptr; // Корешок изначально без указателя
        count_roots = 0;
        fout.open("test.txt"); // сразу создали файлик, возможно это лишнее, но как-то по другому придумать не смог, проблема описана на 36 строчке
    }

    void push(int data) // Взял пример названия с прошлой лабы, просто добавляет значение в дерево
    {
        if (root == nullptr) // Обработали корень
        {
            root = new Branch(data);
            count_roots++;
        }
        else
        {
            Branch* buffer = this->root;
            while (buffer->right != nullptr && buffer->left != nullptr) // Находим свободную ветку чтоб поместить наше значение
            {
                if (data > buffer->data)
                {
                    buffer = buffer->right;
                }
                else
                {
                    buffer = buffer->left;
                }
            }
            if (data > buffer->data)
            {
                buffer->right = new Branch(data);
                count_roots++;
            }
            else
            {
                buffer->left = new Branch(data);
                count_roots++;
            }
        }
    }

    int find_element(int data) // Функция поиска элемента, возвращает поле Даты.
    {
        Branch* buffer = this->root; // buffer - временная переменная
        while (buffer->data != data)
        {
            if (data > buffer->data)
            {
                buffer = buffer->right;
            }
            else
            {
                buffer = buffer->left;
            }
        }
        return(buffer->data);
    }

    void delete_element(int element)
    {
        // Находим дату нашего элемента, после чего удаляем

        Branch* removing_element = root;
        while (removing_element->data != element)
        {
            if (removing_element->data < element)
            {
                removing_element = removing_element->right;
            }
            else
            {
                removing_element = removing_element->left;
            }
        }
        

        if (removing_element == root) // Если это корень нашей всей хорошей истории :>
        {
            root = nullptr;
        }
        else
        {
            Branch* current_element = this->root;
            Branch* prev_element = this->root; // Запоминаем предыдущее звено каждый раз.

            while (prev_element->right->data != removing_element->data && prev_element->left->data != removing_element->data) // Находим ветку с нашим значением
            {
                if (removing_element->data > current_element->data)
                {
                    current_element = current_element->right;
                }
                else
                {
                    current_element = current_element->left;
                }
                prev_element = current_element;
            }
            if (prev_element->left == removing_element)
            {
                prev_element->left = nullptr; // Просто обнуляем указатель и все, пробовал еще добавить delete removing_element, но выдает ошибку почему-то :(
            }
            else
            {
                prev_element->right = nullptr;
            }
        }
    }

    void save_to_file()
    {
        save(root);
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    Tree test;
    // какие-то проверякалки ниже
    test.push(5);
    test.push(3);
    test.push(10);
    test.push(1);
    test.push(8);
    test.push(4);
    test.push(18);

    cout << " Команды: 1 - добавить элемент в дерево\n 2 - найти элемент\n 3 - сохранить\n 0 - остановить программу.\n Введите команду: ";
    char command;
    cin >> command;
    while (command != '0')
    {
        switch (command)
        {
        case('1'):
            int element;
            cout << " Введите значение элемента: ";
            cin >> element;
            test.push(element);
            cout << " Введите команду: ";
            cin >> command;
            break;
        case('2'):
        {
            cout << "Введите значение элемента: ";
            int element_for_find;
            cin >> element_for_find;
            cout << " Найденный элемент: " << test.find_element(element_for_find) << endl;
            cout << " Удалить?(y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y')
            {
                test.delete_element(test.find_element(element_for_find));
            }
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('3'):
            test.save_to_file();
            cout << " Введите команду: ";
            cin >> command;
            break;
        case('0'):
            break;
        default:
            cout << " Команда не найдена, введите снова:(" << endl;
            cin >> command;
            break;
        }
    }
    return 0;
}