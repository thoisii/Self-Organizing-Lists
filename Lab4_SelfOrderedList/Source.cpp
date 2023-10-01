#include "SelfOrderedList.h"
#include <fstream>
#include <string>
#include "link.h"
#include <iostream>

using namespace std;

int main() {
	//Test 1
	cout << "Lab 4 - Self Organizing List - Trenton Hoisington" << endl << endl;
	cout << "Starting Char Test: " << endl << endl;
	//list for count
	SelfOrderedList<char> list1;

	//COUNT
	//initializes list
	list1.add('A');
	list1.add('B');
	list1.add('C');
	list1.add('D');
	list1.add('E');
	list1.add('F');
	list1.add('G');
	list1.add('H');

	//distincts which reorder to call
	list1.setPath(1);
	//calls find to search linked list
	list1.find('F');
	list1.find('D');
	list1.find('F');
	list1.find('G');
	list1.find('E');
	list1.find('G');
	list1.find('F');
	list1.find('A');
	list1.find('D');
	list1.find('F');
	list1.find('G');
	list1.find('E');
	list1.find('H');
	list1.find('I');

	//prints out count heuristic
	cout << "Count Heuristic:            Size of list: " << list1.size() << endl;
	cout << "Number of compares: " << list1.getCompares() << endl;
	list1.printlist();
	list1.removeall();

	//list for Move-To-Front
	SelfOrderedList<char> list2;

	//MOVETOFRONT
	//initializes list
	list2.add('A');
	list2.add('B');
	list2.add('C');
	list2.add('D');
	list2.add('E');
	list2.add('F');
	list2.add('G');
	list2.add('H');

	//sets reorder to moveToFront()
	list2.setPath(2);
	//calls find to search linked list
	list2.find('F');
	list2.find('D');
	list2.find('F');
	list2.find('G');
	list2.find('E');
	list2.find('G');
	list2.find('F');
	list2.find('A');
	list2.find('D');
	list2.find('F');
	list2.find('G');
	list2.find('E');
	list2.find('H');
	list2.find('I');

	//prints out move to front heuristic
	cout << "Move to Front Heuristic:    Size of list: " << list2.size() << endl;
	cout << "Number of compares: " << list2.getCompares() << endl;
	list2.printlist();
	list2.removeall();

	//list for transpose
	SelfOrderedList<char> list3;

	//TRANSPOSE
	//initializes list
	list3.add('A');
	list3.add('B');
	list3.add('C');
	list3.add('D');
	list3.add('E');
	list3.add('F');
	list3.add('G');
	list3.add('H');

	//sets reorder to transpose
	list3.setPath(3);
	//calls find to search linked list
	list3.find('F');
	list3.find('D');
	list3.find('F');
	list3.find('G');
	list3.find('E');
	list3.find('G');
	list3.find('F');
	list3.find('A');
	list3.find('D');
	list3.find('F');
	list3.find('G');
	list3.find('E');
	list3.find('H');
	list3.find('I');

	//prints out transpose heuristic
	cout << "Transpose Heuristic:        Size of list: " << list3.size() << endl;
	cout << "Number of compares: " << list3.getCompares() << endl;
	list3.printlist();
	list3.removeall();

	//Test 2
	cout << "Starting String Test: " << endl << endl;

	//sets filename
	string filename = "test.txt";

	//list for string reorder of count
	SelfOrderedList<string> list4;

	//file used to grab words
	ifstream file1;
	string word1;
	//open file
	file1.open(filename.c_str());
	while (file1 >> word1) { //take word and print
		list4.find(word1);
	}
	//close file
	file1.close();
	//prints 10 nodes from count heuristic
	cout << "Count Heuristic:            Size of list: " << list4.size() << endl;
	cout << "Number of compares: " << list4.getCompares() << endl;
	list4.printlist(10);
	list4.removeall();

	//list for MTF
	SelfOrderedList<string> list5;
	//sets reorder to MTF
	list5.setPath(2);
	ifstream file2;
	string word2;
	//open file
	file2.open(filename.c_str());
	while (file2 >> word2) { //take word and print
		list5.find(word2);
	}
	//close file
	file2.close();
	//prints 10 nodes from MTF heuristic
	cout << "Move to Front Heuristic:    Size of list: " << list5.size() << endl;
	cout << "Number of compares: " << list5.getCompares() << endl;
	list5.printlist(10);
	list5.removeall();

	//list for transpose
	SelfOrderedList<string> list6;
	//sets reorder to transpose
	list6.setPath(3);
	ifstream file3;
	string word3;
	//open file
	file3.open(filename.c_str());
	while (file3 >> word3) { //take word and print
		list6.find(word3);
	}
	//close file
	file3.close();
	//prints 10 nodes from transpose heuristic
	cout << "Transpose Heuristic:        Size of list: " << list6.size() << endl;
	cout << "Number of compares: " << list6.getCompares() << endl;
	list6.printlist(10);
	list6.removeall();

	return 0;
}