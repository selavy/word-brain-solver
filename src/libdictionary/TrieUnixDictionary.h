//
// Created by peter on 4/26/15.
//

#ifndef WORD_BRAIN_SOLVER_TRIEUNIXDICTIONARY_H
#define WORD_BRAIN_SOLVER_TRIEUNIXDICTIONARY_H

#include "Dictionary.h"
#include "Trie.h"

class TrieUnixDictionary : public Dictionary {
public:
    explicit TrieUnixDictionary(std::size_t maxSize=0);
    explicit TrieUnixDictionary(std::vector<int>& wordLengths);
    virtual ~TrieUnixDictionary();
    virtual bool check(const std::string& word) const;

private:
    rtv::Trie<char, std::string> trie_;

private: // methods
    template <typename T>
    void load(T verify);

    bool isPrefix(std::string const &word) const;
};


#endif //WORD_BRAIN_SOLVER_TRIEUNIXDICTIONARY_H
