#include <iostream>
#include "../include/DLR.hpp"


using namespace std;

static int number = 0;
static int valid = 0;

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


void result(bool correct){
	number++;
	if (correct)
	{
		cout << "[***] THE TEST RAN CORRECTLY! [***]\n";
		valid++;
		return;
	}
	cerr << "[!!!] THE TEST RAN INCORRECTLY [!!!]\n";
}

void conclusion(){
    cout << "\n\n ==== Conclusion of tests ====\n";
	cout << "\n[***] Test: " << number << "\n[***] Correct: " << valid << endl;
}
/*  ================================================
            
                	TESTS                       
    
    ================================================ */
void printingTest(){
	bool correct = true;
    cout << "\n\t ==== PRINTING TEST ====\n\n";

    Ring<int> ring1;

	cout << "[*] Printing normal list\n";

	ring1.randNodes(3);
	ring1.print();
	if(ring1.length()!=3) 
		correct = false;

	cout << "[*] Printing clear list\n";
	ring1.destroyRing();
	ring1.print();
	if(ring1.length()!=0) 
		correct = false;

	//result of the test
	result(correct);


}

void addingTest(){
	
	bool correct = true;
	Ring<int>::Iterator it;
	cout << "\n\t ==== Adding TEST ====\n\n";

    Ring<int> r1;
	Ring<int> r2,r3;

	r1.pushBefore(1);
	r1.pushBefore(2);
	r1.pushBefore(3);
	it = r1.begin();
	cout << "[*] Printing list created by pushBefore\n";
    r1.print();
	if(r1.length()!=3 || *(it) != 3) 
		correct = false;

    r1.destroyRing();
    r1.pushAfter(1);
    r1.pushAfter(2);
    r1.pushAfter(3);
    r1.pushAfter(43);
    r1.pushAfter(53);
	it = r1.begin();
	cout << "[*] Printing list created by pushAfter\n";
	if(r1.length()!=5 || *(it) != 53) 
	 	correct = false;	
    r1.print();

	r1.initialize();
	r1.pushBack(1);
	r1.pushBack(2);
	r1.pushBack(3);
	it = r1.begin();
	if(r1.length()!=3 || *(it-1) != 3) 
		correct = false;
	cout << "[*] Printing list created by pushBack\n";
    r1.print();

	r2.randNodes(-2); //nonpositive number 
	r2.randNodes(3);
	if(r2.length()!=3) 
		correct = false;
	cout << "[*] Printing list creted by randNodes\n";
	r2.print();

	result(correct);

}

void deletingTest(){
	bool correct = true;
	Ring<int>::Iterator it;
    
	cout << "\n\t ==== Deleting TEST ====\n\n";

    Ring<int> r;
	r.deleteByKey(2);
	if(r.length()!=0) 
		correct = false;
	
	r.randNodes(3);
    r.pushBefore(2);
    r.randNodes(5); 
	r.print();
	it = r.begin();
	if(r.length()!=9 || *(it+5) != 2) 
		correct = false;

	cout << "[*] Deleting any and any->prev nodes\n";
	r.deleteFront();
	r.deleteBack();
	r.print();
	it = r.begin();
	if(r.length()!=7 || *(it+4) != 2 || *(it-3)!=2) 
		correct = false;

	cout << "[*] Deleting first node with the Key = 2\n";
	r.deleteByKey(2);
	r.print();
	if(r.length()!=6 || *(it+4) == 2) 
	correct = false;

	result(correct);

}

void sizeTest(){
	bool correct = true;
	cout << "\n\t ==== Size of Ring TEST ====\n\n";

    Ring<int> r;
	r.randNodes(10); 
	cout << "Size of ring is equal: " << r.length() << "\n\n";
	if(r.length()!=10) 
		correct = false;
	cout << "[*] Clearing whole Ring\n\n";
    r.destroyRing();
	cout << "Size of Ring is equal: " << r.length() << "\n\n";
	if(r.length()!=0) 
		correct = false;
	
	result(correct);
	
}

void assigmentTest(){
	bool correct = true;
	Ring<int>::Iterator it,it2;

	cout << "\n\t ==== Assigment operator TEST ====\n\n";

    Ring<int> r1, r2, r3;
	r1.randNodes(10);
	r2 = r1;

	cout << "[*] Printing orginal ring\n";
	r1.print();
	cout << "[*] Printing copied ring\n";
	r2.print();
	
	it = r1.begin();
	it2 = r2.begin();
	for(int i=0; i<r2.length(); i++){
		if(*(it)!=*(it2)){
			correct = false;
		}
		it++;
		it2++;
	}

	r2 = r3;
	cout << "[*] Printing copied ring from empty ring\n";
    r2.print();

	if(r2.length()!=0)
		correct =false;

	result(correct);
}

void overloadingTest(){
	bool correct = true;
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

	Ring<int>::Iterator it,it2;
	it = r1.begin() + r2.length();
	it2 = r2.begin();
	for(int i=0; i<(r1.length()-r2.length()); i++){
		if(*(it)!=*(it2)){
			correct = false;
		}
		it++;
		it2++;
	}


	r2 = r1;
	cout << "[*] Printing new list after =\n";
	r2.print();

	it = r1.begin();
	it2 = r2.begin();
	for(int i=0; i<r1.length(); i++){
		if(*(it)!=*(it2)){
			correct = false;
		}
		it++;
		it2++;
	}
	
	result(correct);

}

void splitTest(){
	bool correct = true;

	cout << "\n\t ==== Spit funtion TEST ====\n\n";

    Ring<int> src, r1, r2;
    src.randNodes(3);
    src.print();

    split(src,r1,true,4,r2,false,4);
	cout << "[*] Printing first list after split\n";
	r1.print();
	cout << "[*] Printing second list after split\n";
	r2.print();

	Ring<int>::Iterator srcIt,it1,it2;
	srcIt = src.begin();
	it1 = r1.begin();
	for(int i=0; i< r1.length(); i++){
		if(*(srcIt) != *(it1)){
			correct = false;
		}
		srcIt = srcIt +2;
		it1++;
	}
	srcIt = src.begin() + 1;
	it2 = r2.begin();
	for(int i=0; i< r2.length(); i++){
		if(*(srcIt) != *(it2)){
			correct = false;
		}
		srcIt = srcIt - 2;
		it2++;
	}	

	result(correct);
    
}

void updateTest(){
	bool correct = true;


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

	Ring<int>::Iterator it;
	it = ring1.begin();
	if(*(it-1)!=5)
		correct = false;
	
	ring1.initialize();
	cout << "[*] List is empty\n";
	ring1.update(3,3);
	if(ring1.length()!=0)
		correct =false;

	ring1.initialize();
	ring1.pushBack(3);
	cout << "[*] Printing one node normal list\n";
	
	ring1.print();
	ring1.update(3,5);
	cout << "[*] Printing updated list\n";
	ring1.print();

	it = ring1.begin();
	if(ring1.length()!=3 && (*it)!=5)
		correct =false;

	result(correct);
}