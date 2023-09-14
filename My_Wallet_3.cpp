#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <ctime>
#include <algorithm>
#include "Header_For_My_Wallet.h"
using namespace std;

int main() 
{
    setlocale(LC_ALL, "Russian");  

    Finance_Manager finance_Manager; 
    while (true) 
    {
        cout << "�������� ��������:" << endl;
        cout << "1. ������� �������" << endl;
        cout << "2. ��������� �������" << endl;
        cout << "3. �������� �������" << endl;
        cout << "4. ������� �������" << endl;
        cout << "5. ������� �������" << endl;
        cout << "6. �������� ���������" << endl;
        cout << "7. ������ ���������" << endl;
        cout << "8. ������������� � ��������� ������ � ��������" << endl;
        cout << "9. ������� ������ � �������� �� �����" << endl;
        cout << "0. ����� �� ���������" << endl;

        int choice;
        cin >> choice;

        if (choice == 0) 
        {
            break;
        }

        switch (choice) 
        {
        case 1: 
        {
            // �������� ������ ��������
            cout << "������� ��� ������ ��������: ";
            string wallet_Name;
            cin >> wallet_Name;
            finance_Manager.create_Wallet(wallet_Name);
            cout << "������� '" << wallet_Name << "' ������." << endl;
            break;
        }
        case 2: 
        {
            // ���������� ��������
            cout << "������� ��� �������� ��� ����������: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "������� ����� ��� ����������: ";
            double amount;
            cin >> amount;
            finance_Manager.deposit_To_Wallet(wallet_Name, amount);
            cout << "������� '" << wallet_Name << "' �������� �� " << amount << " ������." << endl;
            break;
        }
        case 3: 
        {
            // ���������� ������� � �������
            cout << "������� ��� ��������, ���� �������� �������: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "������� ����� �������: ";
            double amount;
            cin >> amount;
            cout << "������� ��������� �������: ";
            string category;
            cin >> category;
            if (finance_Manager.add_Expense(wallet_Name, amount, category)) 
            {
                cout << "������� ������� ���������." << endl;
            }
            break;
        }
        case 4: 
        {
            // �������� ��������
            cout << "������� ��� �������� ��� ��������: ";
            string wallet_Name;
            cin >> wallet_Name;
            if (finance_Manager.remove_Wallet(wallet_Name)) 
            {
                cout << "������� '" << wallet_Name << "' ������." << endl;
            }
            else 
            {
                cout << "������� � ������ '" << wallet_Name << "' �� ������." << endl;
            }
            break;
        }
        case 5: 
        {
            // �������� ������� �� ��������
            cout << "������� ��� ��������, �� �������� ������� �������: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "������� ������ ������� ��� ��������: ";
            size_t transaction_Index;
            cin >> transaction_Index;
            if (finance_Manager.remove_Transaction(wallet_Name, transaction_Index)) 
            {
                cout << "������� ������� �������." << endl;
            }
            else 
            {
                cout << "������� � ������ '" << wallet_Name << "' �� ������ ��� ������ ������� �����������." << endl;
            }
            break;
        }
        case 6: 
        {
            // ���������� ����� ���������
            cout << "������� �������� ����� ���������: ";
            string category;
            cin >> category;
            finance_Manager.add_Category(category);
            cout << "��������� '" << category << "' ���������." << endl;
            break;
        }
        case 7: 
        {
            // ����� ������ ���������
            finance_Manager.list_Categories();
            break;
        }
        case 8: 
        {
            // ��������� � ���������� ������� � ��������� � ����
            cout << "������� ��� ����� ��� ���������� ������� � ���������: ";
            string filename;
            cin >> filename;
            finance_Manager.save_Reports_To_File(filename);
            break;
        }
        case 9: 
        {
            // ����� ������� � ��������� �� �����
            cout << "������ � ��������:" << endl;
            finance_Manager.generate_And_Save_Ratings(cout);
            break;
        }
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            break;
        }

    }
// ������ ��� ������������ ������ ���������.
finance_Manager.create_Wallet("������� 1");
finance_Manager.create_Wallet("������� 2");

finance_Manager.add_Category("��������");
finance_Manager.add_Category("���������");
finance_Manager.add_Category("�����������");

finance_Manager.deposit_To_Wallet("������� 1", 1000.0);
finance_Manager.deposit_To_Wallet("������� 2", 1500.0);

finance_Manager.add_Expense("������� 1", 300.0, "��������");
finance_Manager.add_Expense("������� 1", 50.0, "���������");
finance_Manager.add_Expense("������� 2", 200.0, "��������");
finance_Manager.add_Expense("������� 2", 100.0, "�����������");

finance_Manager.generate_And_Save_Reports("finance_report.txt");
    return 0;
}

