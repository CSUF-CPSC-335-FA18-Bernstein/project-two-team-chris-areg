///////////////////////////////////////////////////////////////////////////////
// experiment.cc
//
// Example code showing how to run an algorithm once and measure its elapsed
// time precisely. You should modify this program to gather all of your
// experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "project2.hh"
#include "timer.hh"

using namespace std;

int main() {

  string_vector all_words;
  // IF - words fail to load output error message and end code
  if ( ! load_words( all_words, "words.txt" ) ) {
    cerr << "error: cannot open \"words.txt\"" << endl;
    return 1;
  }

  std::ofstream myfile; //ofstream used to write test values to .csv file
  myfile.open( "quicksort.csv" );

  for( int i= 0; i < 100; i++ )
  {
    int n = 400000;
    string_vector n_words( all_words.begin(), all_words.begin() + n );

    randomize_list( n_words );

    Timer timer;
    quicksort( n_words );
    double elapsed = timer.elapsed();
    cout << "quicksort, "
         << "n=" << n << ", "
         << "elapsed time = " << elapsed << " seconds" << endl;

    myfile << elapsed << endl;
  }
  myfile.close();

  return 0;
}
