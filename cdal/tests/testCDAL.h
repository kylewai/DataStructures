#ifndef TESTCDAL_H
#define TESTCDAL_H
#include "CDAL.h"

using namespace cop3530;
class testCDAL
{
    public:
        static bool test0CDAL();
        static bool test1CDAL();
        static bool test5CDAL();
        static bool test150CDAL();
        static bool testIterCDAL();
        static bool testCopierCDAL();
        testCDAL();
        ~testCDAL();

};
bool equals_functionC(const int &element, const int &element2){
    if(element == element2){
        return true;
    }
    return false;
}
bool testCDAL::test1CDAL(){
    //------------Testing size 1 CDAL------------

    CDAL<int> *s1 = new CDAL<int>();
    std::cout << s1->length();

    std::cout << "\n********TEST CDAL SIZE 1\n" << std::endl;
    s1->push_front(6);
    std::cout << "push_front 6" << std::endl;
    std::cout << "peek_front: " << s1->peek_front() << std::endl;
    if(s1->peek_front() != 6) return false;
    std::cout << "peek_back: " << s1->peek_back() << std::endl;
    if(s1->peek_back() != 6) return false;
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 1) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(s1->is_empty()) return false;
    std::cout << "Contents: ";
    int *arr = s1->contents();
    std::cout << arr[0] << std::endl;
    if(arr[0] != 6) return false;
    delete[] arr;
    std::cout << "Print: ";
    std::ostream stream(std::cout.rdbuf());
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "Contains 2? Expecting 0" << std::endl;
    std::cout << "contains 2: " << s1->contains(2, *equals_functionC) << std::endl;
    if(s1->contains(2, *equals_functionC)) return false;
    std::cout << "Contains 6? Expecting 1" << std::endl;
    std::cout << "contains 6: " << s1->contains(6, *equals_functionC) << std::endl;
    if(!s1->contains(6, *equals_functionC)) return false;


    std::cout << "--------------------" << std::endl;

    try{
        s1->item_at(1);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->remove(1);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->insert(1, 2);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->replace(1, 1);
        return false;
    }
    catch(std::runtime_error){
    }


    std::cout << "pop_back Expecting 6" << std::endl;
    if(s1->pop_back() != 6) return false;
    std::cout << "pop_back: " << 6 << std::endl;
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 0) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    s1->push_back(6);
    std::cout << "push_back 6" << std::endl;
    std::cout << "pop_front Expecting 6" << std::endl;
    if(s1->pop_front() != 6) return false;
    std::cout << "pop_front: " << 6 << std::endl;
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 0) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    s1->insert(1, 0);
    std::cout << "insert 1 at the 0 position" << std::endl;
    std::cout << "peek_back Expecting 1" << std::endl;
    std::cout << "peek_back: " << s1->peek_back() << std::endl;
    if(s1->peek_back() != 1) return false;
    std::cout << "peek_front Expecting 1" << std::endl;
    std::cout << "peek_front: " << s1->peek_front() << std::endl;
    std::cout << "item_at(0): ";
    std::cout << s1->item_at(0) << std::endl;
    if(s1->item_at(0) != 1) return false;
    if(s1->peek_front() != 1) return false;
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 1) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(s1->is_empty()) return false;
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    if(s1->replace(2, 0) != 1) return false;
    std::cout << "replace(2, 0): 1" << std::endl;
    if(s1->remove(0) != 2) return false;
    std::cout << "remove(0): " << 2 << std::endl;
    std::cout << "--------------------" << std::endl;


    s1->clear();
    std::cout<< "clear()-" << std::endl;
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 0) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    try{
        s1->pop_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->pop_back();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->remove(0);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_back();
        return false;
    }
    catch(std::runtime_error){
    }

    std::cout << "\n------------TEST SIZE 1 CDAL PASSED---------------\n";

    delete s1;

    return true;
}

bool testCDAL::test0CDAL(){
    //------------Testing size 0 CDAL------------

    std::cout << "\n********TEST CDAL SIZE 0\n" << std::endl;
    CDAL<int> *s1 = new CDAL<int>();
    std::cout << "Length: " << s1->length() << std::endl;
    if(s1->length() != 0) return false;
    std::cout << "is_empty: " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;
    std::cout << "Contents: ";
    try{
        int *arr = s1->contents();
        delete[] arr;
        return false;
    }
    catch(std::runtime_error){
        std::cout << std::endl;
    }
    std::cout << "Print: ";
    std::ostream stream(std::cout.rdbuf());
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "Contains 2? Expecting 0" << std::endl;
    std::cout << "contains 2: " << s1->contains(2, *equals_functionC) << std::endl;
    if(s1->contains(2, *equals_functionC)) return false;
    std::cout << "Contains 6? Expecting 0" << std::endl;
    std::cout << "contains 6: " << s1->contains(6, *equals_functionC) << std::endl;
    if(s1->contains(6, *equals_functionC)) return false;



    try{
        s1->pop_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->pop_back();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->replace(1, 0);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->remove(0);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_back();
        return false;
    }
    catch(std::runtime_error){
    }

    std::cout << "\n------------TEST SIZE 0 CDAL PASSED---------------\n";

    delete s1;

    return true;
}

