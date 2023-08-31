#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include"header.hpp"
using namespace std;

typedef struct WordInfo{
  std::string word;
  int occurrences;

  WordInfo() : word("\0"), occurrences(0) {}

  WordInfo(string word, int occurrences){
    word = word;
    occurrences = occurrences;
  }

} WordInfo;

typedef struct Node{
  WordInfo words;
  Node *left_son;
  Node *right_son;
  int weight;

  Node() : words(WordInfo()), left_son(nullptr), right_son(nullptr), weight(0) {}
  Node(const WordInfo& w, Node* left = nullptr, Node* right = nullptr, int wgt = 0)
        : words(w), left_son(left), right_son(right), weight(wgt) {}

}Node;


struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->words.occurrences > b->words.occurrences;
    }
};


typedef struct FilesInfo{
  string wordSelect;
  int frequencyWord;
  Node *rootBinaryTree;
  Node *rootAVL;
  priority_queue<Node*, vector<Node*>, Compare> fifo;
  unordered_map<string, string> encodedHuffman; 
}FilesInfo;



void fillHeap(vector<WordInfo*>& heap, const unordered_map<string, WordInfo>& glossary, int k, string word_select);

bool emptyLine(const string linha);

void readText(string fileName, ifstream &file, unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords);

void buildBinaryTree(WordInfo word, Node *&root);

void fillGlossaryStopWords(unordered_map<string, WordInfo> &glossaryStopWords);

void printGlossary(unordered_map<string,WordInfo> glossary);

bool treatments(string &word);

void printLevels(Node* root, ostream& output = cout);

void getWordsSelect(vector<string>&wordsSelect);

void insertTree(Node *&t, WordInfo r);
void rebalanceTree(Node *&t);
int getWeight(Node *&t);
int getMaxWeight(int left, int right);
void rotacaoSimplesDireita(Node *&t);
void rotacaoSimplesEsquerda(Node *&t);
void rotacaoDuplaDireita(Node *&t);
void rotacaoDuplaEsquerda(Node *&t);


void putWordsInQueue(vector<Node*>heap, priority_queue<Node*, vector<Node*>, Compare> &fifo);
void printQueue(priority_queue<Node*, vector<Node*>, Compare> fifo);
void HuffmanTree(priority_queue<Node*, vector<Node*>, Compare> &fifo);
void printPreOrder(Node* current_No);
void buildHuffmanCodes(Node* root, string code, unordered_map<string, string>& huffmanCodes);
void HuffmanCode(vector<Node*>heap_aux, priority_queue<Node*, vector<Node*>, Compare> &fifo, string code, unordered_map<string, string>& encodedHuffman);

void outputFile(const string filename, FilesInfo info_files);

#endif