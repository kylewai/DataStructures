#include "testCDAL.h"

int main(){

    bool e = testCDAL::test1CDAL();
    bool f = testCDAL::test0CDAL();
    bool h = testCDAL::test5CDAL();
    bool g = testCDAL::test150CDAL();
    bool i = testCDAL::testIterCDAL();
    bool j = testCDAL::testCopierCDAL();
    if(e && f && h && g && i && j){
        std::cout<< "\n\nALL CDAL TESTS PASSED!\n";
    }
}
