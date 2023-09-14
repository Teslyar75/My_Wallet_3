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
        cout << "Выберите действие:" << endl;
        cout << "1. Создать кошелек" << endl;
        cout << "2. Пополнить кошелек" << endl;
        cout << "3. Добавить затрату" << endl;
        cout << "4. Удалить кошелек" << endl;
        cout << "5. Удалить затрату" << endl;
        cout << "6. Добавить категорию" << endl;
        cout << "7. Список категорий" << endl;
        cout << "8. Сгенерировать и сохранить отчеты и рейтинги" << endl;
        cout << "9. Вывести отчеты и рейтинги на экран" << endl;
        cout << "0. Выйти из программы" << endl;

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
            // Создание нового кошелька
            cout << "Введите имя нового кошелька: ";
            string wallet_Name;
            cin >> wallet_Name;
            finance_Manager.create_Wallet(wallet_Name);
            cout << "Кошелек '" << wallet_Name << "' создан." << endl;
            break;
        }
        case 2: 
        {
            // Пополнение кошелька
            cout << "Введите имя кошелька для пополнения: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "Введите сумму для пополнения: ";
            double amount;
            cin >> amount;
            finance_Manager.deposit_To_Wallet(wallet_Name, amount);
            cout << "Кошелек '" << wallet_Name << "' пополнен на " << amount << " гривен." << endl;
            break;
        }
        case 3: 
        {
            // Добавление затраты в кошелек
            cout << "Введите имя кошелька, куда добавить затрату: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "Введите сумму затраты: ";
            double amount;
            cin >> amount;
            cout << "Введите категорию затраты: ";
            string category;
            cin >> category;
            if (finance_Manager.add_Expense(wallet_Name, amount, category)) 
            {
                cout << "Затрата успешно добавлена." << endl;
            }
            break;
        }
        case 4: 
        {
            // Удаление кошелька
            cout << "Введите имя кошелька для удаления: ";
            string wallet_Name;
            cin >> wallet_Name;
            if (finance_Manager.remove_Wallet(wallet_Name)) 
            {
                cout << "Кошелек '" << wallet_Name << "' удален." << endl;
            }
            else 
            {
                cout << "Кошелек с именем '" << wallet_Name << "' не найден." << endl;
            }
            break;
        }
        case 5: 
        {
            // Удаление затраты из кошелька
            cout << "Введите имя кошелька, из которого удалить затрату: ";
            string wallet_Name;
            cin >> wallet_Name;
            cout << "Введите индекс затраты для удаления: ";
            size_t transaction_Index;
            cin >> transaction_Index;
            if (finance_Manager.remove_Transaction(wallet_Name, transaction_Index)) 
            {
                cout << "Затрата успешно удалена." << endl;
            }
            else 
            {
                cout << "Кошелек с именем '" << wallet_Name << "' не найден или индекс затраты некорректен." << endl;
            }
            break;
        }
        case 6: 
        {
            // Добавление новой категории
            cout << "Введите название новой категории: ";
            string category;
            cin >> category;
            finance_Manager.add_Category(category);
            cout << "Категория '" << category << "' добавлена." << endl;
            break;
        }
        case 7: 
        {
            // Вывод списка категорий
            finance_Manager.list_Categories();
            break;
        }
        case 8: 
        {
            // Генерация и сохранение отчетов и рейтингов в файл
            cout << "Введите имя файла для сохранения отчетов и рейтингов: ";
            string filename;
            cin >> filename;
            finance_Manager.save_Reports_To_File(filename);
            break;
        }
        case 9: 
        {
            // Вывод отчетов и рейтингов на экран
            cout << "Отчеты и рейтинги:" << endl;
            finance_Manager.generate_And_Save_Ratings(cout);
            break;
        }
        default:
            cout << "Некорректный выбор. Попробуйте еще раз." << endl;
            break;
        }

    }
// пример для демонстрации работы программы.
finance_Manager.create_Wallet("Кошелек 1");
finance_Manager.create_Wallet("Кошелек 2");

finance_Manager.add_Category("Продукты");
finance_Manager.add_Category("Транспорт");
finance_Manager.add_Category("Развлечения");

finance_Manager.deposit_To_Wallet("Кошелек 1", 1000.0);
finance_Manager.deposit_To_Wallet("Кошелек 2", 1500.0);

finance_Manager.add_Expense("Кошелек 1", 300.0, "Продукты");
finance_Manager.add_Expense("Кошелек 1", 50.0, "Транспорт");
finance_Manager.add_Expense("Кошелек 2", 200.0, "Продукты");
finance_Manager.add_Expense("Кошелек 2", 100.0, "Развлечения");

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
        cout << "Недостаточно средств на кошельке " << name << endl;
        return false;
    }
}
const string& Wallet::get_Name() const { return name; }
double Wallet::get_Balance() const { return balance; }
const vector<Transaction>& Wallet::get_Transactions() const { return transactions; }
void Wallet::clear_Transactions() { transactions.clear(); }  // Очистить список транзакций

 //1. Метод для создания нового кошелька
void Finance_Manager::create_Wallet(const string& name)
{
    wallets.push_back(Wallet(name));
}

//2. Метод для пополнения кошелька
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

//3. Метод для добавления затраты в кошелек
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

//4. Метод для удаления кошелька по имени
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

