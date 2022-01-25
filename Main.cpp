#include <iostream>
#include "Trie.h"
#include <fstream>
#include <sstream>
using namespace std;


int main(int argc, char **argv)
{
    string inputfile=argv[1];
    string outputfile=argv[2];
    string line;
    int counter=0;
    fstream f;
    fstream f2;

    f.open(inputfile,ios::in);

    while(getline(f,line)){
        counter++;
    }
    f.close();

    string inputs[counter];
    counter=0;
    f.open(inputfile,ios::in);

    while(getline(f,line)){
        inputs[counter]=line;
        counter++;
    }
    f.close();

    f2.open(outputfile,ios::out);

    //beginning of trie (root)
    Trie* trie=new Trie();

    for(int i=0;i<counter;i++){
        if(inputs[i].substr(0,6)=="insert"){
            string delimeter="(";
            string delimeter2=")";

            string T;
            int paramsize=0;
            string param=inputs[i].substr(inputs[i].find(delimeter)+1,inputs[i].find(delimeter2)-7);
            string params[2];
            stringstream x(param);
            //temp[0] ı virgülle split et ve elemanları qstates listine ekle

            while (getline(x, T, ',')) {
                params[paramsize]=T;
                paramsize++;

            }

            //insert(params[0],params[1]);

            trie->insertTrie(params[0],params[1],f2);
        }
        else if(inputs[i].substr(0,6)=="delete"){
            string delimeter="(";
            string delimeter2=")";
            string param=inputs[i].substr(inputs[i].find(delimeter)+1,inputs[i].find(delimeter2)-7);
            //delete();
            trie->deleteWord(param,f2);

        }
        else if(inputs[i].substr(0,6)=="search"){
            string delimeter="(";
            string delimeter2=")";
            string param=inputs[i].substr(inputs[i].find(delimeter)+1,inputs[i].find(delimeter2)-7);

            //search(params[0],params[1]);

            trie->searchTrie(param,f2);

        }
        else if(inputs[i].substr(0,4)=="list"){
            //list();
            trie->listTrie(trie,f2);
        }
    }
    /*Trie* trie=new Trie();
    trie->insertTrie("achra","smelly");
    trie->insertTrie("adra","turtle");
    trie->insertTrie("gaezo","brother");
    trie->insertTrie("kemak","spouse");
    trie->insertTrie("kem","married");
    trie->insertTrie("kemik","ally");
    trie->insertTrie("gaezo","brother");
    trie->searchTrie("mekis");
    trie->searchTrie("adra");
    trie->searchTrie("gaez");
    trie->searchTrie("kemok");
    trie->searchTrie("kemak");
    trie->searchTrie("kem");*/


    return 0;
}
