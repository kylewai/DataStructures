#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AVL.h"



bool comparison_functionV(const int& key1, const int& key2){
    if(key1 < key2){
        return true;
    }
    return false;
}
bool equality_functionV(const int& key1, const int& key2){
    if(key1 == key2){
        return true;
    }
    return false;
}


using namespace cop3530;

SCENARIO("TEST SIZE 1 AVL"){
    GIVEN("A BST of integers is created"){


        AVL<int, int, comparison_functionV, equality_functionV> * bst = new AVL<int, int, comparison_functionV, equality_functionV>();

        WHEN("insert with key 7 and value 7 is called"){

            bst->insert(7, 7);

            THEN("lookup(7) should return 7"){
                int dat = bst->lookup(7);
                REQUIRE(dat == 7);
            }

            THEN("contains(7) should return true"){
                REQUIRE(bst->contains(7) == true);
            }
            THEN("is_empty() should return false"){
                REQUIRE(bst->is_empty() == 0);
            }
            THEN("is_full() should return false"){
                REQUIRE(bst->is_full() == 0);
            }
            THEN("size() should return 1"){
                REQUIRE(bst->size() == 1);
            }
            THEN("height() should return 0"){
                REQUIRE(bst->height() == 0);
            }
            THEN("balance() should return 0"){

                REQUIRE(bst->balance() == 0);
            }

            WHEN("remove(7) is called"){
                bst->remove(7);


                THEN("lookup(7) should throw an exception"){
                    CHECK_THROWS(bst->lookup(7));
                }

                THEN("contains(7) should return false"){
                    bool cont = bst->contains(7);
                    REQUIRE(cont == false);
                }
                THEN("is_empty() should return true"){
                    bool empt = bst->is_empty();
                    REQUIRE(empt == true);
                }
                THEN("is_full() should return false"){
                    REQUIRE(bst->is_full() == 0);
                }
                THEN("size() should return 0"){
                    REQUIRE(bst->size() == 0);
                }
                THEN("height() should return 0"){
                    REQUIRE(bst->height() == 0);
                }
                THEN("balance() should return 0"){
                    REQUIRE(bst->balance() == 0);
                }
            }
        }
        delete bst;
    }
}