//5. Метод для удаления транзакции из кошелька
bool Finance_Manager::remove_Transaction(const string& wallet_Name, size_t transaction_Index)
{
    for (auto& wallet : wallets)
    {
        if (wallet.get_Name() == wallet_Name)
        {
            if (transaction_Index < wallet.get_Transactions().size())
            {
                wallet.clear_Transactions();  // Очистить все транзакции в кошельке (в данной реализации)
                return true;
            }
            break;
        }
    }
    return false;
}

//6. Метод для добавления новой категории транзакций
void Finance_Manager::add_Category(const string& category)
{
    categories.push_back(category);
}

//7. Метод для вывода списка категорий
void Finance_Manager::list_Categories() const
{
    cout << "Список категорий:" << endl;
    for (const std::string& category : categories)
    {
        cout << category << endl;
    }
}

//8. Метод для генерации и сохранения отчетов о затратах и рейтингов
void Finance_Manager::generate_And_Save_Ratings(ostream& output) const
{
    generate_And_Save_Top_Expenses(output, "Три наибольшие затраты за неделю:", 7);
    generate_And_Save_Top_Expenses(output, "Три наибольшие затраты за месяц:", 30);
    generate_And_Save_Top_Categories(output, "Три категории наибольших затрат за неделю:", 7);
    generate_And_Save_Top_Categories(output, "Три категории наибольших затрат за месяц:", 30);
}

//9. Метод для генерации и сохранения списка топовых затрат
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

    // Сортируем затраты в порядке убывания
    sort(top_Expenses.begin(), top_Expenses.end(), [](const Expense& a, const Expense& b)
        {
            return a.amount > b.amount;
        });

    output << title << endl;

    int count = 0;
    for (const Expense& expense : top_Expenses)
    {
        output << expense.wallet_Name << ": " << expense.amount << " гривен." << endl;
        count++;
        if (count >= 3)
        {
            break;
        }
    }

    output << endl;
}

//10. Метод для генерации и сохранения списка топовых категорий
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

    // Сортируем категории затрат в порядке убывания
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
        output << category.first << ": " << category.second << " гривен." << endl;
        count++;
        if (count >= 3)
        {
            break;
        }
    }

    output << endl;
}

//11. Метод для сохранения отчетов и рейтингов в файл
void Finance_Manager::save_Reports_To_File(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка: Не удалось открыть файл для сохранения." << endl;
        return;
    }

    file << "Отчет по затратам за день:" << endl;
    generate_Daily_Report(file);

    file << "Отчет по затратам за неделю:" << endl;
    generate_Weekly_Report(file);

    file << "Отчет по затратам за месяц:" << endl;
    generate_Monthly_Report(file);

    // Генерация и сохранение рейтингов
    generate_And_Save_Ratings(file);

    file.close();
    cout << "Отчеты и рейтинги сохранены в файле: " << filename << endl;
}

//12. Метод для генерации отчета по затратам за день
void Finance_Manager::generate_Daily_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "Отчет по затратам для кошелька: " << wallet.get_Name() << endl;
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

        output << "Сумма затрат за сегодня: " << daily_Total_Expense << " гривен." << endl;
    }
}

//13. Метод для генерации отчета по затратам за неделю
void Finance_Manager::generate_Weekly_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "Отчет по затратам для кошелька: " << wallet.get_Name() << endl;
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

        output << "Сумма затрат за последние 7 дней: " << weekly_Total_Expense << " рублей." << endl;
    }
}

//14. Метод для генерации отчета по затратам за месяц
void Finance_Manager::generate_Monthly_Report(ostream& output) const
{
    time_t now;
    tm today;
    time(&now);
    localtime_s(&today, &now);

    for (const Wallet& wallet : wallets)
    {
        output << "Отчет по затратам для кошелька: " << wallet.get_Name() << endl;
        double monthly_Total_Expense = 0.0;

        for (const Transaction& transaction : wallet.get_Transactions())
        {
            const tm& transaction_Date = transaction.get_Transaction_Date();
            if (transaction_Date.tm_year == today.tm_year && transaction_Date.tm_mon == today.tm_mon)
            {
                monthly_Total_Expense += transaction.get_Amount();
            }
        }

        output << "Сумма затрат за текущий месяц: " << monthly_Total_Expense << " гривен." << endl;
    }
}

//15. Генерируем отчет для сохранения.
void Finance_Manager::generate_And_Save_Reports(const string& filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка: Не удалось открыть файл для сохранения." << endl;
        return;
    }

    file << "Отчет по затратам за день:" << endl;
    generate_Daily_Report(file);

    file << "Отчет по затратам за неделю:" << endl;
    generate_Weekly_Report(file);

    file << "Отчет по затратам за месяц:" << endl;
    generate_Monthly_Report(file);

    generate_And_Save_Top_Expenses(file, "Три наибольшие затраты за неделю:", 7);
    generate_And_Save_Top_Expenses(file, "Три наибольшие затраты за месяц:", 30);

    generate_And_Save_Top_Categories(file, "Три категории наибольших затрат за неделю:", 7);
    generate_And_Save_Top_Categories(file, "Три категории наибольших затрат за месяц:", 30);

    file.close();
    cout << "Отчеты и рейтинги сохранены в файле: " << filename << endl;
}