bool testCDAL::test5CDAL(){
    //------------Testing size 5 CDAL------------

    std::cout << "\n********TEST CDAL SIZE 5\n" << std::endl;
    CDAL<int> *s1 = new CDAL<int>();
    for(int i = 0; i < 5; i++){
        s1->push_back(1);
        std::cout << "push back 1" << std::endl;
    }
    std::cout << "Contains 1? Expecting 1" << std::endl;
    std::cout << "contains 1: " << s1->contains(1, *equals_functionC) << std::endl;
    std::cout << "Print: ";
    std::ostream stream(std::cout.rdbuf());
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "Contents: ";
    int *arr = s1->contents();
    std::cout << arr[0] << " " << arr[1] << " " << arr[2] << " "  << arr[3] << " " << arr[4] << std::endl;
    if(arr[0] != 1 || arr[1] != 1 || arr[2] != 1 || arr[3] != 1 || arr[4] != 1) return false;
    delete[] arr;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 5) return false;
    std::cout << "remove(0): ";
    if(s1->remove(0) != 1) return false;
    std::cout << 1 << std::endl;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 4) return false;
    std::cout << "remove(0): ";
    if(s1->remove(0) != 1) return false;
    std::cout << 1 << std::endl;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 3) return false;
    std::cout << "remove(0): ";
    if(s1->remove(0) != 1) return false;
    std::cout << 1 << std::endl;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 2) return false;
    std::cout << "remove(0): ";
    if(s1->remove(0) != 1) return false;
    std::cout << 1 << std::endl;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 1) return false;
    std::cout << "remove(0): ";
    if(s1->remove(0) != 1) return false;
    std::cout << 1 << std::endl;
    std::cout << "Length: ";
    std::cout << s1->length() << std::endl;
    if(s1->length() != 0) return false;
    std::cout << "is_empty(): " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;
    std::cout << "is_full(): " << s1->is_full() << std::endl;
    if(s1->is_full()) return false;

    std::cout << "push_back 1000" << std::endl;
    s1->push_back(1000);
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "push_front 8" << std::endl;
    s1->push_front(8);
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "insert 9 at position 1" << std::endl;
    s1->insert(9, 1);
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "insert 7 at position 0" << std::endl;
    s1->insert(7, 0);
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "push_back 5" << std::endl;
    s1->push_back(5);
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "remove(2): ";
    if(s1->remove(2) != 9) return false;
    std::cout << 9 << std::endl;
    std::cout << "Print: ";
    s1->print(stream);
    std::cout << std::endl;
    std::cout << "peek_front Expecting 7" << std::endl;
    std::cout << "peek_front: " << s1->peek_front() << std::endl;
    if(s1->peek_front() != 7) return false;
    std::cout << "peek_back Expecting 5" << std::endl;
    std::cout << "peek_back: " << s1->peek_back() << std::endl;
    if(s1->peek_back() != 5) return false;
    std::cout << "item_at(2) Expecting 1000" << std::endl;
    std::cout << "item_at(2): " << s1->item_at(2) << std::endl;
    if(s1->item_at(2) != 1000) return false;
    if(s1->replace(3, 1) != 8) return false;
    std::cout << "replace(3, 1): 8" << std::endl;
    std::cout << "item_at(1): " << s1->item_at(1) << std::endl;
    if(s1->item_at(1) != 3) return false;
    std::cout << "pop_back Expecting 5" << std::endl;
    if(s1->pop_back() != 5) return false;
    std::cout << "pop_back: 5" << std::endl;
    std::cout << "pop_front Expecting 7" << std::endl;
    if(s1->pop_front() != 7) return false;
    std::cout << "pop_front: 7" << std::endl;


    try{
        s1->item_at(2);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->remove(2);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->insert(1, 3);
        return false;
    }
    catch(std::runtime_error){
    }
    std::cout << "clear()-";
    s1->clear();
    std::cout << "\nis_empty(): " << s1->is_empty() << std::endl;
    if(!s1->is_empty()) return false;

    try{
        s1->pop_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->pop_back();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->replace(1, 0);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->remove(0);
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_front();
        return false;
    }
    catch(std::runtime_error){
    }
    try{
        s1->peek_back();
        return false;
    }
    catch(std::runtime_error){
    }

    std::cout << "\n------------TEST SIZE 5 CDAL PASSED---------------\n";

    delete s1;

    return true;
}

