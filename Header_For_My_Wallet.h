#pragma once

class Transaction;
class Wallet;
class Finance_Manager;
// Класс, представляющий транзакцию (затрату или доход)
class Transaction
{
    double amount;         // Сумма транзакции
    string category;  // Категория транзакции
    tm transaction_Date;    // Дата и время транзакции

public:
    // Конструктор класса Transaction, инициализирует сумму и категорию транзакции
    Transaction(double amount, const string& category)
        : amount(amount), category(category)
    {
        // Записываем текущую дату и время транзакции
        time_t now;
        tm localTime;
        time(&now);
        localtime_s(&localTime, &now);
        transaction_Date = localTime;
    }

    // Методы доступа к данным транзакции
    double get_Amount() const;
    const string& get_Category() const;
    const tm& get_Transaction_Date() const;

};


// Класс, представляющий кошелек с возможностью хранения транзакций
class Wallet
{

    string name;               // Имя кошелька
    double balance;                 // Баланс кошелька
    vector<Transaction> transactions;  // Список транзакций в кошельке

public:
    // Конструктор класса Wallet, инициализирует имя кошелька и баланс
    Wallet(const string& name) : name(name), balance(0.0) {}

    // Метод для пополнения кошелька
    void deposit(double amount);

    // Метод для добавления затраты в кошелек
    bool add_Expense(double amount, const string& category);

    // Методы доступа к данным кошелька
    const string& get_Name() const;
    double get_Balance() const;
    const vector<Transaction>& get_Transactions() const;
    void clear_Transactions();

};


// Класс, управляющий финансами и кошельками
class Finance_Manager
{
    vector<Wallet> wallets;      // Список кошельков
    vector<string> categories;  // Список категорий для транзакци

public:

    Finance_Manager() {}
    //1. Метод для создания нового кошелька
    void create_Wallet(const string& name);


    //2. Метод для пополнения кошелька
    void deposit_To_Wallet(const string& wallet_Name, double amount);


    //3. Метод для добавления затраты в кошелек
    bool add_Expense(const string& wallet_Name,
        double amount, const string& category);


    //4. Метод для удаления кошелька по имени
    bool remove_Wallet(const string& wallet_Name);


    //5. Метод для удаления транзакции из кошелька
    bool remove_Transaction(const string& wallet_Name, size_t transaction_Index);


    //6. Метод для добавления новой категории транзакций
    void add_Category(const string& category);


    //7. Метод для вывода списка категорий
    void list_Categories() const;


    //8. Метод для генерации и сохранения отчетов о затратах и рейтингов
    void generate_And_Save_Ratings(ostream& output) const;


    //9. Метод для генерации и сохранения списка топовых затрат
    void generate_And_Save_Top_Expenses(ostream& output,
        const string& title, int days) const;

    //10. Метод для генерации и сохранения списка топовых категорий
    void generate_And_Save_Top_Categories(ostream& output, const string& title, int days) const;

    //11. Метод для сохранения отчетов и рейтингов в файл
    void save_Reports_To_File(const string& filename) const;

    //12. Метод для генерации отчета по затратам за день
    void generate_Daily_Report(ostream& output) const;

    //13. Метод для генерации отчета по затратам за неделю
    void generate_Weekly_Report(ostream& output) const;

    //14. Метод для генерации отчета по затратам за месяц
    void generate_Monthly_Report(ostream& output) const;

    //15. Генерируем отчет для сохранения.
    void generate_And_Save_Reports(const string& filename);

};