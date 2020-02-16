// 010-NodeTest.cpp

// main() provided in 000-CatchMain.cpp

#include "catch.hpp"

#include <utility>
#include "../Node.hpp"




//



//APutils::Node<std::pair<int, int>> testNode{testPair, &c};
//
////    APutils::Node<std::pair<int,int>> testNodeMatteo3(testPair,nullptr,nullptr,nullptr);
////    APutils::Node<std::pair<int,int>> test2();
//testNode.printNode();
//testNodeMatteo.printNode();
////APutils::Node<std::pair<int, int>> testNode2{};
////testNode2 = testNodeMatteo;  // already NOT ALLOWED by the unique_ptr


//std::pair<int, int> rootPair(1,1);
//std::pair<const int, int> leftPair(0,0);
//const std::pair<const int, int> rightPair(2,2);
//APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
////APutils::Node<std::pair<int, int>> nodeLeft(leftPair, &nodeRoot);
////APutils::Node<std::pair<int, int>> nodeRight(rightPair,&nodeRoot);
////nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeLeft);  // <- WRONG!!!
////nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(&nodeRight); // <- WRONG!!!
//nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
//nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

//nodeRoot.left->printNode();
//nodeRoot.right->printNode();
//nodeRoot.printNode();






TEST_CASE( "Inserting pairs into Nodes", "[node_insert]" ) {

    APutils::Node<std::pair<int, int>> c;
    std::pair<int, int> testPair(3,4);

    SECTION( "Empty Node" ) {

        REQUIRE( c.data.first == 0 );
        REQUIRE( c.data.second == 0 );
        REQUIRE( c.parent == nullptr );
        REQUIRE( c.left.get() == nullptr );
        REQUIRE( c.right.get() == nullptr );
    }

    SECTION( "Node with Data" ) {

        APutils::Node<std::pair<int,int>> testNode(testPair, nullptr);

        REQUIRE( testNode.data.first == 3 );
        REQUIRE( testNode.data.second == 4 );
        REQUIRE( testNode.parent == nullptr );
        REQUIRE( testNode.left.get() == nullptr );
        REQUIRE( testNode.right.get() == nullptr );
    }

    SECTION( "Node with Data and Parent" ) {

        APutils::Node<std::pair<int,int>> testNode(testPair, &c);

        REQUIRE( testNode.data.first == 3 );
        REQUIRE( testNode.data.second == 4 );
        REQUIRE( testNode.parent == &c );
        REQUIRE( testNode.left.get() == nullptr );
        REQUIRE( testNode.right.get() == nullptr );
    }

//    SECTION( "reserving bigger changes capacity but not size" ) {
//        v.reserve( 10 );

//        REQUIRE( v.size() == 5 );
//        REQUIRE( v.capacity() >= 10 );
//    }
//    SECTION( "reserving smaller does not change size or capacity" ) {
//        v.reserve( 0 );

//        REQUIRE( v.size() == 5 );
//        REQUIRE( v.capacity() >= 5 );
//    }
}








//std::string one() {
//    return "1";
//}

//TEST_CASE( "Assert that something is true (pass)", "[require]" ) {
//    REQUIRE( one() == "1" );
//}

//TEST_CASE( "Assert that something is true (fail)", "[require]" ) {
//    REQUIRE( one() == "x" );
//}

//TEST_CASE( "Assert that something is true (stop at first failure)", "[require]" ) {
//    WARN( "REQUIRE stops at first failure:" );

//    REQUIRE( one() == "x" );
//    REQUIRE( one() == "1" );
//}

//TEST_CASE( "Assert that something is true (continue after failure)", "[check]" ) {
//    WARN( "CHECK continues after failure:" );

//    CHECK(   one() == "x" );
//    REQUIRE( one() == "1" );
//}

//TEST_CASE( "Assert that something is false (stops at first failure)", "[require-false]" ) {
//    WARN( "REQUIRE_FALSE stops at first failure:" );

//    REQUIRE_FALSE( one() == "1" );
//    REQUIRE_FALSE( one() != "1" );
//}

//TEST_CASE( "Assert that something is false (continue after failure)", "[check-false]" ) {
//    WARN( "CHECK_FALSE continues after failure:" );

//    CHECK_FALSE(   one() == "1" );
//    REQUIRE_FALSE( one() != "1" );
//}
