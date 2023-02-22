//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool isDuplicateG(string name){
    GroupNode* findG = gList->getHead();
    bool duplicate = false;
    while(findG!= nullptr&&!duplicate){
        if(findG->getName() == name){
            duplicate = true;
            return duplicate;
        }
        findG = findG->getNext();
    }
    return duplicate;
    //the name is not the name for group, find the shape name
}

bool isDuplicateS(string name){
    GroupNode* findShape = gList->getHead();
    bool duplicate = false;
    while(findShape!= nullptr&&!duplicate){
        ShapeList* s = findShape ->getShapeList();
        if(s->find(name)!= nullptr){
            duplicate = true;
            return duplicate;
        }
        findShape = findShape->getNext();
    }
    return duplicate;
}
bool validName(string name){
    bool valid = true;
    for(int i=0;i<NUM_KEYWORDS;i++){
        if(name == keyWordsList[i]){
            cout<<"error: invalid name"<<endl;
            valid = false;
            return valid;
        }
    }
    for(int j=0; j<NUM_TYPES;j++){
        if(name == shapeTypesList[j]){
            cout<<"error: invalid name"<<endl;
            valid=false;
            return valid;
        }
    }
    
    return valid;
}
bool invalidCommand (bool failFlag){
    if(failFlag){
        cout<<"Invalid Command"<<endl;
        cout<<">";
        return true;
    }
    return false;
}
void shapeCreate(GroupNode* group, string name, string type, int xloc, int yloc, int xsize, int ysize){
    
    if(!validName(name)){
        return;
    }
    
    
    if(isDuplicateS(name)){
        cout<<"error: name "<<name<<" exists"<<endl;
        return;
    }
    if(isDuplicateG(name)){
        cout<<"error: name "<<name<<" exists"<<endl;
        return;
    }
    
    ShapeNode* newNode = new ShapeNode();
    Shape* newShape = new Shape(name,type,xloc,xsize,yloc,ysize);
    //ShapeList* newList;
    
    newNode->setShape(newShape);
    //cout<<"76"<<endl;
    group->getShapeList()->insert(newNode);
    cout<<name<<": "<<type<<" "<<xloc<<" "<<yloc<<" "<<xsize<<" "<<ysize<<endl;
    
    return;
}

void groupCreate(string name){
    if(!validName(name)){
        //cout<<"Invalid Name";
        return;
    }
    GroupNode* temp = gList->getHead();
    while(temp!=nullptr){
        if(temp->getName()==name){
            cout<<"name "<<name<<" exists"<<endl;
            return;
        }
        temp=temp->getNext();
    }
    GroupNode* newGroup = new GroupNode(name);
    
    gList->insert(newGroup);
    //ShapeList* newList = new ShapeList();
    //newGroup->setShapeList(newList);
    cout<<name<<": "<<"group"<<endl;
    
    return;
}

void moveShape(string name, string group, GroupNode* pool){
    if(!validName(name)||!validName(group)){
        return;
    }
    //find if the group name exist in the list
    if(!isDuplicateS(name)){
        cout<<"shape "<<name<<" not found"<<endl;
        return;
    }
    if(!isDuplicateG(group)){
        cout<<"group "<<group<<" not found"<<endl;
        return;
    }
    //find the shape with name in the shape list and return with a pointer
    
    GroupNode* from = gList->getHead();
    
    bool found = false;
    while(from!= nullptr && !found){
        ShapeList* s = from ->getShapeList();
        if(s->find(name)!= nullptr){
            found = true;
        }
        if(!found){
            from = from->getNext();
        }
        
    }
    ShapeNode* moveShape = from->getShapeList()->find(name);
    //cout<<"lin156"<<endl;
    string n, type;
    int xl,yl,xs,ys;
    n = moveShape->getShape()->getName();
    type = moveShape->getShape()->getType();
    xl = moveShape->getShape()->getXlocation();
    yl = moveShape->getShape()->getYlocation();
    xs = moveShape->getShape()->getXsize();
    ys = moveShape->getShape()->getYsize();
    //cout<<"line 165"<<endl;
    ShapeNode* newNode = new ShapeNode();
    Shape* newShape = new Shape(n,type,xl,xs,yl,ys);
    newNode->setShape(newShape);
    //cout<<"line 169"<<endl;
    //newNode is created with the data from pool and insert this into the new group;
    //first find the group in the group list
    GroupNode* tempG = gList->getHead();
    
    bool nameFind = false;
    while(tempG->getNext()!=nullptr && !nameFind){
        //string nn;
        //nn = tempG->getName();
        //cout<<nn<<endl;
        if(tempG->getName() == group){
            //cout<<"ddddd"<<endl;
            nameFind = true;
        }
        if(!nameFind){
            tempG = tempG->getNext();
        }
    }
    //cout<<"findfind"<<endl;
    //tempG -> print();
    //cout<<"tempG"<<endl;
    //newNode->print();
    //insert into the shapeList of the group Node
    tempG->getShapeList()->insert(newNode);
    //tempG->print();
    //delete the node from the pool
    //cout<<"got you!"<<endl;
    from->getShapeList()->remove(name);
    cout<<"moved "<<name<<" to "<<group<<endl;
    return;
    
}