SCENARIO("TEST SIZE 8 AVL"){
    GIVEN("An AVL of integers is created"){
        AVL<int, int, comparison_functionV, equality_functionV> * bst = new AVL<int, int, comparison_functionV, equality_functionV>();
        WHEN("insert with key 7 and value 7 is called"){
            bst->insert(7, 7);
            THEN("The level order traversal should be: 7"){
                int *test = bst->contents();
                int compare[1] = {7};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
            WHEN("insert with key 8 and value 8 is called"){
                bst->insert(8, 8);
                THEN("The level order traversal should be: 7 8"){
                    int *test = bst->contents();
                    int compare[2] = {7, 8};
                    for(size_t i = 0; i < bst->size(); i++){
                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                    }
                    delete[] test;
                    bst->print();
                }

                THEN("contains(8) should return true"){
                    REQUIRE(bst->contains(8) == true);
                }
                THEN("is_empty() should return false"){
                    REQUIRE(bst->is_empty() == false);
                }
                THEN("is_full() should return false"){
                    REQUIRE(bst->is_full() == 0);
                }
                THEN("size() should return 2"){
                    REQUIRE(bst->size() == 2);
                }
                THEN("height() should return 1"){
                    REQUIRE(bst->height() == 1);
                }
                THEN("balance() should return -1"){
                    REQUIRE(bst->balance() == -1);
                }
                THEN("lookup(8) should return 8"){
                    REQUIRE(bst->lookup(8) == 8);
                }

                WHEN("insert with key 3 and value 3 is called"){
                    bst->insert(3, 3);
                    THEN("The level order traversal should be: 7 3 8"){
                        int *test = bst->contents();
                        int compare[3] = {7, 3, 8};
                        for(size_t i = 0; i < bst->size(); i++){
                            REQUIRE(equality_functionV(compare[i], test[i]) == true);
                        }
                        delete[] test;
                        bst->print();
                    }
                    THEN("contains(3) should return false"){
                        REQUIRE(bst->contains(3) == true);
                    }
                    THEN("is_empty() should return false"){
                        REQUIRE(bst->is_empty() == false);
                    }
                    THEN("is_full() should return false"){
                        REQUIRE(bst->is_full() == 0);
                    }
                    THEN("size() should return 3"){
                        REQUIRE(bst->size() == 3);
                    }
                    THEN("height() should return 1"){
                        REQUIRE(bst->height() == 1);
                    }
                    THEN("balance() should return 0"){
                        REQUIRE(bst->balance() == 0);
                    }
                    THEN("lookup(3) should return 3"){
                        REQUIRE(bst->lookup(3) == 3);
                    }

                    WHEN("insert with key 2 and value 2 is called"){
                        bst->insert(2, 2);
                        THEN("The level order traversal should be: 7 3 8 2"){
                            int *test = bst->contents();
                            int compare[4] = {7, 3, 8, 2};
                            for(size_t i = 0; i < bst->size(); i++){
                                REQUIRE(equality_functionV(compare[i], test[i]) == true);
                            }
                            delete[] test;
                            bst->print();
                        }
                        THEN("contains(2) should return true"){
                            REQUIRE(bst->contains(2) == true);
                        }
                        THEN("is_empty() should return false"){
                            REQUIRE(bst->is_empty() == false);
                        }
                        THEN("is_full() should return false"){
                            REQUIRE(bst->is_full() == 0);
                        }
                        THEN("size() should return 4"){
                            REQUIRE(bst->size() == 4);
                        }
                        THEN("height() should return 2"){
                            REQUIRE(bst->height() == 2);
                        }
                        THEN("balance() should return 1"){
                            REQUIRE(bst->balance() == 1);
                        }
                        THEN("lookup(2) should return 2"){
                            REQUIRE(bst->lookup(2) == 2);
                        }

                        WHEN("insert with key 5 and value 5 is called"){
                            bst->insert(5, 5);
                            THEN("The level order traversal should be: 7 3 8 2 5"){
                                int *test = bst->contents();
                                int compare[5] = {7, 3, 8, 2, 5};
                                for(size_t i = 0; i < bst->size(); i++){
                                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                }
                                delete[] test;
                                bst->print();
                            }
                            THEN("contains(5) should return false"){
                                REQUIRE(bst->contains(5) == true);
                            }
                            THEN("is_empty() should return false"){
                                REQUIRE(bst->is_empty() == false);
                            }
                            THEN("is_full() should return false"){
                                REQUIRE(bst->is_full() == 0);
                            }
                            THEN("size() should return 5"){
                                REQUIRE(bst->size() == 5);
                            }
                            THEN("height() should return 2"){
                                REQUIRE(bst->height() == 2);
                            }
                            THEN("balance() should return 1"){
                                REQUIRE(bst->balance() == 1);
                            }
                            THEN("lookup(5) should return 5"){
                                REQUIRE(bst->lookup(5) == 5);
                            }

                            WHEN("insert with key 4 and value 4 is called"){
                                bst->insert(4, 4);
                                THEN("The level order traversal should be: 5 3 7 2 4 8"){
                                    int *test = bst->contents();
                                    int compare[6] = {5, 3, 7, 2, 4, 8};
                                    for(size_t i = 0; i < bst->size(); i++){
                                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                    }
                                    delete[] test;
                                    bst->print();
                                }
                                THEN("contains(4) should return false"){
                                    REQUIRE(bst->contains(4) == true);
                                }
                                THEN("is_empty() should return false"){
                                    REQUIRE(bst->is_empty() == false);
                                }
                                THEN("is_full() should return false"){
                                    REQUIRE(bst->is_full() == 0);
                                }
                                THEN("size() should return 6"){
                                    REQUIRE(bst->size() == 6);
                                }
                                THEN("height() should return 2"){
                                    REQUIRE(bst->height() == 2);
                                }
                                THEN("balance() should return 0"){
                                    REQUIRE(bst->balance() == 0);
                                }
                                THEN("lookup(4) should return 4"){
                                    REQUIRE(bst->lookup(4) == 4);
                                }

                                WHEN("insert with key 6 and value 6 is called"){
                                    bst->insert(6, 6);
                                    THEN("The level order traversal should be: 5 3 7 2 4 6 8"){
                                        int *test = bst->contents();
                                        int compare[7] = {5, 3, 7, 2, 4, 6, 8};
                                        for(size_t i = 0; i < bst->size(); i++){
                                            REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                        }
                                        delete[] test;
                                        bst->print();
                                    }
                                    THEN("contains(6) should return false"){
                                        REQUIRE(bst->contains(6) == true);
                                    }
                                    THEN("is_empty() should return false"){
                                        REQUIRE(bst->is_empty() == false);
                                    }
                                    THEN("is_full() should return false"){
                                        REQUIRE(bst->is_full() == 0);
                                    }
                                    THEN("size() should return 7"){
                                        REQUIRE(bst->size() == 7);
                                    }
                                    THEN("height() should return 2"){
                                        REQUIRE(bst->height() == 2);
                                    }
                                    THEN("balance() should return 0"){
                                        REQUIRE(bst->balance() == 0);
                                    }
                                    THEN("lookup(6) should return 6"){
                                        REQUIRE(bst->lookup(6) == 6);
                                    }

                                    WHEN("insert with key 10 and value 10 is called"){
                                        bst->insert(10, 10);
                                        THEN("The level order traversal should be: 5 3 7 2 4 6 8 10"){
                                            int *test = bst->contents();
                                            int compare[8] = {5, 3, 7, 2, 4, 6, 8, 10};
                                            for(size_t i = 0; i < bst->size(); i++){
                                                REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                            }
                                            delete[] test;
                                            bst->print();
                                        }
                                        THEN("contains(10) should return false"){
                                            REQUIRE(bst->contains(10) == true);
                                        }
                                        THEN("is_empty() should return false"){
                                            REQUIRE(bst->is_empty() == false);
                                        }
                                        THEN("is_full() should return false"){
                                            REQUIRE(bst->is_full() == 0);
                                        }
                                        THEN("size() should return 8"){
                                            REQUIRE(bst->size() == 8);
                                        }
                                        THEN("height() should return 3"){
                                            REQUIRE(bst->height() == 3);
                                        }
                                        THEN("balance() should return -1"){
                                            REQUIRE(bst->balance() == -1);
                                        }
                                        THEN("lookup(10) should return 10"){
                                            REQUIRE(bst->lookup(10) == 10);
                                        }
                                        THEN("checkBal() should return true"){
                                            REQUIRE(bst->checkBalInit() == true);
                                        }

                                        WHEN("remove(3) is called"){
                                            bst->remove(3);
                                            THEN("The level order traversal should be: 5 4 7 2 6 8 10"){
                                                int *test = bst->contents();
                                                int compare[7] = {5, 4, 7, 2, 6, 8, 10};
                                                for(size_t i = 0; i < bst->size(); i++){
                                                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                }
                                                delete[] test;
                                                bst->print();
                                            }
                                            THEN("size() should return 7"){
                                                REQUIRE(bst->size() == 7);
                                            }
                                            THEN("height() should return 3"){
                                                REQUIRE(bst->height() == 3);
                                            }
                                            THEN("balance() should return -1"){
                                                REQUIRE(bst->balance() == -1);
                                            }
                                            THEN("lookup(3) should throw an exception"){
                                                CHECK_THROWS(bst->lookup(3));
                                            }
                                            THEN("remove(3) should throw an exception"){
                                                CHECK_THROWS(bst->remove(3));
                                            }
                                            THEN("checkBal() should return true"){
                                                REQUIRE(bst->checkBalInit() == true);
                                            }

                                            WHEN("remove(5) is called"){
                                                bst->remove(5);
                                                THEN("The level order traversal should be: 6 4 8 2 7 10"){
                                                    int *test = bst->contents();
                                                    int compare[6] = {6, 4, 8, 2, 7, 10};
                                                    for(size_t i = 0; i < bst->size(); i++){
                                                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                    }
                                                    delete[] test;
                                                    bst->print();
                                                }

                                                THEN("size() should return 6"){
                                                    REQUIRE(bst->size() == 6);
                                                }
                                                THEN("height() should return 2"){
                                                    REQUIRE(bst->height() == 2);
                                                }
                                                THEN("balance() should return 0"){
                                                    REQUIRE(bst->balance() == 0);
                                                }
                                                THEN("lookup(5) should throw an exception"){
                                                    CHECK_THROWS(bst->lookup(5));
                                                }
                                                THEN("remove(5) should throw an exception"){
                                                    CHECK_THROWS(bst->remove(5));
                                                }
                                                THEN("checkBal() should return true"){
                                                    REQUIRE(bst->checkBalInit() == true);
                                                }
                                                WHEN("clear() is called"){
                                                    bst->clear();
                                                    THEN("is_empty() should return true"){
                                                        REQUIRE(bst->is_empty() == true);
                                                    }
                                                    THEN("is_full() should return false"){
                                                        REQUIRE(bst->is_full() == 0);
                                                    }
                                                    THEN("size() should return 0"){
                                                        REQUIRE(bst->size() == 0);
                                                    }
                                                    THEN("height() should return 0"){
                                                        REQUIRE(bst->height() == 0);
                                                    }
                                                    THEN("balance() should return 0"){
                                                        REQUIRE(bst->balance() == 0);
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
        delete bst;
    }
    GIVEN("An AVL of integers is created"){
        AVL<int, int, comparison_functionV, equality_functionV> * bst = new AVL<int, int, comparison_functionV, equality_functionV>();
        WHEN("insert with key 10 and value 10 is called"){
            bst->insert(10, 10);
            THEN("The level order traversal should be: 10"){
                int *test = bst->contents();
                int compare[1] = {10};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
            THEN("contains(10) should return true"){
                REQUIRE(bst->contains(10) == true);
            }
            THEN("size() should return 1"){
                REQUIRE(bst->size() == 1);
            }
            THEN("height() should return 0"){
                REQUIRE(bst->height() == 0);
            }
            THEN("balance() should return 0"){
                REQUIRE(bst->balance() == 0);
            }
            THEN("lookup(10) should return 10"){
                REQUIRE(bst->lookup(10) == 10);
            }

            WHEN("insert with key 7 and value 7 is called"){
                bst->insert(7, 7);
                THEN("The level order traversal should be: 10 7"){
                    int *test = bst->contents();
                    int compare[2] = {10, 7};
                    for(size_t i = 0; i < bst->size(); i++){
                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                    }
                    delete[] test;
                    bst->print();
                }
                THEN("contains(7) should return true"){
                    REQUIRE(bst->contains(7) == true);
                }
                THEN("size() should return 2"){
                    REQUIRE(bst->size() == 2);
                }
                THEN("height() should return 1"){
                    REQUIRE(bst->height() == 1);
                }
                THEN("balance() should return 1"){
                    REQUIRE(bst->balance() == 1);
                }
                THEN("lookup(7) should return 7"){
                    REQUIRE(bst->lookup(7) == 7);
                }

                WHEN("insert with key 15 and value 15 is called"){
                    bst->insert(15, 15);
                    THEN("The level order traversal should be: 10 7 15"){
                        int *test = bst->contents();
                        int compare[3] = {10, 7, 15};
                        for(size_t i = 0; i < bst->size(); i++){
                            REQUIRE(equality_functionV(compare[i], test[i]) == true);
                        }
                        delete[] test;
                        bst->print();
                    }
                    THEN("contains(15) should return true"){
                        REQUIRE(bst->contains(15) == true);
                    }
                    THEN("size() should return 3"){
                        REQUIRE(bst->size() == 3);
                    }
                    THEN("height() should return 1"){
                        REQUIRE(bst->height() == 1);
                    }
                    THEN("balance() should return 0"){
                        REQUIRE(bst->balance() == 0);
                    }
                    THEN("lookup(15) should return 15"){
                        REQUIRE(bst->lookup(15) == 15);
                    }

                    WHEN("insert with key 4 and value 4 is called"){
                        bst->insert(4, 4);
                        THEN("The level order traversal should be: 10 7 15 4"){
                            int *test = bst->contents();
                            int compare[4] = {10, 7, 15, 4};
                            for(size_t i = 0; i < bst->size(); i++){
                                REQUIRE(equality_functionV(compare[i], test[i]) == true);
                            }
                            delete[] test;
                            bst->print();
                        }
                        THEN("contains(4) should return true"){
                            REQUIRE(bst->contains(4) == true);
                        }
                        THEN("size() should return 4"){
                            REQUIRE(bst->size() == 4);
                        }
                        THEN("height() should return 2"){
                            REQUIRE(bst->height() == 2);
                        }
                        THEN("balance() should return 1"){
                            REQUIRE(bst->balance() == 1);
                        }
                        THEN("lookup(4) should return 4"){
                            REQUIRE(bst->lookup(4) == 4);
                        }

                        WHEN("insert with key 9 and value 9 is called"){
                            bst->insert(9, 9);
                            THEN("The level order traversal should be: 10 7 15 4 9"){
                                int *test = bst->contents();
                                int compare[5] = {10, 7, 15, 4, 9};
                                for(size_t i = 0; i < bst->size(); i++){
                                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                }
                                delete[] test;
                                bst->print();
                            }
                            THEN("contains(9) should return true"){
                                REQUIRE(bst->contains(9) == true);
                            }
                            THEN("size() should return 5"){
                                REQUIRE(bst->size() == 5);
                            }
                            THEN("height() should return 2"){
                                REQUIRE(bst->height() == 2);
                            }
                            THEN("balance() should return 1"){
                                REQUIRE(bst->balance() == 1);
                            }
                            THEN("lookup(9) should return 9"){
                                REQUIRE(bst->lookup(9) == 9);
                            }

                            WHEN("insert with key 14 and value 14 is called"){
                                bst->insert(14, 14);
                                THEN("The level order traversal should be: 10 7 15 4 9 14"){
                                    int *test = bst->contents();
                                    int compare[6] = {10, 7, 15, 4, 9, 14};
                                    for(size_t i = 0; i < bst->size(); i++){
                                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                    }
                                    delete[] test;
                                    bst->print();
                                }
                                THEN("contains(14) should return true"){
                                    REQUIRE(bst->contains(14) == true);
                                }
                                THEN("size() should return 6"){
                                    REQUIRE(bst->size() == 6);
                                }
                                THEN("height() should return 2"){
                                    REQUIRE(bst->height() == 2);
                                }
                                THEN("balance() should return 0"){
                                    REQUIRE(bst->balance() == 0);
                                }
                                THEN("lookup(14) should return 14"){
                                    REQUIRE(bst->lookup(14) == 14);
                                }

                                WHEN("insert with key 16 and value 16 is called"){
                                    bst->insert(16, 16);
                                    THEN("The level order traversal should be: 10 7 15 4 9 14 16"){
                                        int *test = bst->contents();
                                        int compare[7] = {10, 7, 15, 4, 9, 14, 16};
                                        for(size_t i = 0; i < bst->size(); i++){
                                            REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                        }
                                        delete[] test;
                                        bst->print();
                                    }
                                    THEN("contains(16) should return true"){
                                        REQUIRE(bst->contains(16) == true);
                                    }
                                    THEN("size() should return 7"){
                                        REQUIRE(bst->size() == 7);
                                    }
                                    THEN("height() should return 2"){
                                        REQUIRE(bst->height() == 2);
                                    }
                                    THEN("balance() should return 0"){
                                        REQUIRE(bst->balance() == 0);
                                    }
                                    THEN("lookup(16) should return 16"){
                                        REQUIRE(bst->lookup(16) == 16);
                                    }

                                    WHEN("insert with key 2 and value 2 is called"){
                                        bst->insert(2, 2);
                                        THEN("The level order traversal should be: 10 7 15 4 9 14 16 2"){
                                            int *test = bst->contents();
                                            int compare[8] = {10, 7, 15, 4, 9, 14, 16, 2};
                                            for(size_t i = 0; i < bst->size(); i++){
                                                REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                            }
                                            delete[] test;
                                            bst->print();
                                        }
                                        THEN("contains(2) should return true"){
                                            REQUIRE(bst->contains(2) == true);
                                        }
                                        THEN("size() should return 8"){
                                            REQUIRE(bst->size() == 8);
                                        }
                                        THEN("height() should return 3"){
                                            REQUIRE(bst->height() == 3);
                                        }
                                        THEN("balance() should return 1"){
                                            REQUIRE(bst->balance() == 1);
                                        }
                                        THEN("lookup(2) should return 2"){
                                            REQUIRE(bst->lookup(2) == 2);
                                        }

                                        WHEN("insert with key 3 and value 3 is called"){
                                            bst->insert(3, 3);
                                            THEN("The level order traversal should be: 10 7 15 3 9 14 16 2 4"){
                                                int *test = bst->contents();
                                                int compare[9] = {10, 7, 15, 3, 9, 14, 16, 2, 4};
                                                for(size_t i = 0; i < bst->size(); i++){
                                                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                }
                                                delete[] test;
                                                bst->print();
                                            }
                                            THEN("contains(3) should return true"){
                                                REQUIRE(bst->contains(3) == true);
                                            }
                                            THEN("size() should return 9"){
                                                REQUIRE(bst->size() == 9);
                                            }
                                            THEN("height() should return 3"){
                                                REQUIRE(bst->height() == 3);
                                            }
                                            THEN("balance() should return 1"){
                                                REQUIRE(bst->balance() == 1);
                                            }
                                            THEN("lookup(3) should return 3"){
                                                REQUIRE(bst->lookup(3) == 3);
                                            }

                                            WHEN("insert with key 20 and value 20 is called"){
                                                bst->insert(20, 20);
                                                THEN("The level order traversal should be: 10 7 15 3 9 14 16 2 4 20"){
                                                    int *test = bst->contents();
                                                    int compare[10] = {10, 7, 15, 3, 9, 14, 16, 2, 4, 20};
                                                    for(size_t i = 0; i < bst->size(); i++){
                                                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                    }
                                                    delete[] test;
                                                    bst->print();
                                                }
                                                THEN("contains(20) should return true"){
                                                    REQUIRE(bst->contains(20) == true);
                                                }
                                                THEN("size() should return 10"){
                                                    REQUIRE(bst->size() == 10);
                                                }
                                                THEN("height() should return 3"){
                                                    REQUIRE(bst->height() == 3);
                                                }
                                                THEN("balance() should return 0"){
                                                    REQUIRE(bst->balance() == 0);
                                                }
                                                THEN("lookup(20) should return 20"){
                                                    REQUIRE(bst->lookup(20) == 20);
                                                }

                                                WHEN("insert with key 17 and value 17 is called"){
                                                    bst->insert(17, 17);
                                                    THEN("The level order traversal should be: 10 7 15 3 9 14 17 2 4 16 20"){
                                                        int *test = bst->contents();
                                                        int compare[11] = {10, 7, 15, 3, 9, 14, 17, 2, 4, 16, 20};
                                                        for(size_t i = 0; i < bst->size(); i++){
                                                            REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                        }
                                                        delete[] test;
                                                        bst->print();
                                                    }
                                                    THEN("contains(17) should return true"){
                                                        REQUIRE(bst->contains(17) == true);
                                                    }
                                                    THEN("size() should return 11"){
                                                        REQUIRE(bst->size() == 11);
                                                    }
                                                    THEN("height() should return 3"){
                                                        REQUIRE(bst->height() == 3);
                                                    }
                                                    THEN("balance() should return 0"){
                                                        REQUIRE(bst->balance() == 0);
                                                    }
                                                    THEN("lookup(3) should return 17"){
                                                        REQUIRE(bst->lookup(17) == 17);
                                                    }

                                                    WHEN("remove(16) is called"){
                                                        bst->remove(16);
                                                        THEN("The level order traversal should be: 10 7 15 3 9 14 17 2 4 20"){
                                                            int *test = bst->contents();bst->print();
                                                            int compare[10] = {10, 7, 15, 3, 9, 14, 17, 2, 4, 20};
                                                            for(size_t i = 0; i < bst->size(); i++){
                                                                REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                            }
                                                            delete[] test;

                                                        }
                                                        THEN("size() should return 10"){
                                                            REQUIRE(bst->size() == 10);
                                                        }
                                                        THEN("height() should return 3"){
                                                            REQUIRE(bst->height() == 3);
                                                        }
                                                        THEN("balance() should return 0"){
                                                            REQUIRE(bst->balance() == 0);
                                                        }

                                                         WHEN("insert with key 30 and value 30 is called"){
                                                            bst->insert(30, 30);
                                                            THEN("The level order traversal should be: 10 7 15 3 9 14 20 2 4 17 30"){
                                                                int *test = bst->contents();
                                                                int compare[11] = {10, 7, 15, 3, 9, 14, 20, 2, 4, 17, 30};
                                                                for(size_t i = 0; i < bst->size(); i++){
                                                                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                                                                }
                                                                delete[] test;
                                                                bst->print();
                                                            }
                                                            THEN("contains(30) should return true"){
                                                                REQUIRE(bst->contains(30) == true);
                                                            }
                                                            THEN("size() should return 11"){
                                                                REQUIRE(bst->size() == 11);
                                                            }
                                                            THEN("height() should return 3"){
                                                                REQUIRE(bst->height() == 3);
                                                            }
                                                            THEN("balance() should return 0"){
                                                                REQUIRE(bst->balance() == 0);
                                                            }
                                                            THEN("lookup(30) should return 30"){
                                                                REQUIRE(bst->lookup(30) == 30);
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
        delete bst;
    }
}


SCENARIO("TEST DUPLICATE KEYS"){
    GIVEN("An AVL of integers is created"){
        AVL<int, int, comparison_functionV, equality_functionV> * bst = new AVL<int, int, comparison_functionV, equality_functionV>();

        WHEN("insert with keys 10, 7, 15, 4, 9, 14, 16 with all values 1 is called"){
            bst->insert(10, 1);
            bst->insert(7, 1);
            bst->insert(15, 1);
            bst->insert(4, 1);
            bst->insert(9, 1);
            bst->insert(14, 1);
            bst->insert(16, 1);
            WHEN("insert with a duplicate key 7 is called with a different value 5"){
                bst->insert(7, 5);
                THEN("The level order traversal should be: 10 7 15 4 9 14 16"){
                    int *test = bst->contents();
                    int compare[7] = {10, 7, 15, 4, 9, 14, 16};
                    for(size_t i = 0; i < bst->size(); i++){
                        REQUIRE(equality_functionV(compare[i], test[i]) == true);
                    }
                    delete[] test;
                    bst->print();
                }
                THEN("The value of key 7 should be 5"){
                    REQUIRE(bst->lookup(7) == 5);
                }
            }
        }
        delete bst;
    }
}

SCENARIO("TEST COPY CONSTRUCTORS"){
    GIVEN("An AVL of integers is created"){
        AVL<int, int, comparison_functionV, equality_functionV> * bst = new AVL<int, int, comparison_functionV, equality_functionV>();
        bst->insert(10, 1);
        bst->insert(7, 1);
        bst->insert(15, 1);
        bst->insert(4, 1);
        bst->insert(9, 1);
        bst->insert(14, 1);
        bst->insert(3, 1);
        WHEN("A new AVL object is instantiated using the copy constructor"){
            AVL<int, int, comparison_functionV, equality_functionV> cop(*bst);
            THEN("It should contain the same tree as the original"){
                int *test = cop.contents();
                int compare[7] = {10, 7, 15, 4, 9, 14, 3};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
        }
        WHEN("A new AVL object is instantiated using the copy assignment operator"){
            AVL<int, int, comparison_functionV, equality_functionV> copa;
            copa = *bst;
            THEN("It should contain the same tree as the original"){
                int *test = copa.contents();
                int compare[7] = {10, 7, 15, 4, 9, 14, 3};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionV(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
        }
        delete bst;
    }
}
SCENARIO("TEST CONST AVL"){
    GIVEN("A const AVL of integers is created"){
        AVL<int, int, comparison_functionV, equality_functionV> const *bst = new AVL<int, int, comparison_functionV, equality_functionV>();

        WHEN("insert with key 1 is called there is a compiler error"){
//            bst->insert(1, 1);
        }
        delete bst;
    }

}
