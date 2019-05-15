#include <iostream>
#include "../include/DLR.hpp"


using namespace std;

//Normal and reverse printing list!
void printingTest();
//Adding to front, to back , after any node and randomly
void addingTest();
//Function split test
void splitTest();
//Deleting any, any->prev, and by key
void deletingTest();
//Size testing
void sizeTest();
//Assigment operator test
void assigmentTest();
//Overloading operator test 
void overloadingTest();
//Update method test
void updateTest();

void updateTest(){
    cout << "\n\t ==== Update TEST ====\n\n";

    Ring<int> ring1;
	ring1.randNodes(3);
	ring1.pushBack(3);
	cout << "[*] Printing normal list\n";

	ring1.print();
	ring1.update(3,5);
	ring1.update(101,5);

	cout << "[*] Printing updated list\n";
	ring1.print();

	ring1.initialize();
	cout << "[*] List is empty\n";
	ring1.update(3,3);

	ring1.initialize();
	ring1.pushBack(3);
	cout << "[*] Printing one node normal list\n";

	ring1.print();
	ring1.update(3,5);
	cout << "[*] Printing updated list\n";
	ring1.print();

}

void printingTest(){
    cout << "\n\t ==== PRINTING TEST ====\n\n";

    Ring<int> ring1;

	cout << "[*] Printing normal list\n";

	ring1.randNodes(3);
	ring1.print();


	cout << "[*] Printing clear list\n";
	ring1.destroyRing();
	ring1.print();

}

void addingTest(){
    cout << "\n\t ==== Adding TEST ====\n\n";

    Ring<int> r1;
	Ring<int> r2,r3;


	r1.pushBefore(1);
	r1.pushBefore(2);
	r1.pushBefore(3);
	cout << "[*] Printing list created by pushBefore\n";
    r1.print();
    r1.destroyRing();


    r1.pushAfter(1);
    r1.pushAfter(2);
    r1.pushAfter(3);
    r1.pushAfter(43);
    r1.pushAfter(53);
	cout << "[*] Printing list created by pushAfter\n";
    r1.print();

	r1.initialize();
	r1.pushBack(1);
	r1.pushBack(2);
	r1.pushBack(3);
	cout << "[*] Printing list created by pushBack\n";
    r1.print();

	r2.randNodes(-2); //nonpositive number 
	r2.randNodes(2.3); //wrong instance
	r2.randNodes(3);
	cout << "[*] Printing list creted by randNodes\n";
	r2.print();


	r3.initialize();
	cout << "[*] Printing list creted by pushBack and randNodes\n";
	r3.randNodes(3);
	r3.pushBack(3);
	r3.pushBack(4);
	r3.pushBack(5);
	r3.print();

	

}

void deletingTest(){
    cout << "\n\t ==== Deleting TEST ====\n\n";

    Ring<int> r;
		r.popByKey(2);

	r.randNodes(3);
    r.pushBefore(2);
    r.randNodes(5); 
	r.print();
	cout << "[*] Deleting any and any->prev nodes\n";
	r.popFront();
	r.popBack();
	r.print();

	cout << "[*] Deleting first node with the Key\n";
	r.popByKey(2);
	r.print();

}

void sizeTest(){
	cout << "\n\t ==== Size of Ring TEST ====\n\n";

    Ring<int> r;
	r.randNodes(10); 
	cout << "\tSize of ring is equal: " << r.length() << "\n\n";
	cout << "[*] Clearing whole Ring\n\n";
    r.destroyRing();
	cout << "\tSize of Ring is equal: " << r.length() << "\n";
	
}

void assigmentTest(){
	cout << "\n\t ==== Assigment operator TEST ====\n\n";

    Ring<int> r1, r2, r3;
	r1.randNodes(10);
	r2 = r1;

	cout << "[*] Printing orginal ring\n";
	r1.print();
	cout << "[*] Printing copied ring\n";
	r2.print();
	
	r2 = r3;
	cout << "[*] Printing copied ring from empty ring\n";
    r2.print();

	
}

void overloadingTest(){
	cout << "\n\t ==== Overload operator TEST ====\n\n";

    Ring<int> r1, r2, r3;
	r1.randNodes(3);
	r1.pushBefore(2);
	r2.randNodes(2);

	

	cout << "[*] Printing orginal lists\n";
	r1.print();
	r2.print();
	r1 += r2;
	cout << "[*] Printing new list after +=\n";
	r1.print();
	r2 = r1;
	cout << "[*] Printing new list after =\n";
	r2.print();
	

}

void splitTest(){
	cout << "\n\t ==== Spit funtion TEST ====\n\n";

  
    Ring<int> src, r1, r2;
    src.randNodes(3);
    src.print();

    split(src,r1,true,4,r2,false,4);
	cout << "[*] Printing first list after split\n";
	r1.print();
	cout << "[*] Printing second list after split\n";
	r2.print();

    
}