void deleteS(string name, GroupNode* pool){
    bool nf = true;
    bool gf = true;
    if(!validName(name)){
        //cout<<"error: invalid name"<<endl;
        return;
    }
    
    if(!isDuplicateS(name)&&!isDuplicateG(name)){
        cout<<"Shape "<<name<<" not found"<<endl;
        return;
    }
    
    
    if(isDuplicateG(name)){
        GroupNode* pre = gList->getHead();
        while(pre->getNext()!=nullptr && pre->getNext()->getName()!=name){
            pre = pre->getNext();
        }
        //cout<<"group found"<<endl;
        //GroupNode* removeG = pre->getNext();
        //GroupNode* after = pre->getNext()->getNext();
        ShapeNode* s = pre->getNext()->getShapeList()->getHead();
        ShapeNode* next;
        //cout<<"start"<<endl;
        //removeG->print();
        //after->print();
        while(s!=nullptr){
            //s->print();
            next = s->getNext();
            string n, type;
            int xs, ys,xl, yl;
            n = s->getShape()->getName();
            type = s->getShape()->getType();
            xl= s->getShape()->getXlocation();
            yl=s->getShape()->getYlocation();
            xs = s->getShape()->getXsize();
            ys = s->getShape()->getYsize();
            Shape* newShape = new Shape(n,type,xl,xs,yl,ys);
            ShapeNode* newNode = new ShapeNode();
            newNode->setShape(newShape);
            pool->getShapeList()->insert(newNode);
            pre->getNext()->getShapeList()->remove(s->getShape()->getName());
            s = next;
        }
        //pre->getNext()->getShapeList()->print();
        //cout<<"deleting shapeNode"<<endl;
        if(pre!=nullptr){
            GroupNode* removeG = pre->getNext();
            pre->setNext(removeG->getNext());
            //pre->getNext()->print();
            delete removeG;
        }
        //pre->setNext(after);
        //pre->getNext()->print();
        //delete removeG;
        cout<<name<<": deleted"<<endl;
        return;
    }else if(isDuplicateS(name)){
        GroupNode* findShape = gList->getHead();
        ShapeNode* shape;
        while(findShape!= nullptr){
            ShapeList* s = findShape ->getShapeList();
            if(s->find(name)!= nullptr){
                //shape = s->find(name);
                s->remove(name);
                cout<<name<<": deleted"<<endl;
                return;
            }
            findShape = findShape->getNext();
        }
    }
    
}

void draw(void){
    gList->print();
    return;
}
int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the poo group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    //ShapeList* newList = new ShapeList();
    //poolGroup->setShapeList(newList);
    string line;
    string command;
    string type,name, group;
    int xloc,yloc,xsize,ysize;
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        if(invalidCommand(lineStream.fail())){
            lineStream.clear();
            getline(cin, line);
            continue;
        }
        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        //cout<<command<<endl;
        if(command == "shape"){
            
            lineStream >> name >> type >> xloc >> yloc >> xsize >> ysize;
            
            shapeCreate(poolGroup,name,type,xloc,yloc,xsize,ysize);
            cout << "> ";
            getline(cin, line);
            continue;
                
        }else if(command == "group"){
            lineStream>> group;
            
            groupCreate(group);
            cout << "> ";
            getline(cin, line);
            continue;
        }else if(command == "draw"){
            draw();
            cout << "> ";
            getline(cin, line);
            continue;
        }else if(command == "move"){
            lineStream>>name>>group;
            moveShape(name,group,poolGroup);
            cout << "> ";
            getline(cin, line);
            continue;
        }else if(command == "delete"){
            lineStream>>name;
            deleteS(name,poolGroup);
            cout << "> ";
            getline(cin, line);
            continue;
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    
    
    return 0;
}

