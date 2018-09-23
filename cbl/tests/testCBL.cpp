#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CBL.h"



using namespace cop3530;

SCENARIO("TEST SIZE 1 CBL"){


    GIVEN("A CBL of integers is created"){

        CBL<int> *s1 = new CBL<int>();
        std::ostream stream(std::cout.rdbuf());

        WHEN("push_front(6) is called"){
            s1->push_front(6);

            WHEN("peek_front() is called"){
                int data = s1->peek_front();

                THEN("peek_front() should be 6"){
                    REQUIRE(data == 6);
                }
            }
            WHEN("peek_back() is called"){

                int data = s1->peek_back();

                THEN("peek_back() should be 6"){
                    REQUIRE(data == 6);
                }
            }
            WHEN("length() is called"){

                int length = s1->length();

                THEN("length() should be 1"){
                    REQUIRE(length == 1);
                }
            }
            WHEN("is_empty() is called"){

                THEN("is_empty() should be false"){
                    REQUIRE(s1->is_empty() == 0);
                }
            }
            WHEN("contents() is called"){

                int *arr = s1->contents();

                THEN("The returned array should be [6]"){
                    int result[1] = {6};
                    for(size_t i = 0; i < s1->length(); i++){
                        REQUIRE(arr[i] == result[i]);
                    }
                }
                delete[] arr;
            }

            WHEN("print is called"){

                //s1->print(stream);

            }

            WHEN("contains 2 is called"){

                bool cont = s1->contains(2, [](const int& a, const int& b) {
                                return a == b;
                });

                THEN("contains 2 should be false"){
                    REQUIRE(cont == 0);
                }
            }
            WHEN("contains 6 is called"){

                bool cont = s1->contains(6, [](const int& a, const int& b) {
                                return a == b;
                });

                THEN("contains 6 should be true"){
                    REQUIRE(cont == 1);
                }
            }
            WHEN("item_at(1) is called"){    //EXCEPTIONS

                THEN("item_at should throw an exception"){
                    CHECK_THROWS(s1->item_at(1));
                }
            }
            WHEN("remove(1) is called"){

                THEN("remove should throw an exception"){
                    CHECK_THROWS(s1->remove(1));
                }
            }
            WHEN("insert(1, 1) is called"){

                THEN("insert should throw an exception"){
                    CHECK_THROWS(s1->insert(1, 2));
                }
            }
            WHEN("replace(1, 1) is called"){

                THEN("replace should throw an exception"){
                    CHECK_THROWS(s1->replace(1, 1));
                }
            }

            WHEN("pop_back() is called"){     //Pop_back

                int popb = s1->pop_back();

                THEN("pop_back() should be 6"){
                    REQUIRE(popb == 6);
                }

                WHEN("length() is called"){

                    int length = s1->length();

                    THEN("length() should be 0"){
                        REQUIRE(length == 0);

                    }
                }
                WHEN("is_empty() is called"){

                    bool empt = s1->is_empty();

                    THEN("is_empty() should be true"){
                        REQUIRE(empt == 1);

                    }
                }
                WHEN("print is called"){
                    //s1->print(stream);

                }

                WHEN("push_back(6) is called"){     //Push_back

                    s1->push_back(6);

                    WHEN("pop_front() is called"){      //Pop_front

                        int popf = s1->pop_front();

                        THEN("pop_front() should be 6"){
                            REQUIRE(popf == 6);
                        }

                        WHEN("length() is called"){

                            int length = s1->length();
                            THEN("length() should be 0"){
                                REQUIRE(length == 0);
                            }
                        }
                        WHEN("is_empty() is called"){
                            bool empt = s1->is_empty();
                            THEN("is_empty() should be true"){
                                REQUIRE(empt == 1);
                            }
                        }
                        WHEN("print is called"){
                            //s1->print(stream);

                        }
                        WHEN("insert(1, 0) is called"){     //insert

                            s1->insert(1, 0);

                            WHEN("peek_back() is called"){

                                int peekb = s1->peek_back();

                                THEN("peek_back() should be 1"){
                                    REQUIRE(peekb == 1);
                                }

                            }
                            WHEN("peek_front() is called"){

                                int peekf = s1->peek_front();

                                THEN("peek_front() should be 1"){
                                    REQUIRE(peekf == 1);
                                }
                            }
                            WHEN("item_at(0) is called"){

                                int item = s1->item_at(0);

                                THEN("item_at(0) should be 1"){
                                    REQUIRE(item == 1);
                                }

                            }
                            WHEN("length() is called"){

                                int length = s1->length();

                                THEN("length() should be 1"){
                                    REQUIRE(length == 1);
                                }
                            }
                            WHEN("is_empty() is called"){

                                THEN("is_empty() should be false"){
                                    REQUIRE(s1->is_empty() == 0);
                                }
                            }
                            WHEN("print is called"){
                                //s1->print(stream);
                            }
                            WHEN("replace(2, 0) is called"){       //replace

                                int rep = s1->replace(2, 0);

                                THEN("replace(2, 0) should return 1"){
                                    REQUIRE(rep == 1);
                                }
                                WHEN("remove(0) is called"){
                                    int rem = s1->remove(0);
                                    THEN("remove(0) should return 2"){
                                        REQUIRE(rem == 2);
                                    }
                                    WHEN("clear() is called"){

                                        s1->clear();

                                        WHEN("length() is called"){
                                            int len = s1->length();
                                            THEN("length() should be 0"){
                                                REQUIRE(len == 0);
                                            }
                                        }
                                        WHEN("is_empty() is called"){
                                            bool empt = s1->is_empty();

                                            THEN("is_empty() should be true"){
                                                REQUIRE(empt == 1);
                                            }
                                        }
                                        WHEN("print is called"){
                                            //s1->print(stream);

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        delete s1;
    }
}

SCENARIO("TEST SIZE 0 CBL"){
    GIVEN("A CBL of integers is created"){
        std::ostream stream(std::cout.rdbuf());
        CBL<int> *s1 = new CBL<int>();

        WHEN("length() is called"){
            int len = s1->length();
            THEN("length() should be 0"){
                REQUIRE(len == 0);
            }
        }
        WHEN("is_empty() is called"){
            bool empt = s1->is_empty();
            THEN("is_empty() should be true"){
                REQUIRE(empt == 1);
            }
        }
        WHEN("print is called"){
            //s1->print(stream);
        }
        WHEN("contains 2 is called"){

            bool cont = s1->contains(2, [](const int& a, const int& b) {
                                return a == b;
            });
            THEN("contains should return false"){
                REQUIRE(cont == 0);
            }
        }
        WHEN("contains 6 is called"){

            bool cont = s1->contains(6, [](const int& a, const int& b) {
                                return a == b;
            });
            THEN("contains should return false"){
                REQUIRE(cont == 0);
            }
        }
        WHEN("pop_front() is called"){
            THEN("pop_front() should throw an exception"){
                CHECK_THROWS(s1->pop_front());
            }
        }
        WHEN("pop_back() is called"){
            THEN("pop_back() should throw an exception"){
                CHECK_THROWS(s1->pop_back());
            }
        }
        WHEN("replace(1, 0) is called"){
            THEN("replace should throw an exception"){
                CHECK_THROWS(s1->replace(1, 0));
            }
        }
        WHEN("remove(0) is called"){
            THEN("remove should throw an exception"){
                CHECK_THROWS(s1->remove(0));
            }
        }
        WHEN("peek_front() is called"){
            THEN("peek_front() should throw an exception"){
                CHECK_THROWS(s1->peek_front());
            }
        }
        WHEN("peek_back() is called"){
            THEN("peek_back() should throw an exception"){
                CHECK_THROWS(s1->peek_back());
            }
        }
        delete s1;
    }

}

SCENARIO("TEST SIZE 5 CBL"){
    GIVEN("A CBL of integers is created"){
        std::ostream stream(std::cout.rdbuf());
        CBL<int> *s1 = new CBL<int>();

        WHEN("push_back(1) is called 5 times"){
            for(int i = 0; i < 5; i++){
                s1->push_back(1);
            }
            WHEN("contains 1 is called"){
                bool cont = s1->contains(1, [](const int& a, const int& b) {
                                return a == b;
                });
                THEN("contains should return true"){
                    REQUIRE(cont == 1);
                }
            }
            WHEN("print is called"){
                //s1->print(stream);
            }
            WHEN("contents() is called"){

                int *arr = s1->contents();
                THEN("The returned array should be [1, 1, 1, 1, 1]"){
                    int result[5] = {1, 1, 1, 1, 1};
                    for(size_t i = 0; i < s1->length(); i++){
                        REQUIRE(arr[i] == result[i]);
                    }
                }
                delete[] arr;
            }
            WHEN("length() is called"){
                int len = s1->length();
                THEN("length() should be 5"){
                    REQUIRE(len == 5);
                }
            }
            WHEN("remove(0) is called"){
                int rem = s1->remove(0);
                THEN("remove should return 1"){
                    REQUIRE(rem == 1);
                }
                WHEN("length() is called"){
                    int len = s1->length();
                    THEN("length() should be 4"){
                        REQUIRE(len == 4);
                    }
                }
                WHEN("remove(0) is called"){
                    int rem = s1->remove(0);
                    THEN("remove should return 1"){
                        REQUIRE(rem == 1);
                    }
                    WHEN("length() is called"){
                        int len = s1->length();
                        THEN("length() should be 3"){
                            REQUIRE(len == 3);
                        }
                    }
                    WHEN("remove(0) is called"){
                        int rem = s1->remove(0);
                        THEN("remove should return 1"){
                            REQUIRE(rem == 1);
                        }
                        WHEN("length() is called"){
                            int len = s1->length();
                            THEN("length() should be 2"){
                                REQUIRE(len == 2);
                            }
                        }
                        WHEN("remove(0) is called"){
                            int rem = s1->remove(0);
                            THEN("remove should return 1"){
                                REQUIRE(rem == 1);
                            }
                            WHEN("length() is called"){
                                int len = s1->length();
                                THEN("length() should be 1"){
                                    REQUIRE(len == 1);
                                }
                            }
                            WHEN("remove(0) is called"){
                                int rem = s1->remove(0);
                                THEN("remove should return 1"){
                                    REQUIRE(rem == 1);
                                }
                                WHEN("length() is called"){
                                    int len = s1->length();
                                    THEN("length() should be 0"){
                                        REQUIRE(len == 0);
                                    }
                                }
                                WHEN("is_empty() is called"){
                                    bool empt = s1->is_empty();
                                    THEN("is_empty() should be true"){
                                        REQUIRE(empt == 1);
                                    }
                                }
                                WHEN("is_full() is called"){
                                    bool ful = s1->is_full();
                                    THEN("is_full() should be false"){
                                        REQUIRE(ful == 0);
                                    }
                                }
                                WHEN("push_back(1000) is called"){
                                    s1->push_back(1000);
                                    WHEN("print is called"){
                                        //s1->print(stream);
                                    }
                                    WHEN("push_front(8) is called"){
                                        s1->push_front(8);
                                        WHEN("print is called"){
                                            //s1->print(stream);
                                        }
                                        WHEN("insert(9, 1) is called"){
                                            s1->insert(9, 1);
                                            WHEN("print is called"){
                                                //s1->print(stream);
                                            }
                                            WHEN("insert(7, 0) is called"){
                                                s1->insert(7, 0);
                                                WHEN("print is called"){
                                                    //s1->print(stream);
                                                }
                                                WHEN("push_back(5) is called"){
                                                    s1->push_back(5);
                                                    WHEN("print is called"){
                                                        //s1->print(stream);
                                                    }
                                                    WHEN("remove(2) is called"){
                                                        int rem = s1->remove(2);
                                                        THEN("remove(2) should return 9"){
                                                            REQUIRE(rem == 9);
                                                        }
                                                        WHEN("print is called"){
                                                            //s1->print(stream);
                                                        }
                                                        WHEN("peek_back() is called"){
                                                            int peekb = s1->peek_back();
                                                            THEN("peek_back() should return 5"){
                                                                REQUIRE(peekb == 5);
                                                            }
                                                        }
                                                        WHEN("peek_front() is called"){
                                                            int peekf = s1->peek_front();
                                                            THEN("peek_front() should return 7"){
                                                                REQUIRE(peekf == 7);
                                                            }
                                                        }
                                                        WHEN("item_at(2) is called"){
                                                            int ite = s1->item_at(2);
                                                            THEN("item_at(2) should return 1000"){
                                                                REQUIRE(ite == 1000);
                                                            }
                                                        }
                                                        WHEN("replace(3, 1) is called"){
                                                            int rep = s1->replace(3, 1);
                                                            THEN("replace(3, 1) should return 8"){
                                                                REQUIRE(rep == 8);
                                                            }
                                                            WHEN("item_at(1) is called"){
                                                                int ite = s1->item_at(1);
                                                                THEN("item_at(1) should return 3"){
                                                                    REQUIRE(ite == 3);
                                                                }
                                                            }
                                                            WHEN("pop_back() is called"){
                                                                int popb = s1->pop_back();
                                                                THEN("pop_back() should return 5"){
                                                                    REQUIRE(popb == 5);
                                                                }
                                                                WHEN("pop_front() is called"){
                                                                    int popf = s1->pop_front();
                                                                    THEN("pop_front() should return 7"){
                                                                        REQUIRE(popf == 7);
                                                                    }
                                                                    WHEN("item_at(2) is called"){
                                                                        THEN("item_at(2) should throw an exception"){
                                                                            CHECK_THROWS(s1->item_at(2));
                                                                        }
                                                                    }
                                                                    WHEN("remove(2) is called"){
                                                                        THEN("remove(2) should throw an exception"){
                                                                            CHECK_THROWS(s1->remove(2));
                                                                        }
                                                                    }
                                                                    WHEN("insert(1, 3) is called"){
                                                                        THEN("insert(1, 3) should throw an exception"){
                                                                            CHECK_THROWS(s1->insert(1, 3));
                                                                        }
                                                                    }
                                                                    WHEN("clear() is called"){
                                                                        s1->clear();
                                                                        WHEN("is_empty() is called"){
                                                                            bool empt = s1->is_empty();
                                                                            THEN("is_empty() should be true"){
                                                                                REQUIRE(empt == 1);
                                                                            }
                                                                        }
                                                                        WHEN("pop_front() is called"){
                                                                            THEN("pop_front() should throw an exception"){
                                                                                CHECK_THROWS(s1->pop_front());
                                                                            }
                                                                        }
                                                                        WHEN("pop_back() is called"){
                                                                            THEN("pop_back() should throw an exception"){
                                                                                CHECK_THROWS(s1->pop_back());
                                                                            }
                                                                        }
                                                                        WHEN("replace(1, 0) is called"){
                                                                            THEN("replace(1, 0) should throw an exception"){
                                                                                CHECK_THROWS(s1->replace(1, 0));
                                                                            }
                                                                        }
                                                                        WHEN("remove(0) is called"){
                                                                            THEN("remove(0) should throw an exception"){
                                                                                CHECK_THROWS(s1->remove(0));
                                                                            }
                                                                        }
                                                                        WHEN("peek_front() is called"){
                                                                            THEN("peek_front() should throw an exception"){
                                                                                CHECK_THROWS(s1->peek_front());
                                                                            }
                                                                        }
                                                                        WHEN("peek_back() is called"){
                                                                            THEN("peek_back() should throw an exception"){
                                                                                CHECK_THROWS(s1->peek_back());
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        delete s1;
    }
}


SCENARIO("TEST SIZE 150 CBL"){
    GIVEN("A CBL of integers is created"){
        CBL<int> *s1 = new CBL<int>();
        std::ostream stream(std::cout.rdbuf());
        WHEN("push_front(1) is called 150 times to add 150 1's to the list"){
            for(int i = 0; i < 150; i++){
                s1->push_front(1);
            }
            WHEN("print is called"){
                //s1->print(stream);
            }
            WHEN("pop_front() is called 150 times to empty the list"){
                for(int i = 0; i < 150; i++){
                        s1->pop_front();
                }
                THEN("The capacity condition should not be violated"){
                    REQUIRE(s1->testCap() == 1);
                }

                WHEN("push_back(1) is called 150 times to add 150 1's to the list"){
                    for(int i = 0; i < 150; i++){
                        s1->push_back(1);
                    }
                    WHEN("insert(10, 10) is called"){
                        s1->insert(10, 10);
                        THEN("item_at(10) should return 10"){
                            REQUIRE(s1->item_at(10) == 10);
                        }
                        WHEN("remove(0) is called 151 times to empty the list"){
                            for(int i = 0; i < 151; i++){
                                s1->remove(0);
                            }
                            THEN("The capacity condition should not be violated"){
                                REQUIRE(s1->testCap() == 1);
                            }
                            WHEN("length() is called"){
                                int len = s1->length();
                                THEN("length() should be 0"){
                                    REQUIRE(len == 0);
                                }
                            }
                            WHEN("is_empty() is called"){
                                bool empt = s1->is_empty();
                                THEN("is_empty() should return true"){
                                    REQUIRE(empt == 1);
                                }
                            }
                        }
                    }
                }
            }
        }
        delete s1;
    }
}


SCENARIO("TEST CBL ITERATOR"){
    GIVEN("A CBL of integers is created"){
        CBL<int> *s1 = new CBL<int>();
        for(int i = 0; i < 100; i++){
            s1->push_front(i);
        }
        CBL<int>::iterator iterate = s1->begin();
        CBL<int>::iterator ending = s1->end();
        WHEN("The list is iterated through using begin() and end() iterators"){
            THEN("The dereferenced iterator should return the elements in the list"){
                int i = 99;
                for(; iterate != ending; ++iterate){
                    REQUIRE(i == *iterate);
                    i--;
                }
            }
        }
        WHEN("A range-based for loop is created to iterate through the list"){
            THEN("The for loop should iterate through the elements in the list"){
                int k = 99;
                for(int i : *s1){
                    REQUIRE(k == i);
                    k--;
                }
            }
        }
        WHEN("The iterator is set equal to an iterator pointing to the second element in the list"){
            CBL<int>::iterator iter = s1->begin();
            ++iter;
            iterate = iter;

            THEN("When iterating through the list the new iterator should return everything from position 2 onwards"){
                int i = 98;
                for(; iterate != ending; ++iterate){
                    REQUIRE(i == *iterate);
                    i--;
                }
            }
            WHEN("An iterator is instantiated using another iterator"){
                CBL<int>::iterator it(iterate);

                THEN("The instantiated iterator should be at the position of the other iterator"){
                    int i = 98;
                    for(; it != ending; ++it){
                        REQUIRE(i == *it);
                        i--;
                    }
                }
            }
        }

        delete s1;
    }
}
SCENARIO("TEST CBL COPIER"){
    GIVEN("A CBL of integers s1 is created with elements 5 through 1 in that order"){
        CBL<int> *s1 = new CBL<int>();
        for(int i = 0; i < 5; i++){
            s1->push_front(i + 1);
        }
        WHEN("A CBL of integers s2 is created with a copy constructor using s1"){
            CBL<int> s2(*s1);
            THEN("s2 should contain the same elements as s1"){
                int compare[5] = {5, 4, 3, 2, 1};
                int *arr = s2.contents();
                for(size_t i = 0; i < s2.length(); i++){
                    REQUIRE(compare[i] == arr[i]);
                }
                delete[] arr;
            }
            WHEN("s2 uses the copy assignment operator with new CBL s3"){
                CBL<int> *s3 = new CBL<int>();
                for(int i = 0; i < 5; i++){
                    s3->push_back(i + 1);
                }
                s2 = *s3;
                THEN("s2 should contain the same elements as s3"){
                    int compare2[5] = {1, 2, 3, 4, 5};
                    int *arr = s2.contents();
                    for(size_t i = 0; i < s2.length(); i++){
                        REQUIRE(compare2[i] == arr[i]);
                    }
                    delete[] arr;
                }
                delete s3;
            }
            s2.clear();
        }
        delete s1;
    }
}
SCENARIO("TEST CONST ITERATOR"){
    GIVEN("A const CBL of integers is created"){
        CBL<int> const *cbl = new CBL<int>();
        WHEN("A const iterator is created"){
            CBL<int>::const_iterator iter = cbl->begin();
            THEN("If the iterator tries to change the contents there will be a compiler error"){
//                *iter = 6; --------Illegal
            }
        }
        delete cbl;
    }

}
SCENARIO("TEST CONST CBL"){
    GIVEN("A const CBL of integers is created"){
        CBL<int> const *cbl = new CBL<int>();
        WHEN("Push_back(5) is called there should be compiler error"){
//            cbl->push_back(5); ------Illegal
        }
        delete cbl;
    }
}
