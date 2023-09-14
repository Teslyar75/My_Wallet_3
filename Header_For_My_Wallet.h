#pragma once

class Transaction;
class Wallet;
class Finance_Manager;
// �����, �������������� ���������� (������� ��� �����)
class Transaction
{
    double amount;         // ����� ����������
    string category;  // ��������� ����������
    tm transaction_Date;    // ���� � ����� ����������

public:
    // ����������� ������ Transaction, �������������� ����� � ��������� ����������
    Transaction(double amount, const string& category)
        : amount(amount), category(category)
    {
        // ���������� ������� ���� � ����� ����������
        time_t now;
        tm localTime;
        time(&now);
        localtime_s(&localTime, &now);
        transaction_Date = localTime;
    }

    // ������ ������� � ������ ����������
    double get_Amount() const;
    const string& get_Category() const;
    const tm& get_Transaction_Date() const;

};


// �����, �������������� ������� � ������������ �������� ����������
class Wallet
{

    string name;               // ��� ��������
    double balance;                 // ������ ��������
    vector<Transaction> transactions;  // ������ ���������� � ��������

public:
    // ����������� ������ Wallet, �������������� ��� �������� � ������
    Wallet(const string& name) : name(name), balance(0.0) {}

    // ����� ��� ���������� ��������
    void deposit(double amount);

    // ����� ��� ���������� ������� � �������
    bool add_Expense(double amount, const string& category);

    // ������ ������� � ������ ��������
    const string& get_Name() const;
    double get_Balance() const;
    const vector<Transaction>& get_Transactions() const;
    void clear_Transactions();

};


// �����, ����������� ��������� � ����������
class Finance_Manager
{
    vector<Wallet> wallets;      // ������ ���������
    vector<string> categories;  // ������ ��������� ��� ���������

public:

    Finance_Manager() {}
    //1. ����� ��� �������� ������ ��������
    void create_Wallet(const string& name);


    //2. ����� ��� ���������� ��������
    void deposit_To_Wallet(const string& wallet_Name, double amount);


    //3. ����� ��� ���������� ������� � �������
    bool add_Expense(const string& wallet_Name,
        double amount, const string& category);


    //4. ����� ��� �������� �������� �� �����
    bool remove_Wallet(const string& wallet_Name);


    //5. ����� ��� �������� ���������� �� ��������
    bool remove_Transaction(const string& wallet_Name, size_t transaction_Index);


    //6. ����� ��� ���������� ����� ��������� ����������
    void add_Category(const string& category);


    //7. ����� ��� ������ ������ ���������
    void list_Categories() const;


    //8. ����� ��� ��������� � ���������� ������� � �������� � ���������
    void generate_And_Save_Ratings(ostream& output) const;


    //9. ����� ��� ��������� � ���������� ������ ������� ������
    void generate_And_Save_Top_Expenses(ostream& output,
        const string& title, int days) const;

    //10. ����� ��� ��������� � ���������� ������ ������� ���������
    void generate_And_Save_Top_Categories(ostream& output, const string& title, int days) const;

    //11. ����� ��� ���������� ������� � ��������� � ����
    void save_Reports_To_File(const string& filename) const;

    //12. ����� ��� ��������� ������ �� �������� �� ����
    void generate_Daily_Report(ostream& output) const;

    //13. ����� ��� ��������� ������ �� �������� �� ������
    void generate_Weekly_Report(ostream& output) const;

    //14. ����� ��� ��������� ������ �� �������� �� �����
    void generate_Monthly_Report(ostream& output) const;

    //15. ���������� ����� ��� ����������.
    void generate_And_Save_Reports(const string& filename);

};