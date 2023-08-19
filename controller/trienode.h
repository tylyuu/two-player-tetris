#ifndef COMMANDTRIE_H
#define COMMANDTRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
class TrieNode {
public:
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::vector<std::string> word;
};

class CommandTrie {
public:
    std::shared_ptr<TrieNode> root;

    CommandTrie();
    void addWord(const std::string &word);
    std::string getWord(const std::string &prefix) const;
};

#endif 
