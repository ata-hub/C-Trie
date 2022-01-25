#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;

class Trie
{
    Trie* children[26];
    bool isEndWord;
    string value;
     char letter;
    public:
        Trie();
        Trie(char c);
        virtual ~Trie();
        void insertTrie(string word, string val,fstream &f);
        void searchTrie(string word,fstream &f);
        void listTrie(Trie* root,fstream &f);
        void printRestChildren(Trie* node,string word,int childnum,fstream &f);
        void deleteWord(string word,fstream &f);
        void deleteTillChild(string word);
        bool startsWith(string word);
        int childCounter(Trie* node);
        int firstLevelNum(Trie* root);
        list<Trie*> firstLevel(Trie* root);
        Trie* longestRoot(Trie* root);
        string longestRootMeaning(Trie* root);
    protected:

    private:
        int listcounter=0;
        string longestRootS="";
        int wordcounter=0;
};

#endif // TRIE_H
