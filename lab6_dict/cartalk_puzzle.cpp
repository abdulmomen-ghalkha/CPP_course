/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using std::vector;
using std::string;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
    std::ifstream words_file(word_list_fname);
    string word;
    vector<StringTriple> results;

    if (!words_file.is_open()) {
        return results;
    }

    while (getline(words_file, word)) {
        if (word.length() >= 5) {
            string remove_first = word.substr(1);  
            string remove_second = word.substr(0, 1) + word.substr(2);  

            if (d.homophones(word, remove_first) &&
                d.homophones(word, remove_second)) {

                results.push_back({word, remove_first, remove_second});
            }
        }
    }

    return results;
}


