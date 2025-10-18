#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Forward declarations
class Topic;
class Subscriber;

class Message {
    string content;

public:
    Message(const string& content) : content(content) {}

    string getContent() const {
        return content;
    }
};

class Subscriber {
    string name;

public:
    Subscriber(const string& name) : name(name) {}

    void onMessage(const Message& message, const string& topicName, const string& publisherName) const {
        cout << name << " got a message from topic '" << topicName 
             << "': " << message.getContent() << " by " << publisherName <<  endl;
    }

    string getName() const {
        return name;
    }
};

class Topic {
    string name;
    vector<Subscriber*> subscribers;  // AGGREGATION: Raw pointers to independent subscribers

public:
    Topic(const string& name) : name(name) {}

    void subscribe(Subscriber* subscriber) {
        // Prevent duplicate subscriptions
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it == subscribers.end()) {
            subscribers.push_back(subscriber);
            cout << "✓ " << subscriber->getName() << " subscribed to " << name << endl;
        } else {
            cout << "! " << subscriber->getName() << " already subscribed to " << name << endl;
        }
    }

    void unsubscribe(Subscriber* subscriber) {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
            cout << "✓ " << subscriber->getName() << " unsubscribed from " << name << endl;
        } else {
            cout << "! " << subscriber->getName() << " was not subscribed to " << name << endl;
        }
    }
    
    void publish(const Message& message, const string& publisherName) {
        cout << "\n📢 Publishing to topic '" << name << "': \"" 
             << message.getContent() << "\" from " << publisherName << endl;
        
        if (subscribers.empty()) {
            cout << "   (No subscribers)" << endl;
        } else {
            for (auto* subscriber : subscribers) {
                subscriber->onMessage(message, name, publisherName);
            }
        }
    }

    string getName() const {
        return name;
    }
};

class Publisher {
    string name;  // Add this
    vector<Topic*> allowedTopics;

public:
    Publisher() {}

    Publisher(const string& name) : name(name) {}  // Add name parameter

    void addTopic(Topic* topic) {
        allowedTopics.push_back(topic);
    }

    void publish(Topic* topic, const Message& content) {
        auto it = find(allowedTopics.begin(), allowedTopics.end(), topic);
        if (it == allowedTopics.end()) {
            throw invalid_argument("Not allowed to publish to this topic");
        }
        topic->publish(content, name);
    }
};

int main() {
    Subscriber messi("Messi");
    Subscriber ronaldo("Ronaldo");
    Subscriber techGuru("Technical Guruji");
    Subscriber mkbhd("MKBHD");
    
    cout << "Created 4 independent subscribers\n" << endl;

    cout << "--- Creating Topics ---" << endl;
    Topic sportsTopic("Sports");
    Topic techTopic("Tech");
    Topic entertainmentTopic("Entertainment");
    
    cout << "\n--- Subscribing to Topics ---" << endl;
    
    // AGGREGATION: Subscribe existing subscribers to topics
    sportsTopic.subscribe(&messi);
    sportsTopic.subscribe(&ronaldo);
    
    techTopic.subscribe(&techGuru);
    techTopic.subscribe(&mkbhd);
    
    // AGGREGATION Key Feature: Same subscriber can subscribe to multiple topics
    cout << "\n--- Demonstrating Multi-Topic Subscription ---" << endl;
    messi.getName();  // Messi subscribes to multiple topics
    sportsTopic.subscribe(&messi);  // Already subscribed
    techTopic.subscribe(&messi);     // Now subscribed to Tech too!
    entertainmentTopic.subscribe(&messi);  // And Entertainment!
    
    cout << "\n--- Setting up Publisher ---" << endl;
    Publisher espn("ESPN");
    Publisher techCrunch("TC");

    espn.addTopic(&sportsTopic);
    espn.addTopic(&entertainmentTopic);
    techCrunch.addTopic(&techTopic);

    cout << "\n--- Publishing Messages ---" << endl;
    espn.publish(&sportsTopic, Message("Football match tonight!"));
    espn.publish(&entertainmentTopic, Message("New movie trailer dropped!"));
    techCrunch.publish(&techTopic, Message("New iPhone 17 released!"));

    cout << "\n--- Unsubscribing from a Topic ---" << endl;
    techTopic.unsubscribe(&messi);
    cout << "Messi is still alive and subscribed to other topics!\n" << endl;

    cout << "--- Publishing Again After Unsubscribe ---" << endl;
    techCrunch.publish(&techTopic, Message("AI breakthrough announced!"));
    // Messi won't receive this message from Tech topic
    
    espn.publish(&sportsTopic, Message("Champions League final!"));
    // But Messi still receives Sports messages

    return 0;
}