double Transaction::get_Amount() const { return amount; }
const string& Transaction::get_Category() const { return category; }
const tm& Transaction::get_Transaction_Date() const { return transaction_Date; }

void Wallet::deposit(double amount)
{
    balance += amount;
}

bool Wallet::add_Expense(double amount, const string& category)
{
    if (balance >= amount)
    {
        balance -= amount;
        transactions.push_back(Transaction(amount, category));
        return true;
    }
    else
    {
        cout << "������������ ������� �� �������� " << name << endl;
        return false;
    }
}
const string& Wallet::get_Name() const { return name; }
double Wallet::get_Balance() const { return balance; }
const vector<Transaction>& Wallet::get_Transactions() const { return transactions; }
void Wallet::clear_Transactions() { transactions.clear(); }  // �������� ������ ����������

 //1. ����� ��� �������� ������ ��������
void Finance_Manager::create_Wallet(const string& name)
{
    wallets.push_back(Wallet(name));
}

//2. ����� ��� ���������� ��������
void Finance_Manager::deposit_To_Wallet(const string& wallet_Name, double amount)
{
    for (auto& wallet : wallets)
    {
        if (wallet.get_Name() == wallet_Name)
        {
            wallet.deposit(amount);
            break;
        }
    }
}

//3. ����� ��� ���������� ������� � �������
bool Finance_Manager::add_Expense(const string& wallet_Name,
    double amount, const string& category)
{
    for (auto& wallet : wallets)
    {
        if (wallet.get_Name() == wallet_Name)
        {
            if (wallet.add_Expense(amount, category))
            {
                return true;
            }
            break;
        }
    }
    return false;
}

//4. ����� ��� �������� �������� �� �����
bool Finance_Manager::remove_Wallet(const string& wallet_Name)
{
    auto it = remove_if(wallets.begin(), wallets.end(),
        [&](const Wallet& wallet) { return wallet.get_Name() == wallet_Name; });

    if (it != wallets.end())
    {
        wallets.erase(it, wallets.end());
        return true;
    }
    else
    {
        return false;
    }
}

//5. ����� ��� �������� ���������� �� ��������
bool Finance_Manager::remove_Transaction(const string& wallet_Name, size_t transaction_Index)
{
    for (auto& wallet : wallets)
    {
        if (wallet.get_Name() == wallet_Name)
        {
            if (transaction_Index < wallet.get_Transactions().size())
            {
                wallet.clear_Transactions();  // �������� ��� ���������� � �������� (� ������ ����������)
                return true;
            }
            break;
        }
    }
    return false;
}

//6. ����� ��� ���������� ����� ��������� ����������
void Finance_Manager::add_Category(const string& category)
{
    categories.push_back(category);
}

//7. ����� ��� ������ ������ ���������
void Finance_Manager::list_Categories() const
{
    cout << "������ ���������:" << endl;
    for (const std::string& category : categories)
    {
        cout << category << endl;
    }
}

//8. ����� ��� ��������� � ���������� ������� � �������� � ���������
void Finance_Manager::generate_And_Save_Ratings(ostream& output) const
{
    generate_And_Save_Top_Expenses(output, "��� ���������� ������� �� ������:", 7);
    generate_And_Save_Top_Expenses(output, "��� ���������� ������� �� �����:", 30);
    generate_And_Save_Top_Categories(output, "��� ��������� ���������� ������ �� ������:", 7);
    generate_And_Save_Top_Categories(output, "��� ��������� ���������� ������ �� �����:", 30);
}

//9. ����� ��� ��������� � ���������� ������ ������� ������
void Finance_Manager::generate_And_Save_Top_Expenses(ostream& output,
    const string& title, int days) const
{
    struct Expense
    {
        string wallet_Name;
        double amount;
    };

    vector<Expense> top_Expenses;

    for (const Wallet& wallet : wallets)
    {
        const vector<Transaction>& transactions = wallet.get_Transactions();
        double total_Expense = 0.0;
        time_t now;
        time(&now);

        for (const Transaction& transaction : transactions)
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            time_t transaction_Time = mktime(const_cast<tm*>(&transaction_Date));
            if (difftime(now, transaction_Time) <= days * 24 * 3600)
            {
                total_Expense += transaction.get_Amount();
            }
        }

        top_Expenses.push_back({ wallet.get_Name(), total_Expense });
    }

    // ��������� ������� � ������� ��������
    sort(top_Expenses.begin(), top_Expenses.end(), [](const Expense& a, const Expense& b)
        {
            return a.amount > b.amount;
        });

    output << title << endl;

    int count = 0;
    for (const Expense& expense : top_Expenses)
    {
        output << expense.wallet_Name << ": " << expense.amount << " ������." << endl;
        count++;
        if (count >= 3)
        {
            break;
        }
    }

    output << endl;
}

