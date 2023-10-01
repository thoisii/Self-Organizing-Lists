/*
 * File:   SelfOrderedList.hpp
 * Author: Dad's ASUS
 *
 * Created on September 28, 2012, 8:18 AM
 */


#ifndef SELFORDEREDLIST_HPP
#define	SELFORDEREDLIST_HPP

 //Include Statements
#include "llist.h"
#include "SelfOrderedListADT.h"
#include "link.h"
#include <iostream>



template <typename E>
class SelfOrderedList : public SelfOrderedListADT<E>, public LList<E> {
public:
    //Default constructor/destructor
    SelfOrderedList() {}
    ~SelfOrderedList() {}

    //Look for 'it'.  If found return true and execute the self-ordering
    //heuristic used for ordering the list: count, move-to-front, or transpose.
    //Increments the compare instance variable every time it compares 'it' to
    //other members of the list. Returns true if 'it' is found.
    bool find(const E& it) {
        bool isFound = false;
        LList<E>::moveToStart();
        while (isFound == false && LList<E>::getCurr() != LList<E>::getTail()->next) {
            //searches list for it
            if (it == LList<E>::getCurr()->element) {
                isFound = true;
                //updates occurance
                LList<E>::getCurr()->occurance++;

                switch (path) { //switch statement for heuristics
                case 1:
                    count(LList<E>::getCurr()); //passes in correct value
                    break;
                case 2:
                    moveToFront(LList<E>::getCurr()); //passes in correct value
                    break;
                case 3:
                    transpose(LList<E>::getCurr()); //passes in correct value
                    break;
                default:
                    cout << "\ndefualt\n" << endl;
                    break;
                }
            }
            //updates the number of comparisons
            numComparisons++;
            //goes through list
            LList<E>::next();

        }
        //if false, adds and for MTF puts it at beginning
        if (isFound == false) {
            add(it);
            switch (path) {
            case 1:
                break;
            case 2:
                moveToFront(LList<E>::getCurr());
                break;
            case 3:
                break;
            default:
                cout << "\ndefualt\n" << endl;
                break;
            }
        }
        return isFound;
    }

    //Called by find if 'it' is not in the list. Adds the new 'it' to the list
    //Can also be called independently when initially loading the list with
    //unique values and when you want to load the list in the order 'it' is 
    //read without your re-order method being called (or the number of compares
    //being incremented.
    void add(const E& it) {
        LList<E>::append(it);
        listSize++;
    }  //Add new 'it' to the list\

    int getCompares() const { return numComparisons; }  //Returns the number of accumulated compares
    int size() const { return listSize; }      //Returns the size of the list

    //Print the list
    //In order print of the list.  printlist() prints the entire list
    //whereas printlist(n) prints n nodes.
    void printlist() {
        Link<E>* temp = LList<E>::getHead();

        while (temp != NULL) {
            cout << temp->element << "-" << temp->occurance << "\t";
            temp = temp->next;
        }
        cout << endl << endl << endl;
    }
    void printlist(int n) {

        Link<E>* temp = LList<E>::getHead();

        for (int i = 0; i < n && temp->next != NULL; i++) {
            cout << temp->element << "-" << temp->occurance << "\t";
            temp = temp->next;
        }
        cout << endl << endl << endl;
    }

    //greatest node->occurance at front and so forth
    void count(Link<E>* node) {
        //gets prev
        LList<E>::prev();
        //does not enter if less than or node = prev
        while (LList<E>::getCurr()->occurance < node->occurance && node != LList<E>::getCurr()) {
            //updates all pointers and switches
            LList<E>::getCurr()->next = node->next;
            node->next = LList<E>::getCurr();
            LList<E>::setCurr(node);
            //checks for tail and if true changes tails value
            if (node == LList<E>::getTail()) {
                LList<E>::setTail(node->next);
            }
            //uses prev to unwind further through while loop
            LList<E>::prev();
        }
        //resets head to node if node is head->next
        if (node == LList<E>::getHead()) {
            LList<E>::setHead(node);
        }
    }

    //moves each newest occurance to front
    void moveToFront(Link<E>* node) {
        //checks if node is not tail
        if (LList<E>::getCurr()->next != LList<E>::getTail()->next) {
            LList<E>::setCurr(LList<E>::getCurr()->next); //updates prev node
        }
        //if node is tail then it updates pointers correctly
        else {
            LList<E>::setTail(LList<E>::getCurr());
            LList<E>::moveToEnd();
            LList<E>::prev();
            LList<E>::prev();
            LList<E>::setTail(LList<E>::getCurr());
            LList<E>::setNextCurr(NULL);
        }
        //updates tail if tail
        if (LList<E>::getTail() == NULL) { LList<E>::setTail(LList<E>::getCurr()); }
        node->next = LList<E>::getHead(); //found node points to head
        LList<E>::setHead(node); //updates head
    }

    void transpose(Link<E>* node) {
        //checks node if head, head->next and head->next->next
        if (node != LList<E>::getHead() && node != LList<E>::getHead()->next && node != LList<E>::getHead()->next->next) {
            //tail
            if (node == LList<E>::getTail()) {
                //goes back three
                LList<E>::prev();
                LList<E>::prev();
                LList<E>::prev();
                //updates pointers to swap only with node's prev node
                Link<E>* temp = LList<E>::getCurr()->next->next; // temp of 4
                LList<E>::getCurr()->next->next = node; // 3 ot 5
                temp->next = node->next;
                LList<E>::getCurr()->next->next->next = NULL; // 4 to 6
                node->next = temp; // 5 to 4
                LList<E>::setTail(node->next);
            }
            //same as before just doesn't update tail
            else {
                LList<E>::prev();
                LList<E>::prev();
                LList<E>::prev();
                Link<E>* temp = LList<E>::getCurr()->next->next; // temp of 4
                LList<E>::getCurr()->next->next = node; // 3 ot 5
                temp->next = node->next;
                LList<E>::getCurr()->next->next->next = node->next->next; // 4 to 6
                node->next = temp; // 5 to 4
            }
        }
        //if node is head's->next->next
        else if (node == LList<E>::getHead()->next->next) {
            //updates the pointers in a different manner by replacing head with temp
            Link<E>* temp = LList<E>::getHead(); // temp of 4
            LList<E>::getHead()->next->next = node->next;
            node->next = LList<E>::getHead()->next;
            temp->next = node;
            LList<E>::setHead(temp);
        }
        //if node is head's->next
        else if (node == LList<E>::getHead()->next) {
            //updates head and node and their pointers
            LList<E>::getHead()->next = node->next;
            node->next = LList<E>::getHead();
            LList<E>::setHead(node);
        }
        //head stays as head
        else {}
    }

    void setPath(int i) { //used for reorder heuristic
        path = i;
    }

    int getPath() { //get function for path
        return path;
    }

private:
    //variables
    int numComparisons;
    int listSize;
    int path = 1;
};

#endif	/* SELFORDEREDLIST_HPP */

