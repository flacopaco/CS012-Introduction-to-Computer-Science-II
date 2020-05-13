#include <iostream>
#include "Message.h"

using namespace std;

Message::Message() {}

// Parameterized constructor
Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id)
    : author(athr), subject(sbjct), body(body), id(id) {}

Message::~Message() {}

void Message::print(unsigned indentation) const {
  string space;
  for(unsigned i = 0; i < indentation; ++i) {
    cout << " ";
  }

  cout << "Message #" << id << ": " << subject << endl;
  for(unsigned i = 0; i < indentation; ++i) {
    cout << " ";
  }

  cout << "from " << author << ": ";
  istringstream iss(body);
  getline(iss, space);
  cout << space;
  cout << endl;

  while(getline(iss, space)) {
    for(unsigned i = 0; i < indentation; ++i) {
      cout << " ";
    }

    cout << space;
    cout << endl;
  }

  if(childList.size() == 0) {
    return;
  }
  else {
    for(unsigned i = 0; i < childList.size(); ++i) {
      cout << endl;
      childList.at(i)->print(2+indentation);
    }
  }
}

const string& Message::getSubject() const {
  return subject;
}

unsigned Message::getID() const {
  return id;
}

void Message::addChild(Message *child) {
  childList.push_back(child);
}
