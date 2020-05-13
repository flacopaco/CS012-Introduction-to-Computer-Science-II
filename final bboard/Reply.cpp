#include <iostream>
#include <sstream>
#include "Message.h"
#include "Reply.h"

using namespace std;

Reply::Reply() {}

// Parameterized constructor
Reply::Reply(const string &athr, const string &sbjct, const string &body, unsigned id)
    : Message(athr, sbjct, body, id) {}

bool Reply::isReply() const { 
  return true; 
}

string Reply::toFormattedString() const {
  stringstream ss;
  ss << "<begin_reply>" << endl << ":id: " << id << endl << ":subject: " << subject << endl << ":from: " << author << endl;

  if(childList.size() != 0) {
    ss << ":children: ";
    
    for(unsigned i = 0; i < childList.size(); i++) {
      ss << childList.at(i)->getID();
      
      if(i != childList.size() - 1) {
        ss << " ";
      }
    }
    ss << endl;
  }
  ss << ":body: " << body << endl << "<end>" << endl;
  return ss.str();
}

