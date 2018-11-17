///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list( string_vector &strings ) {

  srand( time( NULL ) );

  for( int i = 0; i < strings.size()-1; i++ )
  {
    int random = rand() % strings.size();
    swap( strings[i], strings[random] );
  }
}

//-----------------------------------------------------------------------------
void merge( string_vector &strings, size_t start, size_t mid, size_t end ) {

	string_vector sortedStrings; //sorted vector being returned
	int startCount = 0;
	int midCount = mid;
  // IF - we get a vector with one or zero elements
  if ( strings.size() <= 1 )
  {
    return;
  }
  // FOR - traversing strings
	for ( int i = 0; i < strings.size(); i++ )
	{
		// IF - ran out of words from start
		if ( startCount >= mid )
		{
			sortedStrings.push_back( strings[midCount] );
			midCount++;
		}
		// ELIF - ran out of words from mid
		else if ( midCount >= strings.size() )
		{
			sortedStrings.push_back( strings[startCount] );
			startCount++;
		}
		// ELIF - start word is lower
		else if ( strings[startCount] < strings[midCount] )
		{
			sortedStrings.push_back( strings[startCount] );
			startCount++;
		}
		// ELSE - mid word is lower
		else
		{
			sortedStrings.push_back( strings[midCount] );
			midCount++;
		}

	}
  // RETURN - sorted vector
	strings = sortedStrings;
	return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort( string_vector & strings, size_t start, size_t end ) {
	int mid;
  // IF - we receive vector with 1 or 0 elements
	if ( strings.size() <= 1 )
	{
	   return;
	}
  // ElIF - we receive vector with even number of elements
	else if ( strings.size() % 2 == 0 )
	{
	   mid = strings.size() / 2;
	}
  // ELSE - we receive vector with odd number of elements
	else
	{
		 mid = ( strings.size() + 1 ) / 2;
	}
	string_vector stringsB;  //vector with first half of words
  stringsB.insert( stringsB.end(), strings.begin(), strings.begin() + mid );
	string_vector stringsC;  //vector with second half of words
  stringsC.insert( stringsC.end(), strings.begin() + mid, strings.end() );
  //recurse with stringsB
	mergesort( stringsB, start, mid - 1 );
  //recurse with stringsC
	mergesort( stringsC, mid, end );
  //merging vector
	strings = stringsB;
  strings.insert( strings.end(), stringsC.begin(), stringsC.end() );
  //sorting merged vector
	merge( strings, start, mid, end );
	return;
}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition( string_vector &strings, int start, int end ) {

  string pivot = strings[start]; //word to be compared
	int i = start; //counter starts from beginning
	int j = end;   //counter starts from end
	while ( i < j )
	{
    //helps sort words before partition
		while ( j > start && pivot < strings[j] )
    {
			j--;
		}
    //puts word before pivot
    swap( strings[i], strings[j] );
    //helps sort words after partition
		while ( i < end && pivot > strings[i] )
    {
			i++;
		}
    //puts word after pivot
		swap( strings[i], strings[j] );
	}
  // RETURN - pivot point
	return j;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort( string_vector &strings, int start, int end ) {
  // IF - # of strings is not 0 or 1
  if( start < end )
  {
    //finds pivot point
    int pivot_point = hoare_partition( strings, start, end );
    //quicksorts left half
    quicksort( strings, start, pivot_point );
    //quicksorts right half
    quicksort( strings, pivot_point+1, end );
  }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path)
{
  //std::cout << "Loading words from [" << path << "]" << std::endl;
  words.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int countWordsLoaded = 0;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
  }
  //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
  return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  mergesort(strings, 0, strings.size() - 1);
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  quicksort(strings, 0, strings.size() - 1);
  return;
}
