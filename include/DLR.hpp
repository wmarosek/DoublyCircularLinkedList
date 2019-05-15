#ifndef DLR_HPP
#define DLR_HPP

#include <iostream>
#include <ctime>
#include <typeinfo>

template <typename Key>
class Ring {

protected: 
    struct Node{
        Key key;

        Node* next;
        Node* prev;
    };
    int count = 0;
    Node* any;

    /* ==== Private methods ==== */
    //Adding node with some Key& , after Node* curr
    bool pushNode(Node* curr, const Key&);
    //Return node with the Key , if valid node is on ring.
    Node* getByKey(const Key&);

public:
    /*  ========================
               CONSTRUCTORS        
        ======================== */
  
    Ring();
    Ring(const Ring<Key>&);
    ~Ring();

    /*  ========================
              BASIC METHODS        
        ======================== */
    bool isEmpty() const;
    int length() const;
    void initialize();
    //Checking that node with key k exist in the ring
    bool findByKey(const Key& k);


    /* ==== += , =  operators, method copy otherRing ==== */
    void copyRing(const Ring<Key>&);
    const Ring& operator=(const Ring<Key>&);
    const Ring& operator+=(const Ring<Key>&);

    /* ==== Pushing methods ==== */

    //Insert before any, and any becomes new node
    void pushBefore(const Key&);
    //Insert after any, and any becomes new node
    void pushAfter(const Key&);
    //Insert before any, but any is still the same as before operation
    void pushBack(const Key&);

    /* ==== Deleting methods ==== */
    //Deleting first node (any)
    void deleteFront();
    //Deleting any->prev
    void deleteBack();
    //Deleting node with Key k
    void deleteByKey(const Key &k);
    //Destroying whole ring
    void destroyRing();

    /* ==== Update method ==== */
    void update(const Key& old, const Key& newKey);

    void print() const;

    /*  ========================
              OTHER METHODS        
        ======================== */

    void randNodes(const int& number);

    /*  ========================
                ITERATOR        
        ======================== */
        
    class Iterator{
    private:
        friend class Ring;
        Node* iter;
    public:
        Iterator(Node *node) : iter(node) {}
        Iterator() : iter(nullptr) {}
        Iterator(const Iterator& src) : iter(src.iter) {}
        ~Iterator() = default;
        Iterator& operator=(const Iterator &other);
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator operator+(int r);
        Iterator operator-(int l);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

        Key& operator*() const;
        
    };

    Iterator begin() const{
        return Iterator(any);
    }


};



/*  ================================================
            
               CLASS METHODS' DEFINITIONS                           
    
    ================================================ */

/*  ========================
           CONSTRUCTORS        
    ======================== */
//Default constructor
template <typename Key>
Ring<Key>::Ring(){
    any = nullptr;
}

//Destructor
template <typename Key>
Ring<Key>::~Ring(){
    destroyRing();
}

/*  ========================
         BASIC METHODS        
    ======================== */
//Initializing a ring (if ring was used , destroy its)
template <typename Key>
void Ring<Key>::initialize(){
    destroyRing();
}

//If ring doesn't has any nodes, return true
template<typename Key>
bool Ring<Key>::isEmpty() const{
    return (any==nullptr);
}

template<typename Key>
int Ring<Key>::length() const{
    return(count);
}

template<typename Key>
void Ring<Key>::destroyRing() {

    while(!isEmpty()){
        this->deleteFront();
    }    
}

template <typename Key>
void Ring<Key>::print() const{
    if(isEmpty()){
        std::cerr << "\n[!] The ring is empty\n" << std::endl;
        return;
    }
    std::cout << "\n\t---- The Ring ----\n" << std::endl;

    Node* curr = any;
    for(int i=0; i < count; i++){

        std::cout << i << "\t Key: "  << curr->key  << "\n";
        curr= curr->next;
    }
    std::cout << "\n";
}



/*  ========================
          PUSH METHODS        
    ======================== */