bool testCDAL::test150CDAL(){
    std::cout << "\n************TEST SIZE 150 CDAL\n";
    CDAL<int> *s1 = new CDAL<int>();
    for(int i = 0; i < 150; i++){
        s1->push_front(1);
    }
    std::cout << "\ninsert(5, 6)\n";
    s1->insert(5, 6);
    std::ostream stream(std::cout.rdbuf());
    s1->print(stream);
    std::cout << std::endl;
    if(s1->item_at(6) != 5) return false;

    for(int i = 0; i < 151; i++){
        s1->pop_front();
        if(s1->noLength()){
            return false;
        }
    }

    for(int i = 0; i < 150; i++){
        s1->push_back(1);
    }
    if(s1->item_at(50) != 1) return false;
    std::cout << "\nreplace(25, 130)\n";
    s1->replace(25, 130);
    s1->print(stream);
    std::cout << std::endl;
    if(s1->item_at(130) != 25 || s1->length() != 150) return false;
    for(int i = 0; i < 150; i++){
        s1->pop_back();
        if(s1->noLength()){
            return false;
        }
    }

    for(int i = 1; i <= 150; i++){
        s1->push_back(i);
    }
    std::cout << std::endl;
    s1->print(stream);
    std::cout << std::endl;
    for(int i = 1; i <= 20; i++){
        s1->remove(50);
        if(s1->noLength()){
            return false;
        }
    }
    std::cout << "\nRemove the 50 position 20 times\n";
    if(s1->item_at(50) != 71) return false;
    s1->print(stream);
    std::cout << std::endl;
    s1->clear();


    for(int i = 1; i <= 150; i++){
        s1->push_front(i);
    }
    std::cout << std::endl;
    for(int i = 1; i <= 20; i++){
        s1->remove(50);
        if(s1->noLength()){
            return false;
        }
    }
    if(s1->item_at(50) != 80) return false;

    std::cout << "\n------------TEST SIZE 150 CDAL PASSED---------------\n";

    delete s1;

    return true;

}

bool testCDAL::testIterCDAL(){

    std::cout << "\n**************Test Iterator CDAL\n";
    CDAL<int> *s1 = new CDAL<int>();
    for(int i = 100; i >= 0; i--){
        s1->push_front(i);
    }

    CDAL<int>::iterator iterate = s1->begin();
    CDAL<int>::iterator ending = s1->end();

    int i = 0;

    for(; iterate != ending; iterate++){
        std::cout << *iterate << " ";
        if(*iterate != i) return false;
        i++;

    }
    std::cout << "\n\nRange-for loop: ";
    int k = 0;
    for(int i : *s1){
        std::cout << i << " ";
        if(i != k) return false;
        k++;
    }

    std::cout << std::endl;

    CDAL<int>::iterator iter = s1->begin();
    ++iter;
    iterate = iter;     //Original iterator is set equal to an iterator beginning at the second position

    i = 1;
    for(; iterate != ending; ++iterate){
        if(*iterate != i) return false;
        i++;
    }
    CDAL<int>::iterator it(iterate);
    i = 1;
    for(; it != ending; ++it){
        if(*it != i) return false;
        i++;
    }

    delete s1;

//    //-----Testing const_iterators
//
//    CDAL<int> const *s2 = new CDAL<int>();
//    s2->push_back(5);
//    CDAL<int>::const_iterator constIterate = s2->begin();
//    std::cout <<"\nconst_iterator value: " << *constIterate << std::endl;
////  *const Iterate = 6; -------Illegal
//
//    delete s2;

//-----Testing const CDAL
//    CDAL<int> const * s15 = new CDAL<int>();
//    s15->push_back(6); ----------Illegal

    std::cout << "\n------------TEST ITERATOR CDAL PASSED---------------\n";



    return true;

}

bool testCDAL::testCopierCDAL(){
    std::cout << "\n----------------Test Copiers CDAL-----------------" << std::endl;
    CDAL<int> *s1 = new CDAL<int>();
    for(int i = 10; i <= 15; i++){
        s1->push_back(i);
    }
    std::ostream stream(std::cout.rdbuf());
    std::cout << "Original list: ";
    s1->print(stream);
    std::cout << std::endl;
    CDAL<int> s2(*s1);

    std::cout << "Copied list: ";
    s2.print(stream);
    std::cout << std::endl;
    if(s2.peek_front() != 10) return false;
    delete s1;

    CDAL<int> *s3 = new CDAL<int>();
    for(int i = 1; i <= 5; i++){
        s3->push_back(i);
    }
    s2 = *s3;
    std::cout << "Original list: ";
    s3->print(stream);
    std::cout << std::endl;
    if(s2.peek_front() != 1) return false;
    std::cout << "Copied list: ";
    s2.print(stream);
    std::cout << std::endl;

    std::cout << "\n------------TEST COPIERS CDAL PASSED---------------\n";
    delete s3;
    s2.clear();

    return true;

}

#endif // TESTCDAL_H
