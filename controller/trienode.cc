#include "trienode.h"

CommandTrie::CommandTrie() {
    root = std::make_shared<TrieNode>();
}

void CommandTrie::addWord(const std::string &word) {
    std::shared_ptr<TrieNode> node = root;
    for (char c : word) {
        if (node->children.count(c) == 0)
            node->children[c] = std::make_shared<TrieNode>();
        node->word.emplace_back(word);
        node = node->children[c];
    }
    node->word.emplace_back(word);
}

std::string CommandTrie::getWord(const std::string &prefix) const {
    std::shared_ptr<TrieNode> node = root;
    for (char c : prefix) {
        if (node->children.count(c) == 0)
            return "";
        else if (node->word.size() == 1)
            return node->word.at(0);
        else
            node = node->children[c];
    }
    if (node->word.size() == 1)
        return node->word.at(0);
    else
        return "";
}
