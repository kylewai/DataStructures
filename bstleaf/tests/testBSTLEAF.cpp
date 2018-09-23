#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BSTLEAF.h"

bool comparison_function(const int& key1, const int& key2){
    if(key1 < key2){
        return true;
    }
    return false;
}
bool equality_function(const int& key1, const int& key2){
    if(key1 == key2){
        return true;
    }
    return false;
}

using namespace cop3530;

SCENARIO("TEST SIZE 1 BSTLEAF"){
    GIVEN("A BST of integers is created"){


        BSTLEAF<int, int, comparison_function, equality_function> * bst = new BSTLEAF<int, int, comparison_function, equality_function>();

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

SCENARIO("TEST SIZE 8 BSTLEAF"){
    GIVEN("An BSTLEAF of integers is created"){
        BSTLEAF<int, int, comparison_function, equality_function> * bst = new BSTLEAF<int, int, comparison_function, equality_function>();
        WHEN("insert with key 7 and value 7 is called"){
            bst->insert(7, 7);
            THEN("The level order traversal should be: 7"){
                int *test = bst->contents();
                int compare[1] = {7};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_function(compare[i], test[i]) == true);
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
                        REQUIRE(equality_function(compare[i], test[i]) == true);
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
                            REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                    REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                THEN("The level order traversal should be: 7 3 8 2 5 4"){
                                    int *test = bst->contents();
                                    int compare[6] = {7, 3, 8, 2, 5, 4};
                                    for(size_t i = 0; i < bst->size(); i++){
                                        REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                THEN("height() should return 3"){
                                    REQUIRE(bst->height() == 3);
                                }
                                THEN("balance() should return 2"){
                                    REQUIRE(bst->balance() == 2);
                                }
                                THEN("lookup(4) should return 4"){
                                    REQUIRE(bst->lookup(4) == 4);
                                }

                                WHEN("insert with key 6 and value 6 is called"){
                                    bst->insert(6, 6);
                                    THEN("The level order traversal should be: 7 3 8 2 5 4 6"){
                                        int *test = bst->contents();
                                        int compare[7] = {7, 3, 8, 2, 5, 4, 6};
                                        for(size_t i = 0; i < bst->size(); i++){
                                            REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                    THEN("height() should return 3"){
                                        REQUIRE(bst->height() == 3);
                                    }
                                    THEN("balance() should return 2"){
                                        REQUIRE(bst->balance() == 2);
                                    }
                                    THEN("lookup(6) should return 6"){
                                        REQUIRE(bst->lookup(6) == 6);
                                    }

                                    WHEN("insert with key 10 and value 10 is called"){
                                        bst->insert(10, 10);
                                        THEN("The level order traversal should be: 7 3 8 2 5 10 4 6"){
                                            int *test = bst->contents();
                                            int compare[8] = {7, 3, 8, 2, 5, 10, 4, 6};
                                            for(size_t i = 0; i < bst->size(); i++){
                                                REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                        THEN("balance() should return 1"){
                                            REQUIRE(bst->balance() == 1);
                                        }
                                        THEN("lookup(10) should return 10"){
                                            REQUIRE(bst->lookup(10) == 10);
                                        }

                                        WHEN("remove(3) is called"){
                                            bst->remove(3);
                                            THEN("The level order traversal should be: 7 4 8 2 5 10 6"){
                                                int *test = bst->contents();
                                                int compare[7] = {7, 4, 8, 2, 5, 10, 6};
                                                for(size_t i = 0; i < bst->size(); i++){
                                                    REQUIRE(equality_function(compare[i], test[i]) == true);
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
                                            THEN("balance() should return 1"){
                                                REQUIRE(bst->balance() == 1);
                                            }
                                            THEN("lookup(3) should throw an exception"){
                                                CHECK_THROWS(bst->lookup(3));
                                            }
                                            THEN("remove(3) should throw an exception"){
                                                CHECK_THROWS(bst->remove(3));
                                            }

                                            WHEN("remove(8) is called"){
                                                bst->remove(8);
                                                THEN("The level order traversal should be: 7 4 10 2 5 6"){
                                                    int *test = bst->contents();
                                                    int compare[6] = {7, 4, 10, 2, 5, 6};
                                                    for(size_t i = 0; i < bst->size(); i++){
                                                        REQUIRE(equality_function(compare[i], test[i]) == true);
                                                    }
                                                    delete[] test;
                                                    bst->print();
                                                }

                                                THEN("size() should return 6"){
                                                    REQUIRE(bst->size() == 6);
                                                }
                                                THEN("height() should return 3"){
                                                    REQUIRE(bst->height() == 3);
                                                }
                                                THEN("balance() should return 2"){
                                                    REQUIRE(bst->balance() == 2);
                                                }
                                                THEN("lookup(8) should throw an exception"){
                                                    CHECK_THROWS(bst->lookup(8));
                                                }
                                                THEN("remove(8) should throw an exception"){
                                                    CHECK_THROWS(bst->remove(8));
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
}

SCENARIO("TEST DUPLICATE KEYS"){
    GIVEN("An BSTLEAF of integers is created"){
        BSTLEAF<int, int, comparison_function, equality_function> * bst = new BSTLEAF<int, int, comparison_function, equality_function>();

        WHEN("insert with keys 7 8 3 2 5 4 6 10 with all values 1 is called"){
            bst->insert(7, 1);
            bst->insert(8, 1);
            bst->insert(3, 1);
            bst->insert(2, 1);
            bst->insert(5, 1);
            bst->insert(4, 1);
            bst->insert(6, 1);
            bst->insert(10, 1);

            WHEN("insert with a duplicate key 8 is called with a different value 5"){
                bst->insert(8, 5);
                THEN("The level order traversal should be: 7 3 8 2 5 10 4 6"){
                    int *test = bst->contents();
                    int compare[8] = {7, 3, 8, 2, 5, 10, 4, 6};
                    for(size_t i = 0; i < bst->size(); i++){
                        REQUIRE(equality_function(compare[i], test[i]) == true);
                    }
                    delete[] test;
                    bst->print();
                }
                THEN("The value of key 8 should be 5"){
                    REQUIRE(bst->lookup(8) == 5);
                }
            }
        }
        delete bst;
    }
}

SCENARIO("TEST COPY CONSTRUCTORS"){
    GIVEN("An BSTLEAF of integers is created"){
        BSTLEAF<int, int, comparison_function, equality_function> * bst = new BSTLEAF<int, int, comparison_function, equality_function>();
        bst->insert(7, 1);
        bst->insert(8, 1);
        bst->insert(3, 1);
        bst->insert(2, 1);
        bst->insert(5, 1);
        bst->insert(4, 1);
        bst->insert(6, 1);
        bst->insert(10, 1);
        WHEN("A new BSTLEAF object is instantiated using the copy constructor"){
            BSTLEAF<int, int, comparison_function, equality_function> cop(*bst);
            THEN("It should contain the same tree as the original"){
                int *test = cop.contents();
                int compare[8] = {7, 3, 8, 2, 5, 10, 4, 6};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_function(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
        }
        WHEN("A new BSTLEAF object is instantiated using the copy assignment operator"){
            BSTLEAF<int, int, comparison_function, equality_function> copa;
            copa = *bst;
            THEN("It should contain the same tree as the original"){
                int *test = copa.contents();
                int compare[8] = {7, 3, 8, 2, 5, 10, 4, 6};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_function(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
        }
        delete bst;
    }
}

SCENARIO("TEST CONST BSTLEAF"){
    GIVEN("A const BSTLEAF of integers is created"){
        BSTLEAF<int, int, comparison_function, equality_function> const *bst = new BSTLEAF<int, int, comparison_function, equality_function>();

        WHEN("insert with key 1 is called there is a compiler error"){
//            bst->insert(1, 1);
        }
        delete bst;
    }

}

