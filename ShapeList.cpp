//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "Shape.h"
#include "ShapeNode.h"
#include "ShapeList.h"
#include <cstring>
ShapeList::ShapeList(){
    //cout<<"shape list 19"<<endl;
    head = nullptr;
}                        // sets head to nullptr
ShapeList::~ShapeList(){
    ShapeNode * current = head;
    
    while(current!=nullptr){
        head = current->getNext();
        delete current;
        current=head;
    }
    
    //head = nullptr;
}                       // deletes all list nodes starting
                                        // with head plus associated Shapes
    
ShapeNode* ShapeList::getHead() const{
    return head;
}         // returns the head pointer
void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
    
}       // sets the head pointer to ptr
    
ShapeNode* ShapeList::find(string name) const{
    
    ShapeNode* current = head;
    
    ShapeNode* Next;
    if(current == nullptr){
        return nullptr;
    }
    while(current!=nullptr){
        //Next = current->getNext();
        
        if(name == current->getShape()->getName()){
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
} // finds a shape node with the specified shape name
                                        // returns a pointer to the node if found, otherwise
                                        // returns nullptr if the node is not found
void ShapeList::insert(ShapeNode* s){
    if(s == nullptr){
        return;
    }
    ShapeNode * current = head;
    if(current == nullptr){
        
        s->setNext(current);
        setHead(s);
        return;
    }
    
    
    while (current->getNext()!=nullptr){
        current = current->getNext();
    }
    s->setNext(current->getNext());
    
    current->setNext(s);
    
}          // inserts the node pointed to by s at the end
                                        // of the list; s should never be nullptr
ShapeNode* ShapeList::remove(string name){
    
    bool deleted = false;
    ShapeNode* current = head;
    ShapeNode* returnN = nullptr;
    if(current->getShape()->getName()==name){
        //cout<<"2345678"<<endl;
        ShapeNode* tempHead = current->getNext();
        //delete current;
        //cout<<"eerr334"<<endl;
        returnN = current;
        
        //return current;
        
        //cout<<"hear wrong"<<endl;
        //tempHead->print();
        head = tempHead;
        delete current;
        //cout<<"rrrrr"<<endl;
        deleted = true;
        
        return returnN;
    }
    
    while(current->getNext()!=nullptr && current->getNext()->getShape()->getName()!=name){
        current = current->getNext();
    }
    if(current!=nullptr){
        ShapeNode* temp = current->getNext();
        current->setNext(temp->getNext());
        returnN = temp;
        delete temp;
    }
    //cout<<"123123"<<endl;
    return returnN;
}     // removes the node with the shape called name
                                        // returns a pointer to the removed node or
                                        // nullptr is a node with name does not exist
void ShapeList::print() const{
    if(head == nullptr){
        return;
    }
    ShapeNode* current = head;
    while(current!=nullptr){
        current->print();
        current = current->getNext();
    }
    
}


