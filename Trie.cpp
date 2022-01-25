#include "Trie.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;

Trie::Trie()
{
    isEndWord=false;
    letter='0';
    for(int i=0;i<26;i++){
        children[i]=nullptr;
    }
}

Trie::Trie(char c)
{
    isEndWord=false;
    letter=c;
    for(int i=0;i<26;i++){
        children[i]=nullptr;
    }
}

Trie::~Trie()
{
    //dtor
}
void Trie::insertTrie(string word, string val,fstream &f){

    Trie* curr=this;
    for(char c:word){

        if(!(curr->children[c-'a'])){

            curr->children[c-'a']=new Trie(c);

        }

        curr=curr->children[c-'a'];
    }
    if(curr->isEndWord==true &&curr->value==val){
        f<<"\""<<word<<"\""<<" already exist"<<endl;

    }
    else if(curr->isEndWord==true &&curr->value!=val){
        curr->value=val;
        f<<"\""<<word<<"\""<<" is updated"<<endl;
    }
    else{
    curr->isEndWord=true;

    curr->value=val;

    f<<"\""<<word<<"\""<<" was added"<<endl;
    }

}
void Trie::searchTrie(string word,fstream &f){
    Trie*curr=this;
    for(char c:word){
        curr=curr->children[c-'a'];
        if(c==word[0]&&!(curr)){
            f<<"\""<<"no record"<<"\""<<endl;
            return;
        }
        else if(!(curr)){
            f<<"\""<<"incorrect Dothraki word"<<"\""<<endl;
            return;
        }
    }
    if(curr->isEndWord){
        f<<"\""<<"The English equivalent is "<<curr->value<<"\""<<endl;
    }
    else{
        f<<"\""<<"not enough Dothraki word"<<"\""<<endl;
    }
}

void Trie::deleteTillChild(string word){
    int counter=0;
    bool secondIsEndWord=false;
    Trie*curr=this;
    list<Trie*> deleteNodes;
    for(char c:word){
        curr=curr->children[c-'a'];
        deleteNodes.push_front(curr);
    }
    for(auto& a:deleteNodes){
        counter++;
        if(a->childCounter(a)>1){

            for(int i=0;i<26;i++){
                if(a->children[i]!=nullptr && a->children[i]->letter==word.at(word.length()-counter+1)){

                    a->children[i]=nullptr;
                }
            }
            break;
        }
        else if(a->isEndWord==true && secondIsEndWord==true){
            //cout<<"Second end word reached, breaking loop"<<endl;
            break;
        }
        else{

            if(a->isEndWord==true){
                secondIsEndWord=true;
            }
            for(int i=0;i<26;i++){
                a->children[i]=nullptr;
            }
        }
    }


}

