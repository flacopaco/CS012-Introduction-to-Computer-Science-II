#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "BBoard.h"
#include "Message.h"
#include "Topic.h"
#include "Reply.h"
#include "User.h"

using namespace std;

/*
  string title;
  vector<User> userList;
  User currentUser;
  vector<Message> messageList;
*/

// Constructs a board with a default title,
// empty user & message lists,
// and the "default" User
BBoard::BBoard()
    : title(""), currentUser(NULL) {}

// Same as the default constructor except
// it sets the title of the board
BBoard::BBoard(const string &boardTitle)
    : title(boardTitle), currentUser(NULL) {}

BBoard::~BBoard() {
    for(unsigned i = 0; i < messageList.size(); ++i) {
        delete messageList[i];
    }
}

// Imports all the authorized users from an input file,
// storing them as User objects in the vector userList
// The name of the input file is passed in as a parameter to this function.
// See below for file format.
bool BBoard::loadUsers(const string &loadfile) {
  ifstream fileName(loadfile.c_str());

  if (!fileName.is_open()) {
    cout << "Error opening file" << endl;
    return false;
  }

  string userName = "", userPassword = "";
  while (fileName >> userName) {
    fileName >> userPassword;
    if (userName != "end") {
      User userData(userName, userPassword);
      userList.push_back(userData);
    }
  }
  fileName.close();
  return true;
}

// const User* BBoard::getUser(const string &name, const string &pw) const {
//   for (unsigned i = 0; i < userList.size(); ++i) {
//     if (userList.at(i).check(name, pw)) {
//       return &userList.at(i);
//     }
//   }
//   return NULL;
// }

// Asks for and validates a user/password.
// Always asks for both user and password combo unless 'q' or 'Q' entered.
// Checks userList to validate user and password.
// If valid, sets currentUser to this User, outputs welcome message,
// then returns true.
// Otherwise outputs error message and then repeats request
// for username/password.
// Continues until valid user/password
// or until 'q' or 'Q' is entered for username.
// If 'q' or 'Q' is entered, does not ask for password, outputs "Bye!"
// and then returns false.
void BBoard::login() {
  cout << "Welcome to " << title << endl;
  string username, password;
  do {
    cout << "Enter your username ('Q' or 'q' to quit): ";
    cin >> username;
    if (username == "q" || username == "Q") {
      cout << "Bye!" << endl;
      return;
    }

    cout << "Enter your password: ";
    cin >> password;

    for (unsigned i = 0; i < userList.size(); ++i) {
      if(userList.at(i).check(username, password)) {
        currentUser = &userList.at(i);
        cout << endl;
        cout << "Welcome back " << currentUser->getUsername() << "!" << endl << endl;
        return;
      }
    }

    cout << "Invalid Username or Password!" << endl;
    cout << endl;
  } while (username != "Q" || username != "q");

  return;
}

// Contains main loop of Bulletin Board.
// First verifies a User has been logged in.
// Exits **function** immediately if no User logged in (Default User).
// Continues to display menu options to user and performs requested action
// until user chooses to quit.
// See output samples for exact format of menu.
void BBoard::run() {
  if(currentUser == NULL) { 
    return;
  }
  
  char action = ' ';
  while(true) {
    printMenu();
    cin >> action;
    action = tolower(action);

    switch(action) {
      case 'd':
        if (messageList.size() == 0) {
        	cout << endl;
          cout << "Nothing to Display." << endl << endl;
          break;
        }
        cout << endl;
        cout << "---------------------------------------------------------" << endl;
        display();
        cout << endl;
        break;
      case 'n':
        addTopic();
        break;
      case 'r':
        addReply();
        break;
      case 'q':
        cout << "Bye!" << endl;
        currentUser = NULL;
        return;
    }
  }
}

void BBoard::printMenu() const {
  cout << "Menu" << endl;
  cout << "- Display Messages ('D' or 'd')" << endl;
  cout << "- Add New Topic ('N' or 'n')" << endl;
  cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
  cout << "- Quit ('Q' or 'q')" << endl;
  cout << "Choose an action: ";
}

void BBoard::display() const {
  for(unsigned i = 0; i < messageList.size(); ++i) {
    if(messageList.at(i)->isReply()) continue;
    messageList.at(i)->print(0);
    cout << "---------------------------------------------------------" << endl;
  }
}

// void BBoard::addTopic() {
//   string subject, line, body;

//   cout << "Enter Subject: ";
//   cin.ignore();
//   getline(cin, subject);

//   cout << "Enter Body: ";
//   while(getline(cin, line) && line != "") {
//     body += line;
//   }

//   Message *msg = new Topic(currentUser->getUsername(), subject, body, messageList.size());
//   messageList.push_back(msg);
//   cout << endl;
// }

// void BBoard::addReply() {
//   string subject, line, body;
//   int id;

//   do {
//     cout << "Enter Message ID: ";
//     cin >> id;
//     cout << endl;
//     if(id < 0) return;
//   } while(static_cast<unsigned>(id) < messageList.size());

//   cout << "Body: ";
//   cin.ignore();
//   while(getline(cin, line) && line != "") {
//     body += line;
//   }

