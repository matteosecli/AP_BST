#include <iostream>
#include <algorithm>    //For std::random_shuffle
#include <chrono>
#include <fstream>
#include <map>
#include <numeric>      // For std::iota, zuppa triestina
//#include <string>
#include <type_traits>  // For std::conditional

#include "BST.hpp"

/* Use the best steady clock available in the system */
using Clock = std::conditional<std::chrono::high_resolution_clock::is_steady,
                               std::chrono::high_resolution_clock,
                               std::chrono::steady_clock>::type;

using TimeUnits = std::chrono::nanoseconds;
constexpr char TimeUnitsStr[] = "nanoseconds";


int main( int argc, char* argv[] ) {
    // Defaults
    int nStart = 1000 ;   // Starting value of range of elements in the tree
    int nIncr  = 1000 ;   // Increment of range of elements in the tree
    int nEnd   = 50000;   // Ending value of range of elements in the tree
    int nSampl = 50   ;   // Number of samples in each measurement
    if ( argc > 1 ) {
        nStart = strtol(argv[ 1], NULL, 10);
        nIncr  = strtol(argv[ 2], NULL, 10);
        nEnd   = strtol(argv[ 3], NULL, 10);
        nSampl = strtol(argv[ 4], NULL, 10);
    }

    /* Open the file stream */
    std::ofstream fileOut;
    std::ofstream fileOutBal;
    std::ofstream fileOutMap;
    fileOut   .open("benchmark_times_tree.txt" );
    fileOutBal.open("benchmark_times_btree.txt");
    fileOutMap.open("benchmark_times_map.txt"  );
    fileOut    << TimeUnitsStr << "\n" << nStart << "\n" << nIncr << "\n" << nEnd << "\n" << nSampl << std::endl;
    fileOutBal << TimeUnitsStr << "\n" << nStart << "\n" << nIncr << "\n" << nEnd << "\n" << nSampl << std::endl;
    fileOutMap << TimeUnitsStr << "\n" << nStart << "\n" << nIncr << "\n" << nEnd << "\n" << nSampl << std::endl;

    /* Loop on the number of elements in the tree */
    for (int nCurrent = nStart; nCurrent <= nEnd; nCurrent+=nIncr) {

        /* Write nCurrent on file */
        fileOut    << nCurrent;
        fileOutBal << nCurrent;
        fileOutMap << nCurrent;

        /* Generate a randomized vector of pairs */
        std::vector<int> v(nCurrent);                // Create a vector with nCurrent elements.
        std::iota(std::begin(v), std::end(v), 1);    // Fill with 1, 2, ..., nCurrent.
        std::random_shuffle( v.begin(), v.end() );   // Reshuffle with builtin random generator.

        /* Create our tree from v */
        APbst::bst<int,int> tree{};
        for ( const auto& i : v ) { tree.emplace(i,i); }

        /* Create the balanced tree */
        APbst::bst<int,int> treeBal{tree};
        treeBal.balance();

        /* Create the map */
        std::map<int,int> stdMap{};
        for ( const auto& i : v ) { stdMap.emplace(i,i); }


        /* Measure our search times of nSampl elements in the tree/map */
        for ( int m = 1; m <= nCurrent/nSampl; ++m ) {


            /* Standard BST */
            auto tStart = Clock::now();
            /* Find elements */
            for ( int i = (m-1)*nSampl; i<m*nSampl; ++i ) {
                tree.find(v[i]);
            }
            /* Store the time and reset the clock */
            auto tEnd = Clock::now();
            fileOut << "\n" << std::chrono::duration_cast<TimeUnits>(tEnd-tStart).count(); // "\t"?


            /* Balanced BST */
            auto tStartBal = Clock::now();
            /* Find elements */
            for ( int i = (m-1)*nSampl; i<m*nSampl; ++i ) {
                treeBal.find(v[i]);
            }
            /* Store the time and reset the clock */
            auto tEndBal = Clock::now();
            fileOutBal << "\n" << std::chrono::duration_cast<TimeUnits>(tEndBal-tStartBal).count(); // "\t"?


            /* Standard Map */
            auto tStartMap = Clock::now();
            /* Find elements */
            for ( int i = (m-1)*nSampl; i<m*nSampl; ++i ) {
                stdMap.find(v[i]);
            }
            /* Store the time and reset the clock */
            auto tEndMap = Clock::now();
            fileOutMap << "\n" << std::chrono::duration_cast<TimeUnits>(tEndMap-tStartMap).count(); // "\t"?


        }

        /* Write EOL on output file */
        fileOut    << std::endl;
        fileOutBal << std::endl;
        fileOutMap << std::endl;

    }

    /* Close output file */
    fileOut   .close();
    fileOutBal.close();
    fileOutMap.close();


    return 0;

}
