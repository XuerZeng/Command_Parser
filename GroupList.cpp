//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include "Shape.h"
#include "GroupList.h"
#include "ShapeList.h"
#include "ShapeNode.h"
GroupList::GroupList(){
    head = nullptr;
}                      // sets head to nullptr
GroupList::~GroupList(){
    GroupNode* current;
    while(head!=nullptr){
        current = head;
        head = current->getNext();
        delete current;
    } 
}                     // deletes all list nodes, including all the ShapeList
                                  // attached to each GroupNode

GroupNode* GroupList::getHead() const{
    return head;
}       // returns the head pointer
void GroupList::setHead(GroupNode* ptr){
    head = ptr;
    //ptr->setNext(nullptr);
}     // sets the head pointer to ptr
void GroupList::insert(GroupNode* s){
    if(s == nullptr){
        return;
    }
    if(head == nullptr){
        setHead(s);
        return;
    }
    
    GroupNode* current = head;
    while(current->getNext()!=nullptr){
        current = current->getNext();
    }
    current->setNext(s);
}        // inserts the node pointed to by s at the end of the list
GroupNode* GroupList::remove(string name){
    if(head ==nullptr){
        return nullptr;
    }
    GroupNode* current = head;
    while(current->getNext()!=nullptr){
        if(name == current ->getName()){
            return current;
        }
    }
    return nullptr;
}// removes the group with the name "name" from the list
                                  // and returns a pointer to the removed GroupNode
                                  // returns nullptr is name is not found on list
void GroupList::print() const{
    GroupNode*temp = head;
    if(head == nullptr){
        return;
    }
    cout<<"drawing:"<<endl;
    while(temp!=nullptr){
        //cout<<"drawing:"<<endl;
        temp->print();
        temp=temp->getNext();
    }
   
} 



