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

    Email(Email &e)
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
    void displayEmail()
    {
        cout << "Sender: " << sender << endl;
        cout << "Receiver: " << receiver << endl;
        cout << "Subject: " << subject << endl;
        cout << "Body: " << body << endl;
    }
};

int main() {
    Email e1("hello@world.com", "", "test email", "this is a test email");

    Email e2(e1); // Using copy constructor

    e2.displayEmail();
    // output:
        // Sender: hello@world.com
        // Receiver: 
        // Subject: test email
        // Body: this is a test email

    // Command to compile and run the code:
        // cd copyProblem 
        // g++ -o email emailCopyConst.cpp
        // ./emailCopyConst 
    
    return 0;
}