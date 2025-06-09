#include <iostream>
#include <bits/stdc++.h>

using namespace std;


// Helper function to convert a string to SHA-256 hash (hex format)
string simpleHash(const string& input)
{
    unsigned long hash = 5381;

    for (char c : input)
    {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return to_string(hash);
}

enum class BankName
{
    DUTCH_BANGLA_BANK,
    STANDARD_CHARTERED_BANK,
    CITY_BANK,
    BRAC_BANK,
    ISLAMI_BANK

};
//Forward Declaration
class User;

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
    string accountNumber;
    double balance;
    User* user;

public:
    Account()
    {
        balance=0.0 ;
    }

    Account(const string& accountNumber, double balance = 0.0)
    {
        this->accountNumber= accountNumber;
        this->balance= balance;
    }

    string getAccountNumber() const
    {
        return accountNumber;
    }
    double getBalance() const
    {
        return balance;
    }

    void setAccountNumber(const string& accNum)
    {
        accountNumber = accNum;
    }
    void setBalance(double bal)
    {
        balance = bal;
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
    string email;
    string hashedPassword;
    Nominee nominee;
    vector<Beneficiary> BeneficiaryList;
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
        return BeneficiaryList;
    }
    vector<Account> getAccountList() const
    {
        return accountList;
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
        this->BeneficiaryList.push_back(Beneficiary);
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

class UserService
{

public:
    // Onboarding a user with nominee
    User onboardUser(const string& name, const string& nid, const string& dob,
                     const string& presentAddr, const string& permanentAddr,
                     const string& email, const string& rawPassword, Nominee& nominee)
    {
        User user(name, nid, dob, presentAddr, permanentAddr, email, rawPassword, nominee);
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
        if(account.getUser() == &user)
        {
            cout<<"Total balance is: "<<account.getBalance()<<" Tk."<<endl;
            return account.getBalance();
        }
        else
        {
            throw runtime_error("The account is not associated with the current user");
        }
    }
};

int main()
{
    /* For checking balance exception handling
    UserService userService;
    try
    {
        double balance = userService.checkTotalBalance(user, account);
    }
    catch (const runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }*/
}
