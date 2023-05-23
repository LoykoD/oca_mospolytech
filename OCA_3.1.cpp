#include <iostream>
using namespace std;

/*
    Двухсвязный список.

    Алгоритмы:
        Создание списка done
        Добавление элемента в конец списка done
        Добавление элемента в начало списка done
        Удаление конечного элемента списка done
        Удаление начального элемента списка done
        Поиск элемента по заданному значению поля структуры
        Добавление элемента после найденного
        Удаление найденного элемента.

    Использовать указатели
*/

struct Student
{
    string name;
    string NumberStudentTicket;
    string Facult;
    string NumberStudentGroup;
};

class List
{
private:
    class Node
    {
    private:
    public:
        Node* NextNode;
        Node* PrevNode;
        Student Data;

        Node(Student data, Node* PrevNode, Node* NextNode = nullptr)
        {
            this->Data = data;
            this->NextNode = NextNode;
            this->PrevNode = PrevNode;
        }

    };
    int SizeNode;
    Node* head;
    Node* buffer_for_find = this->head;
    Node* buffer_for_find_prew = this->head;
public:
    List()
    {
        SizeNode = 0;
        head = nullptr;
    }

    void push_back(Student data)
    {
        if (head == nullptr)
        {
            head = new Node(data,nullptr);
            SizeNode++;
        }
        else
        {
            Node* buffer = this->head;
            Node* buffer_2 = buffer;
            while (buffer->NextNode != nullptr)
            {
                cout << buffer << endl;
                buffer_2 = buffer->NextNode;
                buffer = buffer->NextNode; // нашел свободное место
                //buffer->PrevNode = buffer_2;
            }
            buffer->NextNode = new Node(data,buffer_2);
            SizeNode++;
        }
    }
    void push_front(Student data) // добавить в начало
    {
        Node* buffer = this->head;

        head = new Node(data,nullptr);
        head->NextNode = buffer;
        buffer->PrevNode = head;
        SizeNode++;
    }

    void pop_front() // Удалить в начале
    {
        Node* temp = head;
        head = head->NextNode;
        head->PrevNode = nullptr;
        delete temp;
        SizeNode--;
    }

    void pop_back() // Удалить в конце
    {
        Node* buffer = this->head;
        Node* buffer2 = this->head;
        while (buffer->NextNode != nullptr)
        {
            buffer2 = buffer;
            buffer = buffer->NextNode;
        }
        delete buffer;
        buffer2->NextNode = nullptr;
        SizeNode--;
    }

    Student FindByNameStudent(string _nameStudent)
    {
        buffer_for_find = this->head;
        buffer_for_find_prew = this->head;
        while (buffer_for_find->NextNode != nullptr)
        {
            size_t pos = buffer_for_find->Data.name.find(_nameStudent);
            if (pos != string::npos)
            {
              return(buffer_for_find->Data);
            };
            buffer_for_find_prew = buffer_for_find;
            buffer_for_find = buffer_for_find->NextNode;
        }
    }

    Student FindByFacultStudent(string _nameFacult)
    {
        buffer_for_find = this->head;
        buffer_for_find_prew = this->head;
        while (buffer_for_find->NextNode != nullptr)
        {
            size_t pos = buffer_for_find->Data.Facult.find(_nameFacult);
            if (pos != string::npos)
            {
                    return(buffer_for_find->Data);
            }
            buffer_for_find_prew = buffer_for_find;
            buffer_for_find = buffer_for_find->NextNode;
        }
    }

    Student FindByNumberStudentTicketStudent(string _NumberStudentTicket)
    {
        buffer_for_find = this->head;
        buffer_for_find_prew = this->head;
        while (buffer_for_find->NextNode != nullptr)
        {
            size_t pos = buffer_for_find->Data.NumberStudentTicket.find(_NumberStudentTicket);
            if (pos != string::npos)
            {
                return(buffer_for_find->Data);
            }
            buffer_for_find_prew = buffer_for_find;
            buffer_for_find = buffer_for_find->NextNode;
        }
    }

    Student FindByNumberStudentGroupStudent(string _NumberStudentGroup)
    {
        buffer_for_find = this->head;
        buffer_for_find_prew = this->head;
        while (buffer_for_find->NextNode != nullptr)
        {
            size_t pos = buffer_for_find->Data.NumberStudentGroup.find(_NumberStudentGroup);
            if (pos != string::npos)
            {
                return(buffer_for_find->Data);
            }
            buffer_for_find_prew = buffer_for_find;
            buffer_for_find = buffer_for_find->NextNode;
        }
    }

    void RemoveFindedElement()
    {
        if (buffer_for_find == head)
            pop_front();
        else
        {
            Node* temp = buffer_for_find;
            cout << buffer_for_find_prew->NextNode << endl;
            cout << buffer_for_find->NextNode << endl;

            buffer_for_find_prew->NextNode = buffer_for_find->NextNode;
            delete temp;
            SizeNode--;
        }

    }

    void Insert(Student _data)
    {
        Node* base = this->head;
        Node* current = buffer_for_find;
        Node* next = buffer_for_find->NextNode;
        //buffer->NextNode = new Node(data);
        current->NextNode = (new Node(_data,current))->NextNode = next->NextNode;
        SizeNode++;
    }
};

