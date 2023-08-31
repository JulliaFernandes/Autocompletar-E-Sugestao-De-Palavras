#include"functions.hpp"
//#include"header.hpp"

using namespace std;

#define k 10 //QUANTIDADE DE ELEMENTOS DE MAIOR FREQUENCIA
#define ARQ 6 //QUANTIDADE DE ARQUIVOS A SEREM PROCESSADOS

int main()
{
    clock_t startTime, endTime;
    startTime = clock();

    // std::locale::global(std::locale(""));
    // std::wcout.imbue(std::locale());
    // auto& f = std::use_facet<std::ctype<wchar_t>>(std::locale());

    ifstream file;
    unordered_map<string, WordInfo> glossary;
    unordered_map<string, WordInfo> glossaryStopWords;
    
    
    unordered_map<string, FilesInfo> info_files; //Informações de cada arquivo

    //Para a Codificação de Huffman
    priority_queue<Node*, vector<Node*>, Compare> fifo; 
    unordered_map<string, string> encodedHuffman;
    
    vector<string>wordsSelect;

    Node *rootBT = NULL;
    Node *rootAVL = NULL;

    vector<WordInfo*> heap;
    vector<Node*>heap_aux;

    FilesInfo newInfos;

    fillGlossaryStopWords(glossaryStopWords);
    
    getWordsSelect(wordsSelect); //Pega as palavras desejadas e as coloca em um vetor

    
    for(int i=0; i<(int)wordsSelect.size(); i++){
        cout << wordsSelect[i] << endl;

        for(int j=1; j<=ARQ; j++){
            string fileName = "data/input" + to_string(j) + ".txt";
            cout << "---------------[TEXTO " << fileName << "]---------------------------" << endl; 
            //string fileName = "data/teste.txt";
            readText(fileName, file, glossary, glossaryStopWords);
            
            fillHeap(heap, glossary, k, wordsSelect[0]);

            if(glossary.find(wordsSelect[i]) != glossary.end()){ //É pq existe nesse arquivo de texto
                for(int h=0; h<(int)heap.size(); h++){ // Pegando cada item do heap e montando as arovres AVL e Binárias
                    WordInfo newWord;
                    newWord.word = heap[h]->word;
                    newWord.occurrences = heap[h]->occurrences;
                    
                    //Necessario para utilizar no CodigoHuffaman
                    Node *node_aux = new Node;
                    node_aux->words=newWord;

                    heap_aux.push_back(node_aux);

                    buildBinaryTree(newWord, rootBT);
                    insertTree(rootAVL, newWord);
                }

                //Para o Codigo de Huffman;
                string code="";
                HuffmanCode(heap_aux, fifo, code, encodedHuffman);

                
                newInfos.rootBinaryTree = rootBT;
                newInfos.rootAVL = rootAVL;
                newInfos.fifo = fifo;
                newInfos.encodedHuffman = encodedHuffman;
                newInfos.wordSelect = wordsSelect[i];
                newInfos.frequencyWord = glossary.at(wordsSelect[i]).occurrences;

                info_files[fileName] = newInfos;

                cout << "\n[ROOT BINARY TREE]" << endl;
                printLevels(info_files.at(fileName).rootBinaryTree);
                cout << "\n[ROOT AVL]" << endl;
                printLevels(info_files.at(fileName).rootAVL);

                cout << "---------------------------FIM ARQUIVO ---------------------------" << endl;
                
            }
            else{
                cout << " ------ A PALAVRA: " << wordsSelect[i] << " NÃO SE ENCONTRA NO TEXTO DE NOME: " << fileName << endl;
            }
            outputFile(fileName, newInfos);
            heap.clear();
            glossary.clear();
        }
    }
    //printGlossary(glossaryStopWords);

    // for (const auto& pair : glossary) {
    //     buildBinaryTree(pair.second, root);
    // }

    

    // cout << "==========================================================================" << endl;
    // cout << "\t*** Palavras mais frequentes ***" << endl;
    // cout << setw(6) << "WORD" << " | " << setw(8) << "FREQUENCY" << endl;
    // fillHeap(heap, glossary, k);

    cout << "--------------------------------------------------------------------------" << endl;

    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "TEMPO DE EXECUÇÃO: " << elapsedTimeMs << " ms " << endl;
    return 0;
}