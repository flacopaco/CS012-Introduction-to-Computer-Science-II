#include <iostream>
#include <sstream>
#include "Message.h"
#include "Topic.h"

using namespace std;

Topic::Topic() {}
// Parameterized constructor
Topic::Topic(const string &athr, const string &sbjct, const string &body, unsigned id)
    : Message(athr, sbjct, body, id) {}

bool Topic::isReply() const { 
  return false; 
}

string Topic::toFormattedString() const {
  stringstream ss;
  ss << "<begin_topic>" << endl << ":id: " << id << endl << ":subject: " << subject << endl << ":from: " << author << endl;

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
