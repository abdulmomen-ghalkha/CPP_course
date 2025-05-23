/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    std::ifstream words_file(filename);
    std::string word;
    if (words_file.is_open()) {
        while (getline(words_file, word)) {
            std::string key = word;
            std::sort(key.begin(), key.end());
            auto& anagram_list = dict[key];
            if (std::find(anagram_list.begin(), anagram_list.end(), word) == anagram_list.end()) {
                anagram_list.push_back(word);
            }
        }
    }
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
    for (const std::string& word : words) {
        std::string key = word;
        std::sort(key.begin(), key.end());
        
        auto& anagram_list = dict[key];
        if (std::find(anagram_list.begin(), anagram_list.end(), word) == anagram_list.end()) {
            anagram_list.push_back(word);
        }
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    std::string key = word;
    std::sort(key.begin(), key.end());

    auto it = dict.find(key);
    if (it != dict.end()) {
        return it->second;
    }    
    return vector< string >();
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector< string > > result;

    for (const auto& pair : dict) {
        if (pair.second.size() >= 2) {
            result.push_back(pair.second);
        }
    }

    return result;
    //return vector< vector < string > >();
}


