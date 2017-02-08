/* OOP244.132 Assignment 4 Test Main
*  Bookstore Order Processor
*
*  Author: Chris Szalwinski
*  Modified by: Mark Fernandes
*  Nov 17 2011
*  a4test.cpp
*
*  Version 1.00
*  Originates from Jan 15 2011 (CS)
*  Changes made:
*   - added checks for valid and registered ISBNs that end in 'X'
*   - added check for invalid ISBN XXXXXXXXX0
*   - added check for invalid ISBN 081613752X (valid value should be 08161351X)
*   - added checks for orders that end in X
*   - added checks for specialorders that end in X
*   - error messages prominently stand out  (modified printf error message)
*
*  Assumes that the declaration of the ISBNPrefix class is in ISBNPrefix.h
*  Assumes that the declaration of the SpecialOrder class is in SpecialOrder.h
*  Assumes that the declaration of the Order class is included in SpecialOrder.h
*  Assumes that the declaration of the ISBN class is included in SpecialOrder.h
*
*  Set   DEBUG to 1 for verbose debugging output
*  Reset DEBUG to 0 for submission version
*/
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
using namespace std;

#include "ISBNPrefix.h"

#define DEBUG 1                    // set to 1 for verbose output
#define PREFIX "prefixRanges.txt"  // file of ISBN Prefix Ranges

#define ORDER         1
#define SPECIAL_ORDER 2

// set the test level here
#define TEST_LEVEL SPECIAL_ORDER

#if TEST_LEVEL == SPECIAL_ORDER
#include "SpecialOrder.h"
#endif

int  pTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested);
int  iTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested);
int  rTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested);
int  oTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested);
int  sTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested);
void testPassed(const char* message, int i, int* totalPassed, int* total);
void testFailed(const char* message, int i, int* totalFailed, int* total);

int main() {
    ISBNPrefix list(PREFIX);
    int totalPassed = 0, totalTested = 0, testNumber = 0;

    // ISBNPrefix Tests
    if (DEBUG)
        printf("Prefix Tests\n============\n");
    if(pTests(list, testNumber, &totalPassed, &totalTested))
        if (DEBUG)
            printf("\nPrefix Tests totalPassed!\n\n");
        else
            printf("Prefix Tests totalPassed!\n");
    else {
        printf("\n");
        if (DEBUG)
            printf("Prefix Tests had errors!\n\n");
        else
            printf("Prefix Tests had errors!\n");
    }

    // ISBN Tests
    if (DEBUG)
        printf("ISBN Tests\n==========\n");
    if(iTests(list, testNumber, &totalPassed, &totalTested))
        if (DEBUG)
            printf("\nISBN Tests totalPassed!\n\n");
        else
            printf("ISBN Tests totalPassed!\n");
    else {
        printf("\n");
        printf("\nISBN Tests had errors!\n");
    }

    // ISBN Prefix Tests
    if (DEBUG)
        printf("ISBN/Prefix Tests\n=================\n");
    if(rTests(list, testNumber, &totalPassed, &totalTested))
        if (DEBUG)
            printf("\nISBN/Prefix Tests totalPassed!\n\n");
        else
            printf("ISBN/Prefix Tests totalPassed!\n");
    else {
        printf("\n");
        printf("\nISBN/Prefix Tests had errors!\n");
    }

    // Order Tests
    if (DEBUG)
        printf("Order Tests\n===========\n");
    if(oTests(list, testNumber, &totalPassed, &totalTested))
        if (DEBUG)
            printf("\nOrder Tests totalPassed!\n\n");
        else
            printf("Order Tests totalPassed!\n");
    else {
        printf("\n");
        printf("\nOrder Tests had errors!\n");
    }

    // Special Order Tests
    #if TEST_LEVEL == SPECIAL_ORDER
    if (DEBUG)
        printf("Special Order Tests\n===================\n");
    if(sTests(list, testNumber, &totalPassed, &totalTested))
        if (DEBUG)
            printf("\nSpecial Order Tests totalPassed!\n\n");
        else
            printf("Special Order Tests totalPassed!\n");
    else {
        printf("\n");
        printf("\nSpecial Order Tests had errors!\n");
    }
    #endif

    // Conclusion
    printf("\nYour Bookstore modules have totalPassed %d of %d tests\n",
        totalPassed, totalTested);
    if (totalPassed == totalTested)
        printf("\nCongratulations!!!   "
        "Your Bookstore modules are ready for submission\n\n");
    else
        printf("Keep working on your code - good luck!\n");

    return 0;
}

