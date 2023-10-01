#ifndef LLIST_H
#define	LLIST_H

#include "book.h"
#include "link.h"
#include "list.h"


// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include in your code if you want access to the
// complete LList template class

// First, get the declaration for the base list class
#include "list.h"

// This is the declaration for LList. It is split into two parts
// because it is too big to fit on one book page
// Linked list implementation
template <typename E> class LList : public List<E> {
private:
    Link<E>* head;       // Pointer to list header
    Link<E>* tail;       // Pointer to last element
    Link<E>* curr;       // Access to current element
    int cnt;    	       // Size of list

    void init() {        // Intialization helper method
        curr = tail = head = new Link<E>;
        cnt = 0;
    }

public:
    LList() { init(); }    // Constructor
    ~LList() { removeall(); }                   // Destructor
    void print() const;                // Print list contents
    void clear() { removeall(); init(); }       // Clear list

    void removeall() {   // Return link nodes to free store
        while (head != NULL) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

    // Insert "it" at current position
    void insert(const E& it) {
        curr->next = new Link<E>(it, 0, curr->next); //inserts
        if (tail == curr) tail = curr->next;  // New tail
        cnt++;
    }

    void append(const E& it) { // Append "it" to list
        tail = tail->next = new Link<E>(it, 0, NULL); //appends
        cnt++;
    }

    // Remove and return current element
    E remove() {
        Assert(curr->next != NULL, "No element");
        E it = curr->next->element;      // Remember value
        Link<E>* ltemp = curr->next;     // Remember link node
        if (tail == curr->next) tail = curr; // Reset tail
        curr->next = curr->next->next;   // Remove from list
        delete ltemp;                    // Reclaim space
        cnt--;			     // Decrement the count
        return it;
    }

    void moveToStart() // Place curr at list start
    {
        curr = head;
    }

    void moveToEnd()   // Place curr at list end
    {
        curr = tail;
    }

    void setCurr(Link<E>* n)   // Place curr at list end
    {
        curr->next = n;
    }
    void setNextCurr(Link<E>* n)   // Place curr at list end
    {
        curr->next->next = n;
    }

    Link<E>* getCurr() { // Returns currs pointer
        return curr->next;
    }

    // Move curr one step left; no change if already at front
    void prev() {
        if (curr == head) return;       // No previous element
        Link<E>* temp = head;
        // March down list until we find the previous element
        while (temp->next != curr) temp = temp->next;
        curr = temp;
    }

    // Move curr one step right; no change if already at end
    void next()
    {
        if (curr != tail) curr = curr->next;
    }

    int length() const { return cnt; } // Return length

    // Return the position of the current element
    int currPos() const {
        Link<E>* temp = head;
        int i;
        for (i = 0; curr != temp; i++)
            temp = temp->next;
        return i;
    }

    // Move down list to "pos" position
    void moveToPos(int pos) {
        Assert((pos >= 0) && (pos <= cnt), "Position out of range");
        curr = head;
        for (int i = 0; i < pos; i++) curr = curr->next;
    }

    const E& getValue() const { // Return current element
        Assert(curr->next != NULL, "No value");
        return curr->next->element;
    }

    void setHead(Link<E>* node) { //set heads pointer
        head->next = node;
    }

    Link<E>* getHead() { //returns heads pointer
        return head->next;
    }

    void setTail(Link<E>* node) { //updates tail
        tail = node;
    }

    Link<E>* getTail() { //returns tail
        return tail;
    }

    Link<E>* getPointer(Link<E>* node) { //returns pointer of node
        return node->next;
    }
};

#endif