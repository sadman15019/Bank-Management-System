#include <iostream>
#include <bits/stdc++.h>

using namespace std;


// Helper function to convert a string to SHA-256 hash (hex format)

//global counters to use user id, merchant id, transasction id, beneficiary id, admin id and accountId.
int userLoggedInId = -1;
int merchantLoggedInId= -1;
int beneficiaryLoggedInId= -1;
int adminLoggedInId= -1;
string simpleHash(const string& input)
{
    unsigned long hash = 5381;

    for (char c : input)
    {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return to_string(hash);
}

void mockExternalApiCall()
{
    cout<<"Successfully called external API"<<endl;
}

enum class BankName
{
    DUTCH_BANGLA_BANK,
    STANDARD_CHARTERED_BANK,
    CITY_BANK,
    BRAC_BANK,
    ISLAMI_BANK
};

enum class Role
{
    CUSTOMER,
    MERCHANT
};

enum class TransactionType
{
    C2C_LOCAL,
    C2C_GLOBAL,
    PAYMENT,
    REFUND,
    ATM_WITHDRAWAL
};
//Forward Declaration
class User;
class Merchant;

class Person
{
protected:
    string name;
    string nidNo;
    string dateOfBirth;
    string presentAddress;
    string parmanentAddress;

public:
    Person() {}
    Person(string name, string nidNo,string dateOfBirth, string presentAddress, string parmanentAddress)
    {
        this->name=name;
        this->nidNo=nidNo;
        this->dateOfBirth=dateOfBirth;
        this->presentAddress=presentAddress;
        this->parmanentAddress=parmanentAddress;
    }
    string getName() const
    {
        return name;
    }
    string getNidNo() const
    {
        return nidNo;
    }
    string getDateOfBirth() const
    {
        return dateOfBirth;
    }
    string getPresentAddress() const
    {
        return presentAddress;
    }
    string getPermanentAddress() const
    {
        return parmanentAddress;
    }

    // Setters
    void setName(const string& name)
    {
        this->name = name;
    }
    void setNidNo(const string& nidNo)
    {
        this->nidNo = nidNo;
    }
    void setDateOfBirth(const string& dateOfBirth)
    {
        this->dateOfBirth = dateOfBirth;
    }
    void setPresentAddress(const string& presentAddress)
    {
        this->presentAddress = presentAddress;
    }
    void setPermanentAddress(const string& parmanentAddress)
    {
        this->parmanentAddress = parmanentAddress;
    }

    /*
    Note: the purpose of 'const' here is to avoid any accidental or mal-intentional modification of ther parameter
          the purpose of '&' is to pass by reference, as pass by value copies the string , it can be costly operation for large strings.
          this pointer points to the current object of the class
    */
};

class Account
{
private:
    int accountId;
    string accountNumber;
    double balance;
    User* user;
    Merchant* merchant;
    double dailyTransaction;
    double monthlyTransaction;

public:
    Account()
    {
        balance=0.0 ;
    }

    Account(const string& accountNumber, double balance = 0.0, double dailyTransaction=0.0, double monthlyTransaction=0.0)
    {
        this->accountNumber= accountNumber;
        this->balance= balance;
        this->dailyTransaction=dailyTransaction;
        this->monthlyTransaction=monthlyTransaction;
    }

    string getAccountNumber() const
    {
        return accountNumber;
    }
    double getBalance() const
    {
        return balance;
    }
    double getDailyTransaction() const
    {
        return dailyTransaction;
    }
    double getMonthlyTransaction() const
    {
        return monthlyTransaction;
    }

    void setAccountNumber(const string& accNum)
    {
        accountNumber = accNum;
    }
    void setBalance(double bal)
    {
        balance = bal;
    }
    void setDailyTransaction(double amount)
    {
        dailyTransaction = amount;
    }
    void setMonthlyTransaction(double amount)
    {
        monthlyTransaction = amount;
    }

    void increaseDailyTransaction(double amount)
    {
        dailyTransaction+= amount;
    }
    void increaseMonthlyTransaction(double amount)
    {
        monthlyTransaction+= amount;
    }

    void resetDailyTransaction()
    {
        dailyTransaction = 0.0;
    }
    void resetMonthlyTransaction()
    {
        monthlyTransaction = 0.0;
    }

    void setUser(User* user)
    {
        this->user = user;
    }
    User* getUser() const
    {
        return user;
    }

    // Basic operations
    void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Nominee : public Person
{
private:
    string relationship;
    User* user = nullptr;

public:
    Nominee() {}

    Nominee(string name, string nid, string dob, string presentAddr, string permanentAddr, string relationship)
        : Person(name, nid, dob, presentAddr, permanentAddr)
    {
        this -> relationship= relationship;
    }

    string getRelationship() const
    {
        return relationship;
    }
    void setRelationship(const string& relationship)
    {
        this-> relationship = relationship;
    }

    User* getUser() const
    {
        return user;
    }
    void setUser(User* user)
    {
        this->user = user;
    }
    /*
    Note: the purpose of using user reference instead of directly a user cause,user and nominee has a bi-directional relationship. If i declare something like following:
       class User {
               Nominee nominee;  // has Nominee
                };

       class Nominee {
               User user;        // has User
                };
      You get an infinite loop of object construction, because : User needs a Nominee, which needs a User, which needs a Nominee, and so on forever.
      This is known as a circular dependency — and C++ doesn't allow this with full objects because it would lead to infinite memory allocation and compilation errors.
    */
};

class Beneficiary
{
private:
    string name;
    string accountNo;
    BankName bankname;
    User* user;

public:
    Beneficiary() {}

    Beneficiary(string name, string accountNo, BankName bankname, User* user)
    {
        this->name = name;
        this->accountNo = accountNo;
        this->bankname = bankname;
        this->user = user;
    }

    bool operator==(const Beneficiary& beneficiary)
    {
        return this->accountNo == beneficiary.accountNo && this->bankname==beneficiary.bankname;
    }
    // Getters
    string getName() const
    {
        return name;
    }
    string getAccountNo() const
    {
        return accountNo;
    }
    BankName getBankName() const
    {
        return bankname;
    }
    User* getUser() const
    {
        return user;
    }

    // Setters
    void setName(const string& name)
    {
        this->name = name;
    }
    void setAccountNo(const string& acc)
    {
        this->accountNo = acc;
    }
    void setBankName(BankName bank)
    {
        this->bankname = bank;
    }
    void setUser(User* user)
    {
        this->user = user;
    }
};


class User : public Person
{
private:
    int userId;
    string email;
    string hashedPassword;
    Nominee nominee;
    vector<Beneficiary> beneficiaryList;
    vector<Account> accountList;

public:
    User() {}

    User(string name, string nid, string dob, string presentAddr, string permanentAddr, string email, string rawPassword, Nominee& nominee)
        : Person(name, nid, dob, presentAddr, permanentAddr)
    {
        this->email = email;
        this->hashedPassword = simpleHash(rawPassword);
        this->nominee = nominee;
        nominee.setUser(this);
    }

    // Getters
    int getUserId() const
    {
        return userId;
    }
    string getEmail() const
    {
        return email;
    }
    string getPassword() const
    {
        return hashedPassword;
    }
    Nominee getNominee() const
    {
        return nominee;
    }
    vector<Beneficiary> getBeneficiaryList() const
    {
        return beneficiaryList;
    }
    vector<Account> getAccountList() const
    {
        return accountList;
    }

    void setUserId(int userId)
    {
        this->userId=userId;
    }
    void setEmail(const string& email)
    {
        this->email = email;
    }
    void setPassword(const string& raw)
    {
        this->hashedPassword = simpleHash(raw);
    }
    void setNominee(const Nominee& nom)
    {
        this->nominee = nom;
        this->nominee.setUser(this);
    }
    void addBeneficiary(Beneficiary Beneficiary)
    {
        Beneficiary.setUser(this);
        this->beneficiaryList.push_back(Beneficiary);
    }

    void addAccount(Account account)
    {
        account.setUser(this);
        this->accountList.push_back(account);
    }
};

class Admin
{
private:
    int adminId;
    string username;
    string email;
    string hashedPassword;

public:
    Admin() {}
    Admin(string username, string email, string rawPassword)
        : username(username), email(email), hashedPassword(simpleHash(rawPassword)) {}

    // Getters
    string getUsername() const
    {
        return username;
    }
    string getEmail() const
    {
        return email;
    }
    string getHashedPassword() const
    {
        return hashedPassword;
    }

    // Setters
    void setUsername(const string& username)
    {
        this->username = username;
    }
    void setEmail(const string& email)
    {
        this->email = email;
    }
    void setRawPassword(const string& raw)
    {
        this->hashedPassword = simpleHash(raw);
    }

    // Function to bind an account to a user (adds account to user's account list)
    void bindAccountToUser(User& user, const string& accountNumber, double initialBalance = 0.0)
    {
        Account newAccount(accountNumber, initialBalance);
        user.addAccount(newAccount);
        cout << "Admin: Bound account " << accountNumber << " to user " << user.getName() << endl;
    }
};

class Transaction
{
private:
    int transactionId;
    string senderAccountNumber;
    string receiverAccountNumber;
    double amount;
    string status;        // "SUCCESS" or "FAILED"
    string failReason;    // Reason in case of failure
    time_t timestamp;     // Epoch time of transaction

public:
    Transaction() {}

    Transaction(const string& sender, const string& receiver, double amount,
                const string& status, const string& failReason, time_t timestamp)
        : senderAccountNumber(sender), receiverAccountNumber(receiver),
          amount(amount), status(status), failReason(failReason), timestamp(timestamp) {}


    int getTransactionId() const
    {
        return transactionId;
    }
    string getSenderAccountNumber() const
    {
        return senderAccountNumber;
    }
    string getReceiverAccountNumber() const
    {
        return receiverAccountNumber;
    }
    double getAmount() const
    {
        return amount;
    }
    string getStatus() const
    {
        return status;
    }
    string getFailReason() const
    {
        return failReason;
    }
    time_t getTimestamp() const
    {
        return timestamp;
    }


    void setTransactionId(int transactionId)
    {
        this->transactionId=transactionId;
    }
    void setSenderAccountNumber(const string& sender)
    {
        senderAccountNumber = sender;
    }
    void setReceiverAccountNumber(const string& receiver)
    {
        receiverAccountNumber = receiver;
    }
    void setAmount(double amt)
    {
        amount = amt;
    }
    void setStatus(const string& stat)
    {
        status = stat;
    }
    void setFailReason(const string& reason)
    {
        failReason = reason;
    }
    void setTimestamp(time_t ts)
    {
        timestamp = ts;
    }
};

class Merchant
{
private:
    int merchantId;
    string name;
    string tinId;
    string address;
    Account account;

public:
    // Default constructor
    Merchant() {}

    // Parameterized constructor
    Merchant(int id, const string& name, const string& tin, const string& addr, const Account& acc)
        : name(name), tinId(tin), address(addr), account(acc) {}

    // Setters
    void setMerchantId(int id)
    {
        merchantId = id;
    }
    void setName(const string& n)
    {
        name = n;
    }
    void setTinId(const string& tin)
    {
        tinId = tin;
    }
    void setAddress(const string& addr)
    {
        address = addr;
    }
    void setAccount(const Account& acc)
    {
        account = acc;
    }

    // Getters
    int getMerchantId() const
    {
        return merchantId;
    }
    string getName() const
    {
        return name;
    }
    string getTinId() const
    {
        return tinId;
    }
    string getAddress() const
    {
        return address;
    }
    Account getAccount() const
    {
        return account;
    }


};

class LimitDetails
{
private:
    double perTransactionLimit;
    double dailyTransactionLimit;
    double monthlyTransactionLimit;
    double minBalanceRequirementForCustomer;
    double minBalanceRequirementForMerchant;
    int maxDailyTransactions;
    int maxMonthlyTransactions;

public:
    LimitDetails() {}

    LimitDetails( double perTransactionLimit, double dailyTransactionLimit, double monthlyTransactionLimit, double minBalanceRequirementForCustomer
                  ,double minBalanceRequirementForMerchants, int maxDailyTransactions, int maxMonthlyTransactions)
    {
        this->perTransactionLimit=perTransactionLimit;;
        this->dailyTransactionLimit=dailyTransactionLimit;
        this->monthlyTransactionLimit=monthlyTransactionLimit;
        this->minBalanceRequirementForCustomer=minBalanceRequirementForCustomer;
        this->minBalanceRequirementForMerchant=minBalanceRequirementForMerchant;
        this->maxDailyTransactions=maxDailyTransactions;
        this->maxMonthlyTransactions=maxMonthlyTransactions;
    }

    double getPerTransactionLimit() const
    {
        return perTransactionLimit;
    }
    double getDailyTransactionLimit() const
    {
        return dailyTransactionLimit;
    }
    double getMonthlyTransactionLimit() const
    {
        return monthlyTransactionLimit;
    }
    double getMinBalanceRequirementForCustomer() const
    {
        return minBalanceRequirementForCustomer;
    }
    double getMinBalanceRequirementForMerchant() const
    {
        return minBalanceRequirementForMerchant;
    }
    int getMaxDailyTransactions() const
    {
        return maxDailyTransactions;
    }
    int getMaxMonthlyTransactions() const
    {
        return maxMonthlyTransactions;
    }


    void setDailyTransactionLimit(double dailyTransactionLimit)
    {
        this->dailyTransactionLimit = dailyTransactionLimit;
    }
    void setMonthlyTransactionLimit(double monthlyTransactionLimit)
    {
        this->monthlyTransactionLimit = monthlyTransactionLimit;
    }
    void setMinBalanceRequirementForCustomer(double minBalanceRequirementForCustomer)
    {
        this->minBalanceRequirementForCustomer = minBalanceRequirementForCustomer;
    }
    void setMinBalanceRequirementForMerchant(double minBalanceRequirementForMerchant)
    {
        this->minBalanceRequirementForMerchant = minBalanceRequirementForMerchant;
    }
    void setMaxDailyTransactions(int maxDailyTransactions)
    {
        this->maxDailyTransactions = maxDailyTransactions;
    }
    void setMaxMonthlyTransactions(int maxMonthlyTransactions)
    {
        this->maxMonthlyTransactions = maxMonthlyTransactions;
    }
};

//global database for all entities
vector<User> userList;
vector<Admin>adminList;
vector<Account>accountList;
vector<Transaction>transactionList;
vector<Merchant>merchantList;
class UserService
{

public:
    // Onboarding a user with nominee
    User onboardUser(const string& name, const string& nid, const string& dob,
                     const string& presentAddr, const string& permanentAddr,
                     const string& email, const string& rawPassword, Nominee& nominee)
    {
        User user(name, nid, dob, presentAddr, permanentAddr, email, rawPassword, nominee);
        user.setUserId(userList.size()+1);
        userList.push_back(user);
        cout << "User onboarded successfully: " << name << endl;
        return user;
    }
    // Update personal information (by email)
    void updatePersonalInfo(User& user, const string& email, const string& newPresentAddr, const string& newPermanentAddr, const string& existingPassword, const string& newPassword)
    {
        if( (existingPassword.empty() && !newPassword.empty()) || (!existingPassword.empty() && newPassword.empty()) )
        {
            cout<<"To change password both existing password and new password must be given"<<endl;
        }
        if(!newPassword.empty())
        {
            if(user.getPassword()==simpleHash(existingPassword))
            {
                user.setPassword(newPassword);
            }
            else
            {
                cout<<"Current Password is wrong."<<endl;
            }
        }
        if(!email.empty())
        {
            user.setEmail(email);
        }
        if(!newPresentAddr.empty())
        {
            user.setPresentAddress(newPresentAddr);
        }
        if(!newPermanentAddr.empty())
        {
            user.setPermanentAddress(newPermanentAddr);
        }
    }

    void addBeneficiary(User& user, const Beneficiary& beneficiary)
    {
        user.addBeneficiary(beneficiary);
    }

    // Check balance of all accounts of a user
    double checkTotalBalance(User& user, Account& account)
    {
        try
        {
            if(account.getUser() != &user)
            {
                throw runtime_error("The account is not associated with the current user");
            }
            cout<<"Total balance is: "<<account.getBalance()<<" Tk."<<endl;
            return account.getBalance();

        }

        catch(const exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }


    bool sendMoneyToLocal(Account& senderAccount, Account& receiverAccount, double amount, const LimitDetails& limitDetails)
    {
        double originalSenderBalance = senderAccount.getBalance();
        double originalReceiverBalance = receiverAccount.getBalance();
        double originalSenderDaily = senderAccount.getDailyTransaction();
        double originalReceiverDaily = receiverAccount.getDailyTransaction();
        double originalSenderMonthly = senderAccount.getMonthlyTransaction();
        double originalReceiverMonthly = receiverAccount.getMonthlyTransaction();
        try
        {
            if (amount > limitDetails.getPerTransactionLimit())
                throw runtime_error("Transaction amount exceeds per transaction limit");

            if (senderAccount.getBalance() < amount)
                throw runtime_error("Sender has insufficient balance");

            if (senderAccount.getDailyTransaction() + amount > limitDetails.getDailyTransactionLimit())
                throw runtime_error("Sender exceeds daily transaction limit");

            if (senderAccount.getMonthlyTransaction() + amount > limitDetails.getMonthlyTransactionLimit())
                throw runtime_error("Sender exceeds monthly transaction limit");

            senderAccount.withdraw(amount);

            if (senderAccount.getBalance() < limitDetails.getMinBalanceRequirementForCustomer())
                throw runtime_error("Sender balance below minimum requirement");

            receiverAccount.deposit(amount);

            if (receiverAccount.getDailyTransaction() + amount > limitDetails.getDailyTransactionLimit())
                throw runtime_error("Receiver exceeds daily tran5saction limit");

            if (receiverAccount.getMonthlyTransaction() + amount > limitDetails.getMonthlyTransactionLimit())
                throw runtime_error("Receiver exceeds monthly transaction limit");

            cout << "Local transfer of " << amount << " Tk successful." << endl;
            return true;
        }
        catch (const exception& ex)
        {
            senderAccount.setBalance(originalSenderBalance);
            receiverAccount.setBalance(originalReceiverBalance);
            senderAccount.setDailyTransaction(originalSenderDaily);
            receiverAccount.setDailyTransaction(originalReceiverDaily);
            senderAccount.setMonthlyTransaction(originalSenderMonthly);
            receiverAccount.setMonthlyTransaction(originalReceiverMonthly);

            cout << "Transaction failed: " << ex.what() << endl;
            return false;
        }
    }

    bool sendMoneyToGlobal(User& user, Account& senderAccount, Beneficiary& beneficiary, double amount, const LimitDetails& limitDetails, BankName BankName)
    {
        double originalSenderBalance = senderAccount.getBalance();
        double originalSenderDaily = senderAccount.getDailyTransaction();
        double originalSenderMonthly = senderAccount.getMonthlyTransaction();
        try
        {
            auto it = find(user.getBeneficiaryList().begin(),user.getBeneficiaryList().end(),beneficiary);
            if(it==user.getBeneficiaryList().end())
            {
                throw runtime_error("The receiver is not in the beneficiary list of the sender user");
            }
            if (amount > limitDetails.getPerTransactionLimit())
                throw runtime_error("Transaction amount exceeds per transaction limit");

            if (senderAccount.getBalance() < amount)
                throw runtime_error("Sender has insufficient balance");

            if (senderAccount.getDailyTransaction() + amount > limitDetails.getDailyTransactionLimit())
                throw runtime_error("Sender exceeds daily transaction limit");

            if (senderAccount.getMonthlyTransaction() + amount > limitDetails.getMonthlyTransactionLimit())
                throw runtime_error("Sender exceeds monthly transaction limit");

            senderAccount.withdraw(amount);

            if (senderAccount.getBalance() < limitDetails.getMinBalanceRequirementForCustomer())
                throw runtime_error("Sender balance below minimum requirement");


            mockExternalApiCall();

            cout << "Gloabal transfer of " << amount << " Tk successful." << endl;
            return true;
        }
        catch (const exception& ex)
        {
            senderAccount.setBalance(originalSenderBalance);
            senderAccount.setDailyTransaction(originalSenderDaily);
            senderAccount.setMonthlyTransaction(originalSenderMonthly);
            cout << "Transaction failed: " << ex.what() << endl;
            return false;
        }
    }


};

class AdminService
{
public:
    void setDailyTransactionLimit(LimitDetails& limitDetails, double dailyTransactionLimit)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setDailyTransactionLimit(dailyTransactionLimit);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    void setMonthlyTransactionLimit(LimitDetails& limitDetails, double monthlyTransactionLimit)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setMonthlyTransactionLimit(monthlyTransactionLimit);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    void setMinBalanceRequirementForCustomer(LimitDetails& limitDetails, double minBalanceRequirementForCustomer)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setMinBalanceRequirementForCustomer(minBalanceRequirementForCustomer);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    void setMinBalanceRequirementForMerchant(LimitDetails& limitDetails, double minBalanceRequirementForMerchant)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setMinBalanceRequirementForMerchant(minBalanceRequirementForMerchant);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    void setMaxDailyTransactions(LimitDetails& limitDetails, double maxDailyTransactions)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setMaxDailyTransactions(maxDailyTransactions);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    void setMaxMonthlyTransactions(LimitDetails& limitDetails, double maxMonthlyTransactions)
    {
        if(adminLoggedInId!=-1)
        {
            limitDetails.setMaxMonthlyTransactions(maxMonthlyTransactions);
        }
        else
        {
            cout<<"Currently No Admin is logged in for setting limit"<<endl;
        }
    }
    vector<User> getUserDetails(string email,string nidNo)
    {
        vector<User>result;
        if(!email.empty())
        {
            if(!nidNo.empty())
            {
                for(int i=0; i<userList.size(); i++)
                {
                    if(userList[i].getEmail()==email && userList[i].getNidNo()==nidNo)
                    {
                        result.push_back(userList[i]);
                    }
                }
            }
            else
            {
                for(int i=0; i<userList.size(); i++)
                {
                    if(userList[i].getEmail()==email)
                    {
                        result.push_back(userList[i]);
                    }
                }
            }
        }
        else if(!nidNo.empty())
        {
            for(int i=0; i<userList.size(); i++)
            {
                if(userList[i].getNidNo()==nidNo)
                {
                    result.push_back(userList[i]);
                }
            }
        }
        else
        {
            result=userList;
        }
        return result;
    }
    vector<Account> getAccountDetails(string accountNo)
    {
        vector<Account>result;
        if(!accountNo.empty())
        {
            for(int i=0; i<accountList.size(); i++)
            {
                if(accountList[i].getAccountNumber()==accountNo)
                {
                    result.push_back(accountList[i]);
                }
            }
        }
        else
        {
            result=accountList;
        }
        return result;
    }
    vector<Merchant> getMerchantDetails(string tinId)
    {
        vector<Merchant>result;
        if(!tinId.empty())
        {
            for(int i=0; i<merchantList.size(); i++)
            {
                if(merchantList[i].getTinId()==tinId)
                {
                    result.push_back(merchantList[i]);
                }
            }
        }
        else
        {
            result=merchantList;
        }
        return result;
    }
    vector<Transaction> getTransactionDetails(int transactionId)
    {
        vector<Transaction>result;
        if(transactionId!=-1)
        {
            for(int i=0; i<transactionList.size(); i++)
            {
                if(transactionList[i].getTransactionId()==transactionId)
                {
                    result.push_back(transactionList[i]);
                }
            }
        }
        else
        {
            result=transactionList;
        }
        return result;
    }
};

/*Todo:
 Transactions -> merchant Payment, Atm withdrawal
 merchant onboarding, login, accept customer payment, refund customers.
 admin login, view list of users with details, block/suspend/reactivate accounts, view a transaction details
 Use data structures instead of database for crud operartions
*/

int main()
{

}