void Trie::deleteWord(string word,fstream &f){
    Trie*curr=this;
    for(char c:word){
        curr=curr->children[c-'a'];
        if(c==word[0]&&!(curr)){
            f<<"\""<<"no record"<<"\""<<endl;
            return;
        }
        else if(!(curr)){
            f<<"\""<<"incorrect Dothraki word"<<"\""<<endl;
            return;
        }
    }
    if(curr->isEndWord){

        //currün childı varsa sadece value'sunu sil, eğer childı yoksa bütün harfleri sil
        if(curr->childCounter(curr)==0){
            //code to delete all letters which only have 1 child
            deleteTillChild(word);

        }
        else{
            curr->value="";
            curr->isEndWord=false;
        }



        f<<"\""<<word<<"\""<<" deletion is successful."<<endl;
    }
    else{
        f<<"not enough Dothraki word"<<endl;
    }


}
void Trie::listTrie(Trie* root,fstream &f){

    if(!root){
        f<<"This root is null"<<endl;
        return;
    }
    Trie*temp=root;
    if(temp->letter=='0'){//ilk trie objesiyse
        //int arrSize=firstLevelNum(temp);
        list<Trie*> firstLevelArr=firstLevel(temp);
        for(auto const& a:firstLevelArr){
            Trie* lastNode=longestRoot(a);//modifies longestRootS
            f<<"-"<<longestRootS;
            int childnum=lastNode->childCounter(lastNode);
            if(lastNode->isEndWord){
                f<<"("<<lastNode->value<<")"<<endl;
            }
            else{
                f<<"\n";
            }
            printRestChildren(lastNode,longestRootS,childnum,f);
            wordcounter=0;

        }
    }
    else{
        //buraya longestRoot ve childCounter kodlarını ekle

    }

    /*if(root->isEndWord){
        listcounter=0;
        cout<<"("<<root->value<<")";
        cout<<"\n";
    }
    for(int i=0;i<26;i++){
        if(temp->children[i]!=nullptr){
            listTrie(temp->children[i]);
        }
    }*/


}
bool Trie::startsWith(string prefix){
    Trie*curr=this;
    for(char c:prefix){
        curr=curr->children[c-'a'];
        if(!(curr)){
            return false;
        }
    }
    return true;



}
int Trie::childCounter(Trie* node){
    int counter=0;
    for(int i=0;i<26;i++){
        if(node->children[i]!=nullptr){
            counter++;
        }
    }
    return counter;

}
Trie* Trie::longestRoot(Trie* root){//returns last node, this function can only be applied to first level nodes
    int val=0;

    string s="";
    if(root->childCounter(root)>1){

        string a(1,root->letter);
        s=s+a;//add the char to the string
        longestRootS=s;
        return root;
    }
    while(root->childCounter(root)<=1){

                bool flag=false;
                string a(1,root->letter);
                s=s+a;//add the char to the string
                for(int i=0;i<26;i++){
                   if(root->children[i]!=nullptr){

                        val=i;
                        flag=true;
                   }

                }
                if(flag==false){
                   longestRootS=s;
                   return root;
                }
                root=root->children[val];


    }
    string a(1,root->letter);
    s=s+a;//add the char to the string
    longestRootS=s;


    return root;
}

string Trie::longestRootMeaning(Trie* root){//returns last node, this function can only be applied to first level nodes
    int val=0;

    string s="";
    if(root->childCounter(root)>1){

        if(root->isEndWord){
            string a=root->value;
            s="("+a+")";
        }

        return s;
    }
    while(root->childCounter(root)<=1){

                bool flag=false;
                string a(1,root->letter);
                s=s+a;//add the char to the string
                for(int i=0;i<26;i++){
                   if(root->children[i]!=nullptr){

                        val=i;
                        flag=true;
                   }

                }
                if(flag==false){
                   longestRootS=s;
                   if(root->isEndWord){
                        string a=root->value;
                        s="("+a+")";
                   }
                   return s;
                }
                root=root->children[val];


    }
    if(root->isEndWord){
        string a=root->value;
        s=s+a;//add the char to the string
    }




    return s;
}

int Trie::firstLevelNum(Trie* root){
    int num=0;
    for(int i=0;i<26;i++){
        if(root->children[i]!=nullptr){
            num++;
        }
    return num;
}
}
list<Trie*> Trie::firstLevel(Trie* root){
    int Arrsize=firstLevelNum(root);
    int counter1=0;
    list <Trie*> firstlevels;
    for(int i=0;i<26;i++){
        if(root->children[i]!=nullptr){
            firstlevels.push_back(root->children[i]);

        }
    }
    return firstlevels;

}

/*string Trie::RestChildren(Trie* node,string s){

    if(node->isEndWord){
            cout<<"("<<node->value<<")";
            cout<<"\n";
            }

    for(int i=0;i<26;i++){
       if(node->children[i]!=nullptr){
            cout<<node->children[i]->letter;
            printRestChildren(node->children[i]);
       }
    }


    return s;
}*/

void Trie::printRestChildren(Trie* node,string word,int childnum,fstream &f){

    bool flag=false;
    if(listcounter==0 && wordcounter<childnum){
        f<<"\t-"<<word;
        flag=true;
    }
    /*if(node->isEndWord){
            cout<<"("<<node->value<<")";
            cout<<"\n";
            }*/

    for(int i=0;i<26;i++){
       if(node->children[i]!=nullptr){
            if(node->children[i]->value==""){
                f<<node->children[i]->letter<<node->children[i]->value;
                listcounter++;
            }
            else{
                f<<node->children[i]->letter<<"("<<node->children[i]->value<<")"<<endl;
                listcounter=0;
                wordcounter++;
            }
            printRestChildren(node->children[i],word,childnum,f);
       }
    }

}
