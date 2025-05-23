/**
 * @file homophone_puzzle.cpp
 * Implementation for an executable which solves one homophone related puzzles.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include "pronounce_dict.h"
#include "cartalk_puzzle.h"

using std::string;
using std::vector;
using std::get;
using std::cout;
using std::left;
using std::setw;
using std::endl;

int main(int argc, char* argv[])
{
    /* Default names. */
    string word_list_filename = "words.txt";
    string pronounce_dict_filename = "cmudict.0.7a";

    /* Process flags and arguments. */
    for(int i = 1; i < argc; i++) {
        if(std::strcmp(argv[i], "-w") == 0) {
            i++;
            if(i != argc) {
                word_list_filename = argv[i];
            }
        }
        else if(std::strcmp(argv[i], "-d") == 0) {
            i++;
            if(i != argc) {
                pronounce_dict_filename = argv[i];
            }
        }
    }

    PronounceDict d(pronounce_dict_filename);

    vector< StringTriple > result1 = cartalk_puzzle(d, word_list_filename);

    /* Here comes some awful string formatting. */
    size_t max_str_padding = 0;
    for(StringTriple& t : result1) {
        max_str_padding = std::max(max_str_padding, get<0>(t).size());
    }   
    max_str_padding++;
    for(StringTriple& t : result1) {
        cout << left << setw(15) << "Original word: " << setw(max_str_padding) 
        <<  get<0>(t) << setw(12) <<  "homophones: " << setw(max_str_padding) 
        << get<1>(t) << setw(max_str_padding) << get<2>(t) << endl;
    }
}
