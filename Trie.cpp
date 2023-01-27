#include <bits/stdc++.h>

using namespace std;

class Trie {

private:
    Trie* children[26];
    bool isEnd;

public:
    Trie(): isEnd{false} {
        for (int i = 0; i < 26; ++ i) this->children[i] = nullptr;
    }

    void addWord(const string word) {

        Trie* root = this;

        for (char c : word) {
            if (!root->children[c - 'a']) root->children[c - 'a'] = new Trie();
            root = root->children[c - 'a'];
        }

        root->isEnd = true;

    }

    bool includesWord(const string word) {

        Trie* root = this;

        for (char c : word) {
            if (!root->children[c - 'a']) return false;
            root = root->children[c - 'a'];
        }

        return root->isEnd;

    }

    bool deleteWord(const string word) {

        if (word == "") return false;
        Trie* root = this;
        Trie* lastNode = nullptr;
        char lastChar = word[0];
        for (char c : word) {
            if (!root->children[c - 'a']) return false;

            int cnt = 0;
            for (int i = 0; i < 26; ++ i)
                if (root->children[i]) ++ cnt;

            if (cnt > 1) {
                lastNode = root;
                lastChar = c;
            }

            root = root->children[c - 'a'];
        }

        int cnt = 0;
        for (int i = 0; i < 26; ++ i)
            if (root->children[i]) ++ cnt;

        if (cnt) root->isEnd = false;
        else {
            Trie* tmp = lastNode->children[lastChar - 'a'];
            lastNode->children[lastChar - 'a'] = nullptr;
            lastNode = tmp;
            while (lastNode) {
                Trie* tmp = nullptr;
                for (int i = 0; i < 26; ++ i)
                    if (lastNode->children[i]) {
                        tmp = lastNode->children[i];
                        delete(lastNode);
                        lastNode = tmp;
                    }
                if (!tmp) lastNode = nullptr;
            }
        }

        return true;

    }


};

int main() {

    Trie* root = new Trie();
    root->addWord("hello");
    root->addWord("helli");
    root->addWord("helium");
    root->addWord("man");
    root->addWord("manicure");
    root->addWord("solo");
    root->addWord("apple");

    // Test includesWord and addWord
    cout << boolalpha;
    cout << root->includesWord("hello") << "\n";
    cout << root->includesWord("solo") << "\n";
    cout << root->includesWord("applf") << "\n";

    // Test deleteWord
    cout << (root->deleteWord("helli") ? "Deleted helli" : "Error occured!") << "\n";
    cout << root->includesWord("helli") << "\n";
    cout << root->includesWord("hello") << "\n";
    cout << (root->deleteWord("apple") ? "Deleted apple" : "Error occured!") << "\n";
    cout << root->includesWord("apple") << "\n";
    cout << (root->deleteWord("man") ? "Deleted man" : "Error occured!") << "\n";
    cout << root->includesWord("man") << "\n";
    cout << root->includesWord("manicure") << "\n";
    return 0;

}
