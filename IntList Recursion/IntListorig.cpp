#include "IntList.h"

#include <iostream>
#include <string>

IntList::IntList(){
    this->head = 0;
}

void IntList::push_front(int value) {
    IntNode* temp = head;
    head = new IntNode(value);
    head->next = temp;
    return;
}

IntList IntList::ostream&operator<<(ostream &out, const IntList &value){
    
}

bool IntList::exists(int value) const {
    if() 
}

IntList IntList::&operator<<(ostream &value, IntNode *node){
    
}

//two exist functions
//one is public the other is private, the private one is recursive
//do if head and the value isnt found in it, do curr->next and recurse the exist function
