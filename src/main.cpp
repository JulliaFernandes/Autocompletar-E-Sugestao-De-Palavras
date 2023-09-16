#include"functions.hpp"

using namespace std;

#define k 11 //QUANTIDADE DE ELEMENTOS DE MAIOR FREQUENCIA
#define ARQ 6 //QUANTIDADE DE ARQUIVOS A SEREM PROCESSADOS

int main()
{
    clock_t startTime, endTime;
    startTime = clock();

    ifstream file;
    unordered_map<string, WordInfo> glossary;
    unordered_map<string, WordInfo> glossaryStopWords;
    
    
    unordered_map<string, FilesInfo> info_files; //Informações de cada arquivo

    //Para a Codificação de Huffman
    priority_queue<Node*, vector<Node*>, Compare> fifo;
    vector<pair<string, string>> encHuffman;
    
    vector<string>wordsSelect;

    Node *rootBT = NULL;
    Node *rootAVL = NULL;

    vector<WordInfo*> heap;
    vector<Node*>heap_aux;
    vector<WordInfo*> newHeap;

    FilesInfo newInfos;

    deleteContent();

    fillGlossaryStopWords(glossaryStopWords);
    
    getWordsSelect(wordsSelect); //Pega as palavras desejadas e as coloca em um vetor

    newHeap = heap;

    for(int i=1; i<=ARQ; i++){
        string fileName = "data/input" + to_string(i) + ".txt";
        cout << "FILE: " << fileName << endl;
        readText(fileName, file, glossary, glossaryStopWords);

        creatHeap(heap, glossary, k);

        fillHeap(heap, glossary, wordsSelect, newHeap, heap_aux, rootBT, rootAVL, fifo, encHuffman ,newInfos, info_files, fileName, k);
        glossary.clear();
        heap.clear();
        newHeap.clear();
        heap_aux.clear();
        
        newInfos.wordSelect="";
        newInfos.frequencyWord =0;
        while (!fifo.empty()) {
            fifo.pop(); // Remove o elemento do topo da fila
        }
    }

    cout << "--------------------------------------------------------------------------" << endl;

    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "TEMPO DE EXECUÇÃO: " << elapsedTimeMs << " ms " << endl;
    return 0;
}