/* pTests performs tests on the ISBNPrefix class and return false for
*  invalid results
*  *totalPassed - total number of tests totalPassed
*  *totalTested - total number of tests attempted
*/
int pTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested) {
    int totalFailed = true;

    // area identifiers
    //
    if(list.isRegistered(-1)) {
        testFailed("isRegistered(-1) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(-1)", ++testNumber, totalPassed, totalTested);

    if(list.isRegistered(99955)) {
        testFailed("isRegistered(99955) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(99955)", ++testNumber, totalPassed, totalTested);

    if(!list.isRegistered(0)) {
        testFailed("isRegistered(0) did not return true", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(0)", ++testNumber, totalPassed, totalTested);

    // publisher identifiers
    //
    if(list.isRegistered(-1, "0")) {
        testFailed("isRegistered(-1, 0) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(-1, 0)", ++testNumber, totalPassed, totalTested);

    if(list.isRegistered(99955, "0")) {
        testFailed("isRegistered(99955, 0) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(99955, 0)", ++testNumber, totalPassed, totalTested);

    if(!list.isRegistered(0, "10")) {
        testFailed("isRegistered(0, 10) did not return true", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(0, 10)", ++testNumber, totalPassed, totalTested);

    if(list.isRegistered(99955, "0")) {
        testFailed("isRegistered(99955, 0) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(99955, 0)", ++testNumber, totalPassed,
            totalTested);

    if(list.isRegistered(0, "95000000")) {
        testFailed("isRegistered(0, 95000000) did not return false", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("isRegistered(0, 95000000)", ++testNumber, totalPassed,
            totalTested);

    // minimum number of digits
    //
    if(list.minNoDigits(-1) != 0) {
        testFailed("minNoDigits(-1) did not return 0", ++testNumber, &totalFailed,
            totalTested);
    } else
        testPassed("minNoDigits(-1)", ++testNumber, totalPassed, totalTested);

    if(list.minNoDigits(0) != 2) {
        testFailed("minNoDigits(0) did not return 2", ++testNumber, &totalFailed,
         totalTested);
    } else
        testPassed("minNoDigits(0)", ++testNumber, totalPassed, totalTested);

    if(list.minNoDigits(92) != 1) {
        testFailed("minNoDigits(92) did not return 1", ++testNumber, &totalFailed,
            totalTested);
    } else
        testPassed("minNoDigits(92)", ++testNumber, totalPassed, totalTested);

    if(list.minNoDigits(99955) != 0) {
        testFailed("minNoDigits(99955) did not return 0", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("minNoDigits(99955)", ++testNumber, totalPassed, totalTested);

    return totalFailed;
}

/* iTests performs tests on the ISBN class and returns false for invalid
*  results
*  *totalPassed - total number of tests totalPassed
*  *totalTested - total number of tests attempted
*/
int iTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested) {
    int  totalFailed = true;
    ISBN isbn, safe;
    char stra[14], strb[14];

    // ISBN()
    //
    isbn = ISBN();
    if(isbn.empty() == 0) {
        testFailed("empty() did not return true for ISBN()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN() and empty()", ++testNumber, totalPassed, totalTested);

    if(isbn.isRegistered() != 0) {
        testFailed("isRegistered() did not return false for ISBN()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN() and isRegistered()", ++testNumber, totalPassed, totalTested);

    // ISBN("9070002043", list)
    //
    isbn = ISBN("9070002043", list);
    if(isbn.empty() != 0) {
        testFailed("empty() did not return false for 9070002043", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN(\"9070002043\", ) and empty()", ++testNumber, totalPassed,
            totalTested);

    if(isbn.isRegistered() == 0) {
        testFailed("isRegistered() did not return true for 9070002043", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN(\"9070002043\", ) and isRegistered()", ++testNumber,
            totalPassed, totalTested);

    // ISBN("9070002046", list)
    //
    isbn = ISBN("9070002046", list);
    if(isbn.empty() == 0) {
        testFailed("empty() did not return true for 9070002046", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002046) and empty()", ++testNumber, totalPassed,
            totalTested);

    if(isbn.isRegistered() != 0) {
        testFailed("isRegistered() did not return false for 9070002046",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(\"9070002046\", ) and isRegistered()", ++testNumber,
            totalPassed, totalTested);

    safe.toStr(stra);
    isbn.toStr(strb);
    if (strcmp(stra, strb)) {
        testFailed("toStr does not return same string for ISBN() and "
            "ISBN(\"9070002046\", )", ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("toStr on ISBN() and IBSN(\"9070002046\", )", ++testNumber,
            totalPassed, totalTested);

    // toStr
    //
    isbn = ISBN("9070002043", list);
    isbn.toStr(stra);
    if(strcmp(stra, "9070002043") != 0) {
        testFailed("toStr did not return 9070002043", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002043) and toStr(char*)", ++testNumber,
            totalPassed, totalTested);

    isbn = ISBN("9070002046", list);
    isbn.toStr(strb);
    if(!strcmp(strb, "9070002046")) {
        testFailed("toStr didn\'t return a string different from 9070002046",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(...) and toStr(char*)", ++testNumber, totalPassed,
            totalTested);

    isbn = ISBN("9070002043", list);
    isbn.toStr(stra);
    if(strcmp(stra, "9070002043")) {
        testFailed("toStr did not return 9070002043", ++testNumber, &totalFailed,
            totalTested);
    } else
        testPassed("ISBN(9070002043) and toStr(char*)",
            ++testNumber, totalPassed, totalTested);

    // toStrWithStyle
    //
    isbn = ISBN("9070002043", list);
    isbn.toStrWithStyle(stra);
    if(strcmp(stra, "90-70002-04-3")) {
        testFailed("toStrWithStyle did not return 90-70002-04-3", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002043) and toStrWithStyle(char*)",
            ++testNumber, totalPassed, totalTested);

    isbn = ISBN("9995500000", list);
    isbn.toStrWithStyle(stra);
    if(strcmp(stra, "9995500000")) {
        testFailed("toStrWithStyle did not return 9995500000",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(9995500000) and toStrWithStyle(char*)",
            ++testNumber, totalPassed, totalTested);

    // == operator
    //
    isbn = ISBN("9070002046", list);
    if(!(isbn == ISBN("9070002046", list))) {
        testFailed("ISBN(9070002046) == ISBN(9070002046) did not return true",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002046) == ISBN(9070002046) returned true",
            ++testNumber, totalPassed, totalTested);

    isbn = ISBN("9070002043", list);
    if(!(isbn == ISBN("9070002043", list))) {
        testFailed("ISBN(9070002043) == ISBN(9070002043) did not return true",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002043) == ISBN(9070002043) returned true",
            ++testNumber, totalPassed, totalTested);

    if(isbn == ISBN("9070002046", list)) {
        testFailed("ISBN(9070002043) == ISBN(9070002046) did not return false",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("ISBN(9070002043) == ISBN(9070002046) returned false",
            ++testNumber, totalPassed, totalTested);

    return totalFailed;
}

/* oTests performs tests on the Order class and returns false for any
*  invalid results
*  *totalPassed - total number of tests totalPassed
*  *totalTested - total number of tests attempted
*/
int oTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested) {
    Order order;
    int totalFailed = true;

    // Order()
    //
    if(order.has(ISBN()) == 0) {
        testFailed("Order(), has(ISBN()) did not return true", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("Order(), has(ISBN()) returned true", ++testNumber, totalPassed,
            totalTested);

    if(order.outstanding() != 0) {
        testFailed("Order(), outstanding() did not return 0", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("Order(), outstanding() returned 0", ++testNumber, totalPassed,
            totalTested);

    // Order(ISBN(9070002043, ))
    //
    order = Order(ISBN("9070002043", list));
    if(order.has(ISBN("9070002043", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002043\", ), 0, 0), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), outstanding()", ++testNumber, totalPassed,
            totalTested);

    order = Order(ISBN("9070002043", list));
    order.add(5);
    if(order.has(ISBN("9070002043", list)) == 0 || order.outstanding() != 5) {
        testFailed("has(ISBN(\"9070002043\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), outstanding()", ++testNumber, totalPassed,
            totalTested);

    // Order(ISBN(9070002046, ))
    //
    order = Order(ISBN("9070002046", list));
    if(order.has(ISBN("9070002046", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002046\", )), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002046\"), outstanding()", ++testNumber, totalPassed,
            totalTested);

    order = Order(ISBN("9070002046", list));
    order.add(5);
    if(order.has(ISBN("9070002046", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002046\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002046\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

   // Order(ISBN(XXXXXXXXX0, ))
   //
    order = Order(ISBN("XXXXXXXXX0", list));
    if(order.has(ISBN("XXXXXXXXX0", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"XXXXXXXXX0\", )), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"XXXXXXXXX0\"), outstanding()", ++testNumber, totalPassed,
            totalTested);

    order = Order(ISBN("XXXXXXXXX0", list));
    order.add(5);
    if(order.has(ISBN("XXXXXXXXX0", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"XXXXXXXXX0\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"XXXXXXXXX0\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

   // Order(ISBN(014010867X, ))
   //
    order = Order(ISBN("014010867X", list));
    if(order.has(ISBN("014010867X", list)) == 0 || order.outstanding() != 0) {
        testFailed("has(ISBN(\"014010867X\", )), outstanding()",
         ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"014010867X\"), outstanding()", ++testNumber,
            totalPassed, totalTested);

    order = Order(ISBN("014010867X", list));
    order.add(5);
    if(order.has(ISBN("014010867X", list)) == 0 || order.outstanding() != 5) {
        testFailed("has(ISBN(\"014010867X\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"014010867X\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

    return totalFailed;
}

/* rTests performs tests on the ISBN and ISBNPrefix classes and
*  returns false for invalid results
*  *totalPassed - total number of tests totalPassed
*  *totalTested - total number of tests attempted
*/
int rTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested) {
    ISBN isbn;
    int totalFailed = true;

    isbn = ISBN("9070002043", list);
    if(!isbn.isRegistered()) {
        testFailed("isRegistered() did not return true for 9070002043)",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("isRegistered() returned true for 9070002043", ++testNumber,
            totalPassed, totalTested);
    isbn = ISBN("9995500000", list);

    if(isbn.isRegistered()) {
        testFailed("isRegistered() did not return false for 9995500000)",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("isRegistered() returned true for 9995500000", ++testNumber,
            totalPassed, totalTested);

    char message[50], value[][11] = {
    "0000000000","0190000007","0200000004","0699000009","0700000003",
    "0850000009","0899990002","0900000007","0949999008","0950000000",
    "0999999907","1000000001","1090000006","1100000003","1399000004",
    "1400000009","1549900005","1550000004","1869790006","1869800001",
    "1998999009","1999000005","1999999908","2000000002","2190000009",
    "2200000006","2349000001","2350000001","2399990005","2495000002",
    "2699000000","2700000005","2839900009","2840000008","2899990004",
    "2900000009","2950000002","2999999909","3000000003","3020000009",
    "3030000001","3033000002","3034000006","3036900004","3037000007",
    "3039990004","3040000004","3200000007","3699000001","3700000006",
    "3849900002","3850000001","3899990005","3949999000","3950000003",
    "4000000004","4190000000","4200000008","4699000002","4700000007",
    "4849900003","4850000002","4899990006","4900000000","4949999001",
    "4950000004","4999999900","5000000005","5190000001","5200000009",
    "5699000003","5700000008","5849900004","5850000003","5899990007",
    "5900000001","5919999004","5920000007","5929900000","5949990005",
    "5950000005","5979900004","5980000003","5989990006","5990000006",
    "5999999901","7000000007","7090000001","7100000009","7499000001",
    "7500000006","7799900008","7800000001","7899990009","7900000003",
    "7999999008","8000000008","8019000003","8020000003","8069900008",
    "8070000007","8084990004","8085000008","8090000002","8099999908",
    "8119000005","8120000005","8170000009","8184990006","8189999001",
    "8190000004","8200000001","8219000007","8220000007","8269900001",
    "8270000000","8289990006","8290000006","8298999002","8299000009",
    "8299999901","8300000003","8319000009","8320000009","8369900003",
    "8370000002","8385000003","8389999005","8390000008","8399999903",
    "8400000005","8419000000","8420000000","8469900005","8470000004",
    "8484990001","8485000005","8489999007","8491990003","8492000007",
    "8492399902","8492400005","8492999004","8493000000","8494999907",
    "8495000008","8496999009","8497000005","8499990002","8500000007",
    "8519000002","8520000002","8569900007","8570000006","8584990003",
    "8585000007","8589999009","8590000001","8598000000","8599999001",
    "8600000009","8629000007","8630000007","8669900009","8670000008",
    "8679990000","8680000000","8689999000","8690000003","8699999909",
    "8700000000","8729000009","8740000001","8764900002","8779990002",
    "8785000000","8794999007","8797000000","8799999900","8800000002",
    "8819000008","8820000008","8860000009","8884990009","8885000002",
    "8889999004","8890000007","8899999902","8900000004","8924000004",
    "8925000008","8954900003","8955000006","8984990000","8985000004",
    "8994999000","8995000007","8999999904","9000000009","9019000004",
    "9020000004","9049900003","9050000002","9069990008","9070000008",
    "9079999008","9080000000","9084999908","9085000009","9089990003",
    "9090000003","9090999906","9094000008","9094999900","9100000000",
    "9110000003","9120000006","9149000004","9150000004","9164900002",
    "9179990002","9185000000","9194999007","9197000000","9199999900",
    "9200000002","9250000006","9260000009","9279000004","9280000004",
    "9289900008","9290000007","9294990001","9295000005","9298999003",
    "9299999902","9500000008","9504900003","9505000006","9508990007",
    "9509000000","9509899003","9509900001","9509999903","9510000000",
    "9511000004","9512000008","9515400007","9515500001","9518890005",
    "9518900000","9519499008","9519500006","9519999906","9520000003",
    "9521900008","9522000000","9524990008","9525000001","9525999009",
    "9526000005","9526500008","9526600002","9526699009","9526700007",
    "9526999908","9527000009","9527999006","9528900003","9529400004",
    "9529500009","9529899009","9529900007","9529999909","9530000006",
    "9530000006","9531400008","9531500002","9535990004","9536000008",
    "9539499003","9539500001","9539999901","9540000009","9542900007",
    "9547990004","9548000008","9548999005","9549000001","9549299902",
    "9549300005","9549999009","9550000001","9551000005","9552000009",
    "9555400008","9555500002","9557990007","9558000000","9559499009",
    "9559500007","9559999907","9560000004","9561900009","9562000001",
    "9566990006","9569999004","9570000007","9570200006","9570300000",
    "9570499001","9571900001","9572000004","9572099000","9572100009",
    "9572700006","9572800000","9573100002","9574300005","9578200005",
    "9579699003","9579700001","9579999902","9585900009","9586000001",
    "9587990005","9588000009","9589499007","9589500005","9589999905",
    "9590000002","9591900007","9596990004","9597000008","9598499006",
    "9601900004","9602000007","9606590003","9606600009","9606899004",
    "9606900002","9606990001","9608500001","9609999905","9610000002",
    "9611900007","9615990000","9616000004","9618999009","9619000005",
    "9619499905","9620000005","9622000002","9626990007","9627000000",
    "9628499009","9628500007","9628699903","9628700006","9628999001",
    "9629000008","9629990008","9630000008","9631900002","9632000005",
    "9637000003","9638499001","9639000000","9639999008","9640000000",
    "9642900009","9643000001","9645490006","9645500001","9648999007",
    "9649000003","9649999906","9650000003","9651900008","9652000000",
    "9655990001","9657000009","9657999006","9659000006","9659999909",
    "9660000006","9662900004","9663000007","9666990008","9667000001",
    "9668999002","9669000009","9669999901","9670000009","9675000007",
    "9676000000","9678900009","9679000001","9679890007","9679900002",
    "9679989003","9679990001","9679999904","9680100006","9683900003",
    "9684000006","9684990006","9687999004","9688000000","9688990000",
    "9690000004","9691000008","9692000001","9693900006","9694000009",
    "9698000003","9699999004","9700100006","9705900000","9706000003",
    "9708990000","9709000004","9709099000","9709100009","9709699903",
    "9709700006","9709999001","9710000004","9710190008","9710200003",
    "9710200003","9710300008","9710599003","9710600001","9710900005",
    "9711000008","9715000002","9718490000","9718500006","9719099003",
    "9719100001","9720000007","9721000000","9722000004","9725400003",
    "9725500008","9727990002","9728000006","9729499004","9729500002",
    "9729999902","9731000003","9732000007","9735400006","9735500000",
    "9737690001","9737700007","9738499003","9738500001","9738999901",
    "9739000002","9739499007","9739500005","9739999905","9740000002",
    "9741900007","9746990004","9747000008","9748499006","9748500004",
    "9748999904","9749000005","9749499905","9749500008","9749999002",
    "9750000005","9752400000","9752500005","9755990003","9756000007",
    "9759199009","9759200007","9759899906","9760000008","9763000009",
    "9764000002","9765900007","9767990003","9768000007","9769499005",
    "9769500003","9769999903","9770000000","9771900005","9772000008",
    "9774990005","9775000009","9777000006","9779990003","9780000003",
    "9781990007","9782000000","9782999008","9783000004","9787999901",
    "9788000002","9789000006","9789990006","9790000006","9790000006",
    "9792000003","9792900004","9793000007","9793999004","9794000000",
    "9797990001","9798000005","9799499003","9799500001","9799999901",
    "9800000003","9801900008","9802000000","9805990001","9806000005",
    "9809999003","9810000006","9811900000","9812000003","9812990003",
    "9813000007","9819999006","9820000009","9821000002","9826990000",
    "9827000004","9828900009","9829000001","9829999009","9830000001",
    "9830100006","9830200000","9831990005","9832000009","9834000006",
    "9834999909","9837900008","9838000000","9838990000","9839000004",
    "9839899007","9839900005","9839999907","9840000004","9843900006",
    "9844000009","9848000003","9848999000","9849000007","9850000007",
    "9853900009","9854000001","9855990005","9856000009","9858999003",
    "9859999902","9861100008","9861200002","9865600005","9867999002",
    "9868000009","9869999905","9870000002","9870900003","9871000006",
    "9871999003","9872999902","9873000003","9874900008","9875000000",
    "9878990001","9879000005","9879500008","9879999908","9880000005",
    "9882000002","9887990000","9888000004","9889699001","9889999900",
    "9890000008","9891000001","9892000005","9895400004","9895500009",
    "9897990003","9898000007","9899499005","9899500003","9899999903",
    "9946000008","9946100002","9946200007","9946390000","9946400006",
    "9946899000","9946900009","9946999900","9947000001","9947100006",
    "9947200000","9947790002","9947800008","9947999009","9948000005",
    "9948390008","9948400003","9948849000","9948850009","9948999908",
    "9949000009","9949000009","9949100003","9949390001","9949400007",
    "9949899001","9949999901","9950000009","9950000009","9951000002",
    "9951390005","9951400000","9951849008","9951850006","9951999905",
    "9952000006","9952100000","9952200005","9952390009","9952400004",
    "9952799004","9952800002","9952999909","9953100004","9953390002",
    "9953400008","9953599009","9953600007","9953890005","9953900000",
    "9953999902","9954000003","9954100008","9954200002","9954390006",
    "9954400001","9954799001","9954999906","9955000007","9955400005",
    "9955929006","9955930004","9956000000","9956000000","9956100005",
    "9956390003","9956400009","9956899003","9956900001","9956999903",
    "9957000004","9957390007","9957400002","9957850008","9957999907",
    "9958000008","9958000008","9958100002","9958490005","9958500000",
    "9958899000","9958900009","9958999900","9959000001","9959100006",
    "9959200000","9959790002","9959800008","9959949001","9959999904",
    "9960000001","9960590003","9960600009","9960899004","9960900002",
    "9960999904","9961000005","9961200004","9961300009","9961690001",
    "9961700007","9961949005","9961950003","9961999908","9962000009",
    "9962540003","9962550009","9962559901","9962560004","9962590000",
    "9962600006","9962849004","9962850002","9962999901","9963000002",
    "9963200001","9963300006","9963540007","9963550002","9963749003",
    "9963750001","9963999905","9964000006","9964600003","9964700008",
    "9964940009","9964950004","9964999003","9965390002","9965400008",
    "9965899002","9965900000","9965999902","9966000003","9966959009",
    "9966960007","9966999906","9967000007","9967400005","9967900008",
    "9968000000","9968490008","9968500003","9968939005","9968940003",
    "9968999903","9970000004","9970390007","9970400002","9970899007",
    "9970900005","9970999907","9971000008","9971500000","9971600005",
    "9971890003","9971900009","9971990008","9971999900","9972000001",
    "9972090000","9972100006","9972100006","9972200000","9972590003",
    "9972600009","9972899004","9972900002","9972999904","9973000005",
    "9973000005","9973690001","9973700007","9973969006","9973970004",
    "9973999908","9974000009","9974200008","9974300002","9974540003",
    "9974550009","9974750008","9974949904","9974950007","9974990009",
    "9975000002","9975400000","9975500005","9975890008","9975900003",
    "9975949002","9975950000","9975999905","9976000006","9976500009",
    "9976600003","9976890001","9976900007","9976989008","9976999003",
    "9976999909","9977890005","9977900000","9977989001","9977999902",
    "9978000003","9978290001","9978300007","9978399003","9978400001",
    "9978940006","9978950001","9978989005","9978990003","9978999906",
    "9979000007","9979400005","9979750006","9979760001","9979900008",
    "9980000007","9980300000","9980400005","9980890002","9980900008",
    "9980989009","9980990007","9981000000","9981100005","9981160008",
    "9981199907","9981790001","9981800007","9981949000","9981950009",
    "9981999903","9982000004","9982790005","9982800000","9982889001",
    "9982990004","9982999907","9983800004","9983940000","9983950006",
    "9983990008","9983999900","9984000001","9984490009","9984500004",
    "9984899004","9984900002","9984999904","9985000005","9985400003",
    "9985500008","9985790006","9985800001","9985899008","9985900006",
    "9985999908","9986000009","9986390001","9986400007","9986899001",
    "9986939909","9986940001","9986970008","9986990009","9987000002",
    "9987390005","9987400000","9987879004","9987880002","9987999905",
    "9988000006","9988200005","9988540000","9988550006","9988749007",
    "9988750005","9988999909","9989100004","9989199000","9989200009",
    "9989299900","9989300003","9989590001","9989600007","9989950008",
    "9989999902","9990100004","9990149003","9990150001","9990179905",
    "9990180008","9990199000","9990300003","9990310009","9990320004",
    "9990389004","9990390002","9990399905","9990400008","9990450005",
    "9990460000","9990489009","9990490007","9990500002","9990530009",
    "9990540004","9990579008","9990580006","9990599904","9990600007",
    "9990620008","9990630003","9990659001","9990699909","9990800006",
    "9990800006","9990810001","9990889007","9990890005","9990899908",
    "9990900000","9990930007","9990940002","9990994005","9990995001",
    "9990999902","9991000003","9991020004","9991089004","9991090002",
    "9991099905","9991100008","9991159002","9991160000","9991200002",
    "9991240004","9991259902","9991260005","9991289003","9991290001",
    "9991299904","9991300007","9991320008","9991330003","9991335005",
    "9991360409","9991400001","9991440003","9991450009","9991489002",
    "9991490000","9991494901","9991500006","9991540008","9991550003",
    "9991579001","9991599908","9991600000","9991620001","9991630007",
    "9991669000","9991670009","9991699902","9991700005","9991720006",
    "9991730001","9991789006","9991790004","9991799907","9991830006",
    "9991840001","9991889000","9991890009","9991899901","9991900004",
    "9991920005","9991940006","9991969004","9991990003","9991999906",
    "9992000007","9992040009","9992050004","9992089008","9992090006",
    "9992099909","9992100001","9992110007","9992120002","9992169001",
    "9992179902","9992180005","9992180005","9992190000","9992199008",
    "9992200006","9992230002","9992240008","9992269006","9992270004",
    "9992299908","9992300000","9992310006","9992320001","9992379006",
    "9992380004","9992399902","9992400005","9992420006","9992430001",
    "9992479000","9992480009","9992490004","9992530006","9992540001",
    "9992579005","9992580003","9992599901","9992600004","9992600004",
    "9992659009","9992660007","9992699906","9992700009","9992730005",
    "9992759003","9992760001","9992799900","9992800003","9992800003",
    "9992810009","9992879009","9992880007","9992899905","9992900008",
    "9992900008","9993000000","9993040002","9993050008","9993079006",
    "9993080004","9993099902","9993100005","9993140007","9993150002",
    "9993179000","9993180009","9993199907","9993210005","9993259004",
    "9993260002","9993269905","9993270008","9993270008","9993280003",
    "9993299006","9993300004","9993320005","9993330000","9993359009",
    "9993360007","9993399906","9993400009","9993410004","9993479004",
    "9993480002","9993499900","9993500003","9993520004","9993559008",
    "9993560006","9993579904","9993580007","9993580007","9993590002",
    "9993600008","9993600008","9993610003","9993659002","9993660000",
    "9993700002","9993710008","9993720003","9993759007","9993760005",
    "9993799904","9993800007","9993820008","9993830003","9993859001",
    "9993899909","9993900001","9993950009","9993960004","9993989002",
    "9993990000","9993999903","9994000004","9994000004","9994069004",
    "9994070002","9994099906","9994100009","9994130005","9994190008",
    "9994199900","9994300008","9994320009","9994330004","9994359002",
    "9994360000","9994400002","9994440004","9994479008","9994480006",
    "9994499904","014010867X","XXXXXXXXX0","061428726X","060611677X",
    "081613752X" };
    int total_isbn = sizeof(value)/sizeof(value[0]);
    for (int i = 0; i < total_isbn; i++) {

      isbn = ISBN(value[i], list);

      // ISBN: XXXXXXXXX0 and ISBN: 081613752X are invalid
      if (strcmp("XXXXXXXXX0", value[i]) == 0 ||
          strcmp("081613752X", value[i]) == 0) {
            if (isValid(value[i]) == 0 ){
              sprintf(message, "  isValid(...) returned false for %s", value[i]);
              testPassed(message, ++testNumber, totalPassed, totalTested);
            } else {
              sprintf(message, "  isValid(...) returned true for %s", value[i]);
              testFailed(message, ++testNumber, &totalFailed, totalTested);
            }
      // All other ISBN's are valid and registered
      } else if(!isbn.isRegistered()) {
            sprintf(message, "isRegistered() did not return true for %s", value[i]);
            testFailed(message, ++testNumber, &totalFailed, totalTested);
        } else if (i%100 == 0) {
            sprintf(message, "isRegistered() returned true for %s", value[i]);
            testPassed(message, ++testNumber, totalPassed, totalTested);
        } else {
            testPassed("", ++testNumber, totalPassed, totalTested);
        }
    }
    return totalFailed;
}

#if TEST_LEVEL == SPECIAL_ORDER
/* sTests performs tests on the Order class and returns false for any
*  invalid results
*  *totalPassed - total number of tests totalPassed
*  *totalTested - total number of tests attempted
*/
int sTests(ISBNPrefix& list, int& testNumber, int* totalPassed, int* totalTested) {
    int totalFailed = true;
    SpecialOrder order0, specialOrder;
    SpecialOrder order1(ISBN("9070002043", list), "note");
    SpecialOrder order2(ISBN("9070002043", list), "note");
    order2.Order::add(5);
    //SpecialOrder order3(ISBN("9070002043", list), 20, 25, "note");
    //SpecialOrder order4(ISBN("9070002043", list), -1, 0, "note");
    SpecialOrder order5(ISBN("9070002046", list), "note");
    SpecialOrder order6(ISBN("9070002046", list), "note");
    order6.Order::add(5);
    SpecialOrder order7(ISBN("XXXXXXXXX0", list), "note");
    order7.Order::add(5);
    SpecialOrder order8(ISBN("014010867X", list), "note");
    order8.Order::add(5);


    // SpecialOrder()
    //
    if(order0.has(ISBN()) == 0) {
        testFailed("SpecialOrder(), has(ISBN()) did not return true",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("SpecialOrder(), has(ISBN()) returned true", ++testNumber,
            totalPassed, totalTested);

    if(order0.outstanding() != 0) {
        testFailed("SpecialOrder(), outstanding() did not return 0", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("SpecialOrder(), outstanding() returned 0", ++testNumber, totalPassed,
            totalTested);

    // SpecialOrder(ISBN(9070002043, ), "note")
    //
    if(order1.has(ISBN("9070002043", list)) == 0 || order1.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002043\", )), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), outstanding()", ++testNumber, totalPassed,
            totalTested);

    if(order2.has(ISBN("9070002043", list)) == 0 || order2.outstanding() != 5) {
        testFailed("has(ISBN(\"9070002043\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

    /*if(order3.has(ISBN("9070002043", list)) != 0 || order3.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002043\", ), 20, 25), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), outstanding()", ++testNumber,
            totalPassed, totalTested);

    if(order4.has(ISBN("9070002043", list)) != 0 || order4.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002043\", ), -1, 0), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002043\"), outstanding()", ++testNumber, totalPassed,
            totalTested);
    */

    // SpecialOrder(ISBN(9070002046, ), "note")
    //
    if(order5.has(ISBN("9070002046", list)) == 0 || order5.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002046\", )), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002046\"), outstanding()", ++testNumber,
            totalPassed, totalTested);

    if(order6.has(ISBN("9070002046", list)) == 0 || order6.outstanding() != 0) {
        testFailed("has(ISBN(\"9070002046\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"9070002046\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

    if(!order7.has(ISBN())) {
        testFailed("SpecialOrder(), has(ISBN()) did not return true",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("Order(), has(ISBN()) returned true", ++testNumber,
            totalPassed, totalTested);

    if (order7.has(ISBN("XXXXXXXXX0", list)) == 0 || order7.outstanding() != 0) {
        testFailed("has(ISBN(\"XXXXXXXXX0\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"XXXXXXXXX0\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

    if (order8.has(ISBN("014010867X", list)) == 0 || order8.outstanding() != 5) {
        testFailed("has(ISBN(\"014010867X\", )), add(5), outstanding()",
            ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("has(\"014010867X\"), add(5), outstanding()", ++testNumber,
            totalPassed, totalTested);

    // assignment operator
    //
    if (DEBUG)
        printf("\nSpecial Order Assignment Operator & Copy Constructor Tests\n"
               "===========================================================\n");
    order0 = order1;
    if(!(order0.has(ISBN("9070002043", list)) && order0.outstanding() == 0)) {
        testFailed("A.O. - has(\"9070002043\"), outstanding()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("A.O. - has(\"9070002043\")), outstanding()", ++testNumber,
            totalPassed, totalTested);

    order8 = order7;
    if(!(order8.has(ISBN("XXXXXXXXX0", list)) && order8.outstanding() == 0)) {
        testFailed("A.O. - has(\"XXXXXXXXX0\"), outstanding()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("A.O. - has(\"XXXXXXXXX0\")), outstanding()", ++testNumber,
            totalPassed, totalTested);


    // add(int)
    //
    order0.Order::add(1);
    if(order0.outstanding() != 1) {
        testFailed("result of add(1) incorrect", ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("passed add(1)", ++testNumber, totalPassed, totalTested);

    order8.Order::add(1);
    if(order8.outstanding() != 0) {
        testFailed("result of add(1) incorrect", ++testNumber, &totalFailed, totalTested);
    } else
        testPassed("passed add(1)", ++testNumber, totalPassed, totalTested);



    // copy constructor
    //
    SpecialOrder s = order0;
    if(!(s.has(ISBN("9070002043", list)) && s.outstanding() == 1)) {
        testFailed("C.C. - has(\"9070002043\"), outstanding()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("C.C. - has(\"9070002043\")), outstanding()", ++testNumber,
            totalPassed, totalTested);

    SpecialOrder* t = new SpecialOrder(ISBN("014010867X", list), "note");
    if (t) {
      testPassed("created (\"014010867X\") dynamically", ++testNumber, totalPassed,
          totalTested);

      t->Order::add(1);
      if(!(t->has(ISBN("014010867X", list)) && t->outstanding() == 1)) {
        testFailed("C.C. - has(\"014010867X\"), outstanding()", ++testNumber,
            &totalFailed, totalTested);
      } else
        testPassed("C.C. - has(\"014010867X\")), outstanding()", ++testNumber,
            totalPassed, totalTested);
      delete t;
    } else
        testFailed("could not create (\"014010867X\") dynamically", ++testNumber,
            &totalFailed, totalTested);


    // constructor - safe state
    //
    SpecialOrder c(ISBN("9070002044", list), "constructor");
    if(!(c.has(ISBN()) && c.outstanding() == 0)) {
        testFailed("Ctor - has(\"9070002044\"), outstanding()", ++testNumber,
            &totalFailed, totalTested);
    } else
        testPassed("Ctor - has(\"9070002044\")), outstanding()", ++testNumber,
            totalPassed, totalTested);

    return totalFailed;
}
#endif

/* testPassed displays passing message, increments *totalPassed and *total
*  i holds test number
*/
void testPassed(const char* message, int i, int* totalPassed, int* total) {
    if (DEBUG && message[0] != '\0')
        printf("totalPassed test %4d (%s)\n", i, message);
    ++*totalPassed;
    ++*total;
}

/* testFailed displays failure message, resets *totalFailed to false, increments
*  *total i holds test number
*/
void testFailed(const char* message, int i, int* totalFailed, int* total) {
    char ESC=27;
    printf("%c[1m",ESC);      // turn console bold on
    printf("FAILED TEST %4d (%s) <===\n", i, message);
    printf("%c[0m",ESC);      // turn console bold off
    *totalFailed = false;
    ++*total;
}