Student Fill_data()
{
    Student person;
    cout << "Введите имя студента: ";
    cin >> person.name;
    cout << "Введите факультет: ";
    cin >> person.Facult;
    cout << "Введите номер группы: ";
    cin >> person.NumberStudentGroup;
    cout << "Введите номер зачетки: ";
    cin >> person.NumberStudentTicket;
    return(person);
}

void Show_data(Student student)
{
    cout << " Имя студента: " << student.name << endl;
    cout << " Факультет:" << student.Facult << endl;
    cout << " Номер группы: " << student.NumberStudentGroup << endl;
    cout << " Номер зачетки: " << student.NumberStudentTicket << endl;
}

int main() {

    Student person;
    List list;
    person.name = "Vonya_Bebra_Da";
    person.Facult = "IT";
    person.NumberStudentGroup = "211-723";
    person.NumberStudentTicket = "123321";
    list.push_back(person);
    person.name = "Volodimir_Pehteneev";
    person.Facult = "Car";
    person.NumberStudentGroup = "211-721";
    person.NumberStudentTicket = "123399";
    list.push_back(person);
    person.name = "Volodimir_Pehteneev22";
    person.Facult = "Car";
    person.NumberStudentGroup = "211-721";
    person.NumberStudentTicket = "123399";
    list.push_front(person);

    list.pop_back();

    setlocale(LC_ALL, "rus");
    cout << "Команды:\n 1 - Добавление элемента в конец списка \n 2 - Добавление элемента в начало списка \n 3 - Удаление конечного элемента списка\n 4 - Удаление начального элемента списка \n 5 - Поиск элемента по заданному значению поля структуры и \n Добавление элемента после найденного и \n Удаление найденного элемента.\n Введите команду: ";
    char command;
    cin >> command;
    while (command != '0')
    {
        switch (command)
        {
        case('1'):
        {
            list.push_back(Fill_data());
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('2'):
        {
            list.push_front(Fill_data());
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('3'):
        {
            list.pop_back();
            cout << " Введите команду: ";
            cin >> command;
            break;
        }
        case('4'):
            list.pop_front();
            cout << " Введите команду: ";
            cin >> command;
            break;
        case('5'):
            char find_command;
            cout << " Поиск по Ф.И.О - '1' \n Поиск по факультету - '2' \n Поиск по номеру группы - '3' \n Поиск по номеру зачетки - '4' \n Введите команду: ";
            cin >> find_command;
            switch (find_command)
            {
            case('1'):
            {
                cout << "Введите Ф.И.О студента: ";
                string student_name;
                cin >> student_name;
                Student student_is_found = list.FindByNameStudent(student_name);
                if (student_is_found.name != "")
                {
                    Show_data(student_is_found);
                    cout << "Удалить? (y/n):";
                    char choice;
                    cin >> choice;
                    if (choice == 'y')
                    {
                        list.RemoveFindedElement();
                    }
                    else if (choice == 'n')
                    {
                        cout << "Добавить новый элемент после найденного? (y/n): ";
                        cin >> choice;
                        if (choice == 'y')
                        {
                            Student new_data = Fill_data();
                            list.Insert(new_data);

                        }
                    }
                }
                cout << " Введите команду: ";
                cin >> command;
                break;
            }
            case('2'):
            {
                cout << "Введите название факультета: ";
                string facult_name;
                cin >> facult_name;
                Student student_is_found = list.FindByFacultStudent(facult_name);
                if (student_is_found.Facult != "")
                {
                    Show_data(student_is_found);
                    cout << "Удалить? (y/n):";
                    char choice;
                    cin >> choice;
                    if (choice == 'y')
                    {
                        list.RemoveFindedElement();
                    }
                };
                cout << " Введите команду: ";
                cin >> command;
                break;
            }
            case('3'):
            {
                cout << "Введите номер группы: ";
                string student_number_group;
                cin >> student_number_group;
                Student student_is_found = list.FindByNumberStudentGroupStudent(student_number_group);
                if (student_is_found.NumberStudentGroup != "")
                {
                    Show_data(student_is_found);
                    cout << "Удалить? (y/n):";
                    char choice;
                    cin >> choice;
                    if (choice == 'y')
                    {
                        list.RemoveFindedElement();
                    }
                }
                cout << " Введите команду: ";
                cin >> command;
                break;
            }
            case('4'):
            {
                cout << "Введите номер зачетки: ";
                string NumberStudentTicket;
                cin >> NumberStudentTicket;
                Student student_is_found = list.FindByNumberStudentTicketStudent(NumberStudentTicket);
                if (student_is_found.NumberStudentTicket != "")
                {
                    Show_data(student_is_found);
                    char choice;
                    cin >> choice;
                    if (choice == 'y')
                    {
                        list.RemoveFindedElement();
                    }
                };
                cout << " Введите команду: ";
                cin >> command;
                break;
            }
            default:
                cout << " Неверная команда, возврат к началу программы";
                cout << " Введите команду: ";
                cin >> command;
                break;
            }
        case('8'):
            cout << " Введите команду: ";
            cin >> command;
            break;
        default:
            break;

        };
    }
    return 0;
}