//   Reply *reply = new Reply(currentUser->getUsername(), "Re: " + subject, body, messageList.size());
//   messageList.at(id)->addChild(reply);
//   messageList.push_back(reply);
// }

void BBoard::addTopic() {
    string temp = "";
    string subject = "";
    string body = "";
    string body2 = "";
    
    cout << "Enter Subject: ";
    cin.ignore();
    getline(cin, subject);
    
    cout << "Enter Body: ";
    cout << endl;
    
    while(true){
        getline(cin, body);
        
        if(body.empty()){
            break;
        }
        
        body2 += (body + "\n");
    }
    body2 = body2.substr(0, body2.size() - 1);
    Topic *newT = new Topic(currentUser->getUsername(), subject, body2, messageList.size() + 1);
    messageList.push_back(newT);
}

void BBoard::addReply() {
    bool correctIndex = false;
    string body = "";
    string subject = "";
    string temp = "";
    string newBody = "";
    
    int searchIndex;
    
    while(!correctIndex){
        cout << "Enter Message ID (-1 for Menu): ";
		cin >> searchIndex;
		
		// if(searchIndex != -1 || searchIndex != 0 || searchIndex < -1 || searchIndex > static_cast<int>(messageList.size())) {
	  	if((searchIndex != -1 && searchIndex < 1) || searchIndex > static_cast<int>(messageList.size())) {
		    cout << "Invalid Message ID!!" << endl << endl;
		}
		  else {
		    correctIndex = true;
		  }
    }
    if(searchIndex < 0){
        cout << endl;
        
        return;
    }
    
    cin.ignore();
    
    cout << "Enter Body: ";
    
    while(true) {
        getline(cin, body);
        
        if(body.empty()) {
            break;
        }
        newBody += (body + "\n");
    }
    newBody = newBody.substr(0, newBody.size() - 1);
    subject = messageList.at(searchIndex - 1)->getSubject();
    
    Reply *newR = new Reply(currentUser->getUsername(), "Re: " + subject, newBody, messageList.size() + 1);
    
    messageList.at(searchIndex - 1)->addChild(newR);
    messageList.push_back(newR);
}

// This function gets a filename (datafile) of a file that stores the messages from previous
// sessions in the given format (See File Format Specs).
// It opens and reads the file, creating Topic and Reply objects as appropriate, and fills the
// messageList vector (note: remember that messageList is a vector of Message pointers, not
// Messages).
// If an error occurs when opening the file, it returns false. Returns true otherwise.
int BBoard::strToInt(string s)
{
    int x;
    stringstream convert(s);
    convert >> x;
    return x;
}

bool BBoard::loadMessages(const string &datafile) {
    ifstream fin(datafile.c_str());
    if(!fin.is_open())
    {
        cout << "Error opening " << datafile << "." << endl;
        return false;
    }

    string s, topic, author, subject, body;
    unsigned count;
    int x;
    int id = 0;
    vector<string> children;
    getline(fin, s);
    if(s != "")
    {
        count = strToInt(s);
        for(unsigned i = 0; i < count; ++i)
        {
            getline(fin, topic);
            getline(fin, s, ' ');
            getline(fin, s);
            id = strToInt(s);
            getline(fin, s, ' ');
            getline(fin, subject);
            getline(fin, s, ' ');
            getline(fin, author);
            fin >> s;
            if(s == ":children:")
            {
                getline(fin, s);
                children.push_back(s);
                fin >> s;
            }

            else
            {
                children.push_back("");
            }

            getline(fin, s, ' ');
            getline(fin, body);
            getline(fin, s);

            while(s != "<end>")
            {
                body += "\n" + s;
                getline(fin, s);
            }

            if(topic != "<begin_topic>")
            {
                Reply * newReply = new Reply(author, subject, body, id);
                messageList.push_back(newReply);
            }
            else
            {
                Topic * newTopic = new Topic(author, subject, body, id);
                messageList.push_back(newTopic);
            }
        }

        fin.close();

        for(unsigned i = 0; i < messageList.size(); ++i)
        {
            istringstream iss(children.at(i));
            while(iss >> x)
            {
                if(x > 0)
                {
                    messageList.at(i)->addChild(messageList.at(x-1));
                }
            }
        }
    }
    return true;
}


// This is the final action of the bulletin board before closing:
// It gets a filename (datafile) of a file that will store all of the the messages,
// and after opening the file, writes the messages into it with the same format.
// If an error occurs when opening the file, it returns false. Returns true otherwise.
// (Note: Since you will be opening the file for writing (i.e. an ofstream),
// "file not found" is NOT an error; a new file will simply be created for you).
// bool BBoard::saveMessages(const string &datafile) {
//   ofstream ofs(datafile.c_str());

//   ofs << messageList.size() << endl;
//   for(unsigned i = 0; i < messageList.size(); ++i) {
//     ofs << messageList.at(i)->toFormattedString();
//   }

//   return true;
// }

bool BBoard::saveMessages(const string &datafile) {
    ofstream outFile;
    outFile.open(datafile.c_str());
    outFile << messageList.size() << endl;
    
    for(unsigned i = 0; i < messageList.size(); i++) {
        outFile << messageList.at(i)->toFormattedString();
    }   
    outFile.close(); 
    
    return true;    
}