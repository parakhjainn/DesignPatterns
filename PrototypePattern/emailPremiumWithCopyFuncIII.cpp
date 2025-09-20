/* Protoype Pattern*/

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Prototype
{
public:
    virtual T *copy() const = 0; // pure virtual
    virtual ~Prototype() = default;
};

class Email : public Prototype<Email>
{
private:
    string sender;
    string receiver;
    string subject;
    string body;

public:
    Email()
    {
    }

    Email(const string &sender, const string &receiver, const string &subject, const string &body)
    {
        this->sender = sender;
        this->receiver = receiver;
        this->subject = subject;
        this->body = body;
    }

    Email(const Email &e)
    {
        this->sender = e.sender;
        this->receiver = e.receiver;
        this->subject = e.subject;
        this->body = e.body;
    }

    Email *copy() const override
    {
        return new Email(*this); // Use copy constructor
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
    PremiumEmail()
    {
    }

    PremiumEmail(const string &sender, const string &receiver, const string &subject, const string &body, const string &cc, const string &bcc)
        : Email(sender, receiver, subject, body), cc(cc), bcc(bcc)
    {
    }

    PremiumEmail(const PremiumEmail &pe)    // Use const reference for copy constructor
        : Email(pe), cc(pe.cc), bcc(pe.bcc) // Call base copy constructor
    {
    }

    PremiumEmail *copy() const override
    {
        return new PremiumEmail(*this); // Use copy constructor
    }

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
    void displayEmail() override
    {
        Email::displayEmail();
        cout << "CC: " << cc << '\n'
             << "BCC: " << bcc << '\n';
    }
};

int main()
{
    Email e1("hello@world.com", "sender", "test email", "this is a test email");

    PremiumEmail pe1("premium@world.com", "p semder", "premium email", "this is a premium email", "cc", "bcc");

    Email e2 = *e1.copy(); // Using copy method

    PremiumEmail pe2 = *pe1.copy(); // Using copy method

    e2.displayEmail();
    pe2.displayEmail();

    return 0;
}