#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BSTRAND.h"

bool comparison_functionA(const int& key1, const int& key2){
    if(key1 < key2){
        return true;
    }
    return false;
}
bool equality_functionA(const int& key1, const int& key2){
    if(key1 == key2){
        return true;
    }
    return false;
}

using namespace cop3530;

SCENARIO("TEST SIZE 1 BSTRAND"){
    GIVEN("A BSTRAND of integers is created"){
        BSTRAND<int, int, comparison_functionA, equality_functionA> *bst = new BSTRAND<int, int, comparison_functionA, equality_functionA>();

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
SCENARIO("TEST SIZE 8 BSTRAND"){
    GIVEN("An BSTRAND of integers is created"){
        BSTRAND<int, int, comparison_functionA, equality_functionA> *bst = new BSTRAND<int, int, comparison_functionA, equality_functionA>();
        WHEN("insert with key 7 and value 7 is called"){
            bst->insert(7, 7);
            THEN("The level order traversal should be: 7"){
                int *test = bst->contents();
                int compare[1] = {7};
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionA(compare[i], test[i]) == true);
                }
                delete[] test;
                bst->print();
            }
            THEN("contains(7) should return true"){
                    REQUIRE(bst->contains(7) == true);
            }
            WHEN("insert with keys 8, 3, 2, 5, 4, 6, 10 and values equal to keys is called"){
                bst->insert(8, 8);
                bst->insert(3, 3);
                bst->insert(2, 2);
                bst->insert(5, 5);
                bst->insert(4, 4);
                bst->insert(6, 6);
                bst->insert(10, 10);

                THEN("contains(8) should return true"){
                    bst->print();
                    REQUIRE(bst->contains(8) == true);
                }
                THEN("contains(3) should return true"){
                    REQUIRE(bst->contains(3) == true);
                }
                THEN("contains(2) should return true"){
                    REQUIRE(bst->contains(2) == true);
                }
                THEN("contains(5) should return true"){
                    REQUIRE(bst->contains(5) == true);
                }
                THEN("contains(4) should return true"){
                    REQUIRE(bst->contains(4) == true);
                }
                THEN("contains(6) should return true"){
                    REQUIRE(bst->contains(6) == true);
                }
                THEN("contains(10) should return true"){
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
                THEN("lookup(8) should return 8"){
                    REQUIRE(bst->lookup(8) == 8);
                }
                THEN("lookup(3) should return true"){
                    REQUIRE(bst->lookup(3) == 3);
                }
                THEN("lookup(2) should return true"){
                    REQUIRE(bst->lookup(2) == 2);
                }
                THEN("lookup(5) should return true"){
                    REQUIRE(bst->lookup(5) == 5);
                }
                THEN("lookup(4) should return true"){
                    REQUIRE(bst->lookup(4) == 4);
                }
                THEN("lookup(6) should return true"){
                    REQUIRE(bst->lookup(6) == 6);
                }
                THEN("lookup(10) should return true"){
                    REQUIRE(bst->lookup(10) == 10);
                }

                WHEN("remove(3) is called"){
                    bst->remove(3);
                    bst->print();
                    THEN("lookup(3) should throw an error"){
                        CHECK_THROWS(bst->lookup(3));
                    }
                    WHEN("remove(5) is called"){
                        bst->remove(5);
                        bst->print();
                        THEN("lookup(5) should throw an error"){
                            CHECK_THROWS(bst->lookup(5));
                        }
                    }
                }
            }
        }
        delete bst;
    }
}
SCENARIO("TEST DUPLICATE KEYS"){
    GIVEN("An BSTRAND of integers is created"){
        BSTRAND<int, int, comparison_functionA, equality_functionA> * bst = new BSTRAND<int, int, comparison_functionA, equality_functionA>();

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
                THEN("The value of key 7 should be 5"){
                    REQUIRE(bst->lookup(7) == 5);
                }
            }
        }
        delete bst;
    }
}

SCENARIO("TEST COPY CONSTRUCTORS"){
    GIVEN("An BSTRAND of integers is created"){
        BSTRAND<int, int, comparison_functionA, equality_functionA> * bst = new BSTRAND<int, int, comparison_functionA, equality_functionA>();
        bst->insert(10, 1);
        bst->insert(7, 1);
        bst->insert(15, 1);
        bst->insert(4, 1);
        bst->insert(9, 1);
        bst->insert(14, 1);
        bst->insert(3, 1);
        WHEN("A new BSTRAND object is instantiated using the copy constructor"){
            BSTRAND<int, int, comparison_functionA, equality_functionA> cop(*bst);
            THEN("It should contain the same tree as the original"){
                int *test = cop.contents();
                int *test2 = bst->contents();
                for(size_t i = 0; i < cop.size(); i++){
                    REQUIRE(equality_functionA(test2[i], test[i]) == true);
                }
                delete[] test;
                delete[] test2;
                bst->print();
            }
        }
        WHEN("A new BSTRAND object is instantiated using the copy assignment operator"){
            BSTRAND<int, int, comparison_functionA, equality_functionA> copa;
            copa = *bst;
            THEN("It should contain the same tree as the original"){
                int *test = copa.contents();
                int *test2 = bst->contents();
                for(size_t i = 0; i < bst->size(); i++){
                    REQUIRE(equality_functionA(test2[i], test[i]) == true);
                }
                delete[] test;
                delete[] test2;
                bst->print();
            }
        }
        delete bst;
    }
}