template<typename Key>
bool Ring<Key>::pushNode(Node* curr, const Key& k){
    if(curr && findByKey(curr->key)){
        Node* temp = new Node;
        temp->key = k;
        Node* next = curr->next;
        temp->prev = curr;
        curr->next = temp;
        next->prev = temp;
        temp->next = next;
        count++;
        return true;
    }
    return false;
}

template <typename Key>
void Ring<Key>::pushBack(const Key& k){
    if (isEmpty()){
        Node* temp = new Node;
        temp->key = k;
        any = temp;
        any->next = any;
        any->prev = any;
        count++;
        return;
    }
    pushNode(any->prev,k);
}
template <typename Key>
void Ring<Key>::pushAfter(const Key& k){
    if(isEmpty()){
        Node* temp = new Node;
        temp->key = k;
        any = temp;
        any->next = any;
        any->prev = any;
        count++;
        return;
    }
    if(pushNode(any, k)){
        any = any->next;
    }
    
}


template <typename Key>
void Ring<Key>::pushBefore(const Key& k){
    pushBack(k);
    if(any != any->next){
        any = any->prev;
    }
}


/*  ========================
          DELETING METHODS        
    ======================== */

template<typename Key>
void Ring<Key>::deleteFront(){
    if(any != any->next && any!=nullptr)
        any = any->next;
    deleteBack();
  
}

template <typename Key>
void Ring<Key>::deleteBack(){
    if(!isEmpty()){
        if(any->prev != any){
            Node* temp = any->prev;
            Node* p = temp->prev;
            p->next = any;
            any->prev = p;
            delete temp;
        }
        else{
            delete any;
            any = nullptr;
        }
        count--;
    }
    else{
        std::cerr << "\n\t[!] The ring is empty\n" << std::endl;
        return;        
    }
}
template <typename Key>
void Ring<Key>::deleteByKey(const Key& k){
    Node* curr = getByKey(k);
    if(curr){
        if(curr == any){
            deleteFront();
            
        }
        else if(curr == any->prev){
            deleteBack();
            
        }
        else{
            Node* prev = curr->prev;
            prev->next = curr->next;
            curr->next->prev = prev;
            delete curr;
            count--;
        }
    }
    else{
        std::cerr << "\n[!] In the ring node with this key doesn't exist\n" << std::endl;
        return;        
    }
}


/*      ========================
    * += , =  operators, copy otherRing        
        ======================== */

template <typename Key>
void Ring<Key>::copyRing(const Ring<Key>& otherRing){
    Node* curr;

    if(!isEmpty()){
        destroyRing();
    }

    if(otherRing.isEmpty()){
        destroyRing();
    }
    else{
        curr = otherRing.any;

        for(int i = 0; i<otherRing.length(); i++){
            this->pushBack(curr->key);
            curr=curr->next;
        }

    }

}

template <typename Key>
Ring<Key>::Ring(const Ring<Key>& otherRing){
    copyRing(otherRing);
}

template <typename Key>
const Ring<Key>& Ring<Key>::operator=(const Ring<Key>& otherRing){
    if(this != &otherRing){
        copyRing(otherRing);
    }
    return *this;
}

template <typename Key>
const Ring<Key>& Ring<Key>::operator+=(const Ring<Key>& otherRing){
    Node* temp = otherRing.any;
    for(int i =0; i < otherRing.length(); i++){
        this->pushBack(temp->key);
        temp = temp->next;
    }
    return *this;
}

/*  ========================
        UPDATE METHOD        
    ======================== */

template<typename Key>
void Ring<Key>::update(const Key& old, const Key& newKey){
    Node* curr = getByKey(old);
    if(curr){
        curr->key = newKey;
        return;
    }
    std::cerr << "[!] Ring doesn't have Node with " << old << "\n";
}

/*  ========================
        ADDITIONAL METHODS        
    ======================== */


