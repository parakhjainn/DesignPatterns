#include <iostream>
#include <string>

using namespace std;

class Email
{
private:
    string sender;
    string receiver;
    string subject;
    string body;

public:
    Email() {

    }

    Email(const string &sender, const string &receiver, const string &subject, const string &body)
    {
        this -> sender = sender;
        this -> receiver = receiver;
        this -> subject = subject;
        this -> body = body;
    }

    Email(const Email &e)
    {
        this -> sender = e.sender;
        this -> receiver = e.receiver;
        this -> subject = e.subject;
        this -> body = e.body;
    }

    // Getters and setters
    string getSender()
    {
        return sender;
    }

    void setSender(string &s)
    {
        sender = s;
    }

    string getReceiver()
    {
        return receiver;
    }

    void setReceiver(string &r)
    {
        receiver = r;
    }

    string getSubject()
    {
        return subject;
    }

    void setSubject(string &sub)
    {
        subject = sub;
    }

    string getBody()
    {
        return body;
    }

    void setBody(string &b)
    {
        body = b;
    }

    // Display method
    virtual void displayEmail()
    {
        cout << "Sender: " << sender << endl;
        cout << "Receiver: " << receiver << endl;
        cout << "Subject: " << subject << endl;
        cout << "Body: " << body << endl;
    }

    virtual ~Email() {} // Make Email polymorphic

};

class PremiumEmail : public Email
{
private:
    string cc;
    string bcc;

public:
    PremiumEmail() {

    }

    PremiumEmail(const string &sender, const string &receiver, const string &subject, const string &body, const string &cc, const string &bcc)
        : Email(sender, receiver, subject, body), cc(cc), bcc(bcc)
    {
    }

    PremiumEmail(const PremiumEmail &pe) // Use const reference for copy constructor
        : Email(pe), cc(pe.cc), bcc(pe.bcc) // Call base copy constructor
    {}

    // Getters and setters for cc and bcc
    string getCc()
    {
        return cc;
    }   
    void setCc(string &c)
    {
        cc = c;
    }
    string getBcc()
    {
        return bcc;
    }
    void setBcc(string &b)
    {
        bcc = b;
    }

    // Display method
    void displayEmail() override {
        Email::displayEmail();
        cout << "CC: "  << cc  << '\n'
             << "BCC: " << bcc << '\n';
    }
};

int main() {
    Email e1("hello@world.com", "", "test email", "this is a test email");

    PremiumEmail pe1("premium@world.com", "", "premium email", "this is a premium email", "", "");

    
    Email* basePtr = &e1; // or &pe1 for PremiumEmail

    if (dynamic_cast<PremiumEmail*>(basePtr)) {
        PremiumEmail pe2(*dynamic_cast<PremiumEmail*>(basePtr));
        pe2.displayEmail();
        cout << "Premium Email -----" << endl;
    }
    else if (dynamic_cast<Email*>(basePtr)) {
        Email e2(*basePtr);
        e2.displayEmail();
        cout << "Email -----" << endl;
    }

    basePtr = &pe1; // switch to PremiumEmail

    if (dynamic_cast<PremiumEmail*>(basePtr)) {
        PremiumEmail pe2(*dynamic_cast<PremiumEmail*>(basePtr));
        pe2.displayEmail();
        cout << "Premium Email -----" << endl;
    }
    else if (dynamic_cast<Email*>(basePtr)) {
        Email e2(*basePtr);
        e2.displayEmail();
        cout << "Email -----" << endl;
    }

    
    
    return 0;
}