#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Directory 
{
private:
    string companyName;
    string owner;
    string phone;
    string address;
    string activity;

public:
    Directory(const string& cName, const string& o, const string& p, const string& a, const string& act)
        : companyName(cName), owner(o), phone(p), address(a), activity(act) {}

    string getCompanyName() const { return companyName; }
    string getOwner() const { return owner; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getActivity() const { return activity; }

    void display() const {
        cout << "Название фирмы: " << companyName << endl;
        cout << "Владелец: " << owner << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Род деятельности: " << activity << endl;
        cout << "-----------------------------" << endl;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << companyName << "," << owner << "," << phone << "," << address << "," << activity << endl;
            file.close();
        }
        else {
            cerr << "Ошибка открытия файла для записи!" << endl;
        }
    }
};

class DirectoryManager 
{
private:
    vector<Directory> directories;
    string filename;

    void loadFromFile() 
    {
        ifstream file(filename);
        string line;
        while (getline(file, line)) 
        {
            size_t pos = 0;
            string token;
            vector<string> fields;
            while ((pos = line.find(',')) != string::npos) 
            {
                token = line.substr(0, pos);
                fields.push_back(token);
                line.erase(0, pos + 1);
            }
            fields.push_back(line);

            if (fields.size() == 5) 
            {
                directories.push_back(Directory(fields[0], fields[1], fields[2], fields[3], fields[4]));
            }
        }
        file.close();
    }

public:
    DirectoryManager(const string& file) : filename(file) 
    {
        loadFromFile();
    }

    void addDirectory(const Directory& dir) 
    {
        directories.push_back(dir);
        dir.saveToFile(filename);
    }

    void showAll() const {
        for (const auto& dir : directories) 
        {
            dir.display();
        }
    }

    void searchByCompanyName(const string& name) const 
    {
        for (const auto& dir : directories) 
        {
            if (dir.getCompanyName() == name) 
            {
                dir.display();
            }
        }
    }

    void searchByOwner(const string& owner) const 
    {
        for (const auto& dir : directories) 
        {
            if (dir.getOwner() == owner) 
            {
                dir.display();
            }
        }
    }

    void searchByPhone(const string& phone) const 
    {
        for (const auto& dir : directories) 
        {
            if (dir.getPhone() == phone) 
            {
                dir.display();
            }
        }
    }

    void searchByActivity(const string& activity) const 
    {
        for (const auto& dir : directories) 
        {
            if (dir.getActivity() == activity) 
            {
                dir.display();
            }
        }
    }
};

// Пример использования
int main() 
{
    setlocale(0, "ru");
    DirectoryManager manager("directories.txt");

    // Добавление новых записей
    manager.addDirectory(Directory("Компания 1", "Владелец 1", "123456", "Адрес 1", "Торговля"));
    manager.addDirectory(Directory("Компания 2", "Владелец 2", "654321", "Адрес 2", "Производство"));
    manager.addDirectory(Directory("Компания 3", "Владелец 3", "654000", "Адрес 2", "Строительство"));
    manager.addDirectory(Directory("Компания 4", "Владелец 4", "654001", "Адрес 3", "Рыболовство"));
    manager.addDirectory(Directory("Компания 5", "Владелец 5", "654003", "Адрес 5", "Логистика"));
    manager.addDirectory(Directory("Компания 6", "Владелец 6", "654876", "Адрес 6", "Закупка"));

    // Показ всех записей
    cout << "Все записи:" << endl;
    manager.showAll();

    // Поиск по названию фирмы
    cout << "\nПоиск по названию фирмы 'Компания 1':" << endl;
    manager.searchByCompanyName("Компания 1");

    // Поиск по владельцу
    cout << "\nПоиск по владельцу 'Владелец 2':" << endl;
    manager.searchByOwner("Владелец 2");

    // Поиск по номеру телефона
    cout << "\nПоиск по номеру телефона '123456':" << endl;
    manager.searchByPhone("123456");

    // Поиск по роду деятельности
    cout << "\nПоиск по роду деятельности 'Производство':" << endl;
    manager.searchByActivity("Производство");

    return 0;
}
