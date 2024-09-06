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
        cout << "�������� �����: " << companyName << endl;
        cout << "��������: " << owner << endl;
        cout << "�������: " << phone << endl;
        cout << "�����: " << address << endl;
        cout << "��� ������������: " << activity << endl;
        cout << "-----------------------------" << endl;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << companyName << "," << owner << "," << phone << "," << address << "," << activity << endl;
            file.close();
        }
        else {
            cerr << "������ �������� ����� ��� ������!" << endl;
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

// ������ �������������
int main() 
{
    setlocale(0, "ru");
    DirectoryManager manager("directories.txt");

    // ���������� ����� �������
    manager.addDirectory(Directory("�������� 1", "�������� 1", "123456", "����� 1", "��������"));
    manager.addDirectory(Directory("�������� 2", "�������� 2", "654321", "����� 2", "������������"));
    manager.addDirectory(Directory("�������� 3", "�������� 3", "654000", "����� 2", "�������������"));
    manager.addDirectory(Directory("�������� 4", "�������� 4", "654001", "����� 3", "�����������"));
    manager.addDirectory(Directory("�������� 5", "�������� 5", "654003", "����� 5", "���������"));
    manager.addDirectory(Directory("�������� 6", "�������� 6", "654876", "����� 6", "�������"));

    // ����� ���� �������
    cout << "��� ������:" << endl;
    manager.showAll();

    // ����� �� �������� �����
    cout << "\n����� �� �������� ����� '�������� 1':" << endl;
    manager.searchByCompanyName("�������� 1");

    // ����� �� ���������
    cout << "\n����� �� ��������� '�������� 2':" << endl;
    manager.searchByOwner("�������� 2");

    // ����� �� ������ ��������
    cout << "\n����� �� ������ �������� '123456':" << endl;
    manager.searchByPhone("123456");

    // ����� �� ���� ������������
    cout << "\n����� �� ���� ������������ '������������':" << endl;
    manager.searchByActivity("������������");

    return 0;
}