//10. ����� ��� ��������� � ���������� ������ ������� ���������
void Finance_Manager::generate_And_Save_Top_Categories(ostream& output, const string& title, int days) const
{
    map<string, double> category_Expenses;

    for (const Wallet& wallet : wallets)
    {
        const vector<Transaction>& transactions = wallet.get_Transactions();
        time_t now;
        time(&now);

        for (const Transaction& transaction : transactions)
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            time_t transaction_Time = mktime(const_cast<tm*>(&transaction_Date));
            if (difftime(now, transaction_Time) <= days * 24 * 3600)
            {
                category_Expenses[transaction.get_Category()] += transaction.get_Amount();
            }
        }
    }

    // ��������� ��������� ������ � ������� ��������
    vector<pair<string, double>> sorted_Categories(category_Expenses.begin(), category_Expenses.end());
    sort(sorted_Categories.begin(), sorted_Categories.end(),
        [](const pair<string, double>& a, const pair<string, double>& b)
        {
            return a.second > b.second;
        });

    output << title << endl;

    int count = 0;
    for (const auto& category : sorted_Categories)
    {
        output << category.first << ": " << category.second << " ������." << endl;
        count++;
        if (count >= 3)
        {
            break;
        }
    }

    output << endl;
}

//11. ����� ��� ���������� ������� � ��������� � ����
void Finance_Manager::save_Reports_To_File(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "������: �� ������� ������� ���� ��� ����������." << endl;
        return;
    }

    file << "����� �� �������� �� ����:" << endl;
    generate_Daily_Report(file);

    file << "����� �� �������� �� ������:" << endl;
    generate_Weekly_Report(file);

    file << "����� �� �������� �� �����:" << endl;
    generate_Monthly_Report(file);

    // ��������� � ���������� ���������
    generate_And_Save_Ratings(file);

    file.close();
    cout << "������ � �������� ��������� � �����: " << filename << endl;
}

//12. ����� ��� ��������� ������ �� �������� �� ����
void Finance_Manager::generate_Daily_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "����� �� �������� ��� ��������: " << wallet.get_Name() << endl;
        double daily_Total_Expense = 0.0;

        for (const Transaction& transaction : wallet.get_Transactions())
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            if (transaction_Date.tm_year == today.tm_year && transaction_Date.tm_mon == today.tm_mon &&
                transaction_Date.tm_mday == today.tm_mday)
            {
                daily_Total_Expense += transaction.get_Amount();
            }
        }

        output << "����� ������ �� �������: " << daily_Total_Expense << " ������." << endl;
    }
}

//13. ����� ��� ��������� ������ �� �������� �� ������
void Finance_Manager::generate_Weekly_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "����� �� �������� ��� ��������: " << wallet.get_Name() << endl;
        double weekly_Total_Expense = 0.0;

        for (const Transaction& transaction : wallet.get_Transactions())
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            time_t transaction_Time = mktime(const_cast<tm*>(&transaction_Date));
            if (difftime(now, transaction_Time) <= 7 * 24 * 3600)
            {
                weekly_Total_Expense += transaction.get_Amount();
            }
        }

        output << "����� ������ �� ��������� 7 ����: " << weekly_Total_Expense << " ������." << endl;
    }
}

//14. ����� ��� ��������� ������ �� �������� �� �����
void Finance_Manager::generate_Monthly_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "����� �� �������� ��� ��������: " << wallet.get_Name() << endl;
        double monthly_Total_Expense = 0.0;

        for (const Transaction& transaction : wallet.get_Transactions())
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            if (transaction_Date.tm_year == today.tm_year && transaction_Date.tm_mon == today.tm_mon)
            {
                monthly_Total_Expense += transaction.get_Amount();
            }
        }

        output << "����� ������ �� ������� �����: " << monthly_Total_Expense << " ������." << endl;
    }
}

//15. ���������� ����� ��� ����������.
void Finance_Manager::generate_And_Save_Reports(const string& filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "������: �� ������� ������� ���� ��� ����������." << endl;
        return;
    }

    file << "����� �� �������� �� ����:" << endl;
    generate_Daily_Report(file);

    file << "����� �� �������� �� ������:" << endl;
    generate_Weekly_Report(file);

    file << "����� �� �������� �� �����:" << endl;
    generate_Monthly_Report(file);

    generate_And_Save_Top_Expenses(file, "��� ���������� ������� �� ������:", 7);
    generate_And_Save_Top_Expenses(file, "��� ���������� ������� �� �����:", 30);

    generate_And_Save_Top_Categories(file, "��� ��������� ���������� ������ �� ������:", 7);
    generate_And_Save_Top_Categories(file, "��� ��������� ���������� ������ �� �����:", 30);

    file.close();
    cout << "������ � �������� ��������� � �����: " << filename << endl;
}