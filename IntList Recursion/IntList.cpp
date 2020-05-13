#include <iostream>
using namespace std;
#include "IntList.h"

IntList::IntList(): head(0){
    
}

void IntList::push_front(int val){
   IntNode* temp = new IntNode(val);
   temp->next = head;
   head = temp;
   return;
}

ostream & operator<<(ostream &out, const IntList &rhs){
    IntNode* obj = rhs.head;
    if(obj != 0 && obj == rhs.head){
        out <<obj->data;
        obj = obj->next; 
    }
    if(obj != 0){
        out <<  " " <<obj->data;
        obj = obj->next;
        operator<<(out, obj);
    }
    return out;
}

bool IntList::exists(int num) const{
    IntNode* obj = head;
    if(!exists(obj, num)){
        return false;
    }else{
        return true;
    }
} 

bool IntList::exists(IntNode * obj, int val) const{
    if(obj == 0){
        return false;
    }else if(obj->next != 0){
        if(obj->data == val){
            return true;
        }
        obj = obj->next;
        return exists(obj, val);
    }else{
        return obj->data == val;
    }
}

ostream & operator<<(ostream &out, IntNode *start){
    IntNode* obj = start;
    if(obj != 0){
        out <<  " " <<obj->data;
        obj = obj->next;
        operator<<(out, obj);
    }
    return out;
}