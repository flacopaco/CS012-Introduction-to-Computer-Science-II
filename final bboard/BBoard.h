#ifndef BBOARD_H
#define BBOARD_H

#include <string>
#include <vector>
#include "User.h"
#include "Message.h"

using namespace std;

class BBoard {
 private:
  string title;
  vector<User> userList;
  User *currentUser;
  vector<Message*> messageList;

 public:
  // Constructs a board with a default title,
  // empty user & message lists,
  // and the "default" User
  BBoard();

  // Same as the default constructor except
  // it sets the title of the board
  BBoard(const string &);
  ~BBoard();

  // Imports all the authorized users from an input file,
  // storing them as User objects in the vector userList
  // The name of the input file is passed in as a parameter to this function.
  // See below for file format.
  bool loadUsers(const string &);

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
  void login();

  // Contains main loop of Bulletin Board.
  // First verifies a User has been logged in.
  // Exits **function** immediately if no User logged in (Default User).
  // Continues to display menu options to user and performs requested action
  // until user chooses to quit.
  // See output samples for exact format of menu.
  void run();

  // This function gets a filename (datafile) of a file that stores the messages from previous
  // sessions in the given format (See File Format Specs).
  // It opens and reads the file, creating Topic and Reply objects as appropriate, and fills the
  // messageList vector (note: rem ember th at messageList is a vector of Message pointers, not
  // Messages).
  // If an error occurs when opening the file, it returns false. Returns true otherwise.
  bool loadMessages(const string &datafile);
  bool saveMessages(const string &datafile);

 private:
  void printMenu() const;
  void display() const;
  void addTopic();
  void addReply();
  const User* getUser(const string &, const string &) const;
  int strToInt(string s);
};
#endif