template <typename Key>
void Ring<Key>::randNodes(const int& number){
    srand(time(NULL));
    if (typeid(Key) == typeid(int) && typeid(number) == typeid(int) && number > 0){
        for (int i = 0; i < number; i++){
            int randomKey = rand() % 100 + 1;
            this->pushBefore(randomKey);
        }
        return;
    }

    std::cerr << "[!] Only postive number of node can be generate. Key has to be integer!\n";
}



template <typename Key>
typename Ring<Key>::Node* Ring<Key>::getByKey(const Key& k){
    if(!isEmpty()){
        //If any's key is equal to k , return any 
        Node* curr = any;
        do{
            if(curr->key == k)
                return curr;
            curr = curr->next;
        }while(curr!=any);        
    }
    return nullptr;
    
}

template<typename Key>
bool Ring<Key>::findByKey(const Key& k){
    Node* temp = getByKey(k);
    if(!temp)
        return false;
    
    return true;
}

/*  ================================================
            
                  ITERATOR's DEFINITIONS                           
    
    ================================================ */


template <typename Key>
typename Ring<Key>::Iterator& Ring<Key>::Iterator::operator=(const Iterator &other){
    this->iter = other.iter;
    return *this;
}

template <typename Key>
typename Ring<Key>::Iterator& Ring<Key>::Iterator::operator++() {
    this->iter = this->iter->next;
    return *this;
}

template <typename Key>
typename Ring<Key>::Iterator Ring<Key>::Iterator::operator++(int) {
    Iterator r = *this;
    ++(*this);
    return r;
}

template <typename Key>
typename Ring<Key>::Iterator& Ring<Key>::Iterator::operator--() {
    this->iter = this->iter->prev;
    return *this;

}

template <typename Key>
typename Ring<Key>::Iterator Ring<Key>::Iterator::operator--(int) {
    Iterator r = *this;
    --(*this);
    return r;
}


template <typename Key>
typename Ring<Key>::Iterator Ring<Key>::Iterator::operator+(int r) 
{
    Iterator temp(this->iter);
    if (r < 0){
        while (r != 0){
            temp.iter = temp.iter->prev;
            r++;
        }
    }
    else{
        while (r != 0){
            temp.iter = temp.iter->next;
            r--;
        }
    }
    return temp;
}

template <typename Key>
typename Ring<Key>::Iterator Ring<Key>::Iterator::operator-(int l) {
    Iterator temp(this->iter);
    if (l >=0 ){
        while (l != 0){
            temp.iter = temp.iter->prev;
            l--;
        }
    }
    else{
        while (l != 0){
            temp.iter = temp.iter->next;
            l++;
        }
    }
    return temp;
}

template <typename Key>
bool Ring<Key>::Iterator::operator==(const Iterator &other) const{
    return this->iter == other.iter;
}

template <typename Key>
bool Ring<Key>::Iterator::operator!=(const Iterator &other) const{
    return this->iter != other.iter;
}

template <typename Key>
Key& Ring<Key>::Iterator::operator*() const{
    return this->iter->key;
}


/*  ================================================
            
                 SPLIT FUNCTION                          
    
    ================================================ */


template <typename Key>
void split(const Ring<Key>& src, Ring<Key>& r1, bool dir1, int len1, Ring<Key>& r2, bool dir2, int len2){
    if(!src.isEmpty()){
        if(typeid(dir1) == typeid(bool) && typeid(dir2) == typeid(bool) && len1>=0 && len2>=0){
            
            typename Ring<Key>::Iterator it1 = src.begin();
            typename Ring<Key>::Iterator it2 = it1+1;
            
            r1.initialize();
            r2.initialize();
            
            while(len1>0){
                r1.pushBack(*(it1));
                dir1 ? it1 = it1 + 2 : it1 = it1 - 2;
                len1--;
            }

            while(len2>0){
                r2.pushBack(*(it2));
                dir2 ? it2 = it2 + 2 : it2 = it2 - 2;
                len2--;
            }
        }
    }
}


#endif
