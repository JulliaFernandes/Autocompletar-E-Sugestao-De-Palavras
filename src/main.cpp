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

    fillGlossaryStopWords(glossaryStopWords);
    
    getWordsSelect(wordsSelect); //Pega as palavras desejadas e as coloca em um vetor

    
    for(int i=0; i<(int)wordsSelect.size(); i++){
        cout << wordsSelect[i] << endl;

        for(int i=1; i<=ARQ; i++){
            string fileName = "data/input" + to_string(i) + ".txt";
            cout << "---------------[TEXTO " << fileName << "]---------------------------" << endl; 
            //string fileName = "data/teste.txt";
            readText(fileName, file, glossary, glossaryStopWords);
            
            fillHeap(heap, glossary, k, wordsSelect[0]);

            
            for(int i=0; i<(int)heap.size(); i++){ // Pegando cada item do heap e montando as arovres AVL e Binárias
                WordInfo newWord;
                newWord.word = heap[i]->word;
                newWord.occurrences = heap[i]->occurrences;
                
                //Necessario para utilizar no CodigoHuffaman
                Node *node_aux = new Node;
                node_aux->words=newWord;

                heap_aux.push_back(node_aux);

                buildBinaryTree(newWord, rootBT);
                insertTree(rootAVL, newWord);
            }

            // cout << "------------------[CODIGO HUFFMAN]----------" << endl;
            // putWordsInQueue(heap_aux, fifo);
            // cout << "\nFIFO" << endl;
            // printQueue(fifo);

            // HuffmanTree(fifo);

            // cout << "FILA " << endl;
            // //printPreOrder(fifo.top());
            // cout << "--------------------------------------------------" << endl;

            // string code="";
            // buildHuffmanCodes(fifo.top(), code, encodedHuffman);

            // cout << "CODIFICAÇÃO HUFFMAN" << endl;

            // for(auto entry: encodedHuffman){
            // 	cout << "CHAR: " << entry.first << " CODE: " << entry.second << endl;
            // }

            //Para o Codigo de Huffman;
            string code="";
            HuffmanCode(heap_aux, fifo, code, encodedHuffman);

            FilesInfo newInfos;
            newInfos.rootBinaryTree = rootBT;
            newInfos.rootAVL = rootAVL;
            newInfos.fifo = fifo;
            newInfos.encodedHuffman = encodedHuffman;

            info_files[fileName] = newInfos;

            cout << "\n[ROOT BINARY TREE]" << endl;
            printLevels(info_files.at(fileName).rootBinaryTree);
            cout << "\n[ROOT AVL]" << endl;
            printLevels(info_files.at(fileName).rootAVL);

            heap.clear();
            cout << "---------------------------FIM ARQUIVO ---------------------------" << endl;
        }
    }
    //printGlossary(glossaryStopWords);

    //Processamento por arquivo
    
    
    
    for(int i=0; i<(int)wordsSelect.size(); i++){
        
    }
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