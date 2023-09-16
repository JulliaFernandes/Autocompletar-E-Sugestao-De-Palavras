#include"functions.hpp"

using namespace std;

int indexHuffman=0;

void deleteContent()
{
    string nomeArquivo = "data/Output.data";

    // Abra o arquivo em modo de truncamento (ios::trunc)
    ofstream arquivo(nomeArquivo, ios::trunc);

    // Verifique se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    // Feche o arquivo após a limpeza
    arquivo.close();
}

void creatHeap(vector<WordInfo*>& heap, const unordered_map<string, WordInfo>& glossary, int k)
{
    int num = min(k, static_cast<int>(glossary.size()));
    heap.reserve(num);

    auto it = glossary.begin();
    for (int i = 0; i < num; ++i) {
        //if(it->second.word != word_select[i]){
            heap.push_back(const_cast<WordInfo*>(&it->second));
        //}
        ++it;
    }

    while(it!=glossary.end()) {
        //if(it->second.word != word_select){
            WordInfo* current = const_cast<WordInfo*>(&it->second);
            if (current->occurrences > heap[0]->occurrences) {
                heap[0] = current;

                // Reorganizar o heap usando o afundamento (sink) HEAPIFY
                //int index = num;
                int index = 0;
                int n = num; // Tamanho atual do heap
                while (true) {
                    int leftChild = 2 * index + 1;
                    int rightChild = 2 * index + 2;
                    int smallest = index;

                    if (leftChild < n && heap[leftChild]->occurrences < heap[smallest]->occurrences)
                        smallest = leftChild;

                    if (rightChild < n && heap[rightChild]->occurrences < heap[smallest]->occurrences)
                        smallest = rightChild;

                    if (smallest != index) {
                    // i++;
                        //cout << "Esse: " << heap[index]->word << ": " << heap[index]->occurrences << " trocou por: " << heap[smallest]->word << ": " << heap[smallest]->occurrences << endl;
                        std::swap(heap[index], heap[smallest]);
                        index = smallest;
                    } else {
                        break;
                    }
                }
            }
        //}
        ++it;
    }

}

void fillHeap(vector<WordInfo*> heap, const unordered_map<string, WordInfo>& glossary, vector<string>word_select, vector<WordInfo*>& newHeap, vector<Node*>&heap_aux, Node *&rootBT, Node *&rootAVL, priority_queue<Node*, vector<Node*>, Compare> &fifo,vector<pair<string, string>> &encHuffman,  FilesInfo &newInfos, unordered_map<string, FilesInfo> &info_files, string fileName, int k) 
{   
    newHeap = heap;
    bool okay;

    for(int i= 0; i< (int)word_select.size(); i++ ){
        cout << "--> word: " << word_select[i] << endl;
        if(glossary.find(word_select[i]) != glossary.end()){
            okay = false;
            for(int j=0; j<(int)newHeap.size(); j++){
                if(newHeap[j]->word == word_select[i]){
                    okay = true;
                    newHeap.erase(newHeap.begin()+j);
                    j--;

                    for(int m=k/2-1; m>=0; m--){
                        heapify(newHeap, k, m);
                    }
                    break;
                }
            }

            if(!okay){ //precisa tirar o primeiro elemento, pois nao havia no heap a palavra de frequencia desejada
                newHeap.erase(newHeap.begin());
                int n = newHeap.size();
                int index = 0;
                while (true) {
                    int leftChild = 2 * index + 1;
                    int rightChild = 2 * index + 2;
                    int smallest = index;

                    if (leftChild < n && newHeap[leftChild]->occurrences < newHeap[smallest]->occurrences)
                        smallest = leftChild;

                    if (rightChild < n && newHeap[rightChild]->occurrences < newHeap[smallest]->occurrences)
                        smallest = rightChild;

                    if (smallest != index) {
                        std::swap(newHeap[index], newHeap[smallest]);
                        index = smallest;
                    } else {
                        break;
                    }
                }
            }
        }
        else{ //Nao tem a plavra que deseja no texto em que esta
            newHeap.erase(newHeap.begin());
            newInfos.frequencyWord=0;
        }

        int width = 20;
        cout << "+" << setfill('-') << setw(width - 2) << "+" << endl;
        for (int i = 0; i <(int)newHeap.size() ; ++i) {
            cout << i+1 << ") " << "\033[31m" << newHeap[i]->word << "\033[0m" << ": " << newHeap[i]->occurrences << endl;
        }
        cout << "+" << setfill('-') << setw(width - 2) << "+" << endl;

        callingBuildFunctions(newHeap, heap_aux, rootBT, rootAVL);

        bool canBuild = callingBuildFunctionsHuffman(glossary, word_select[i], encHuffman, fifo, heap_aux);
        if(canBuild){
            newInfos.rootBinaryTree = rootBT;
            newInfos.rootAVL = rootAVL;
            newInfos.fifo = fifo;
            newInfos.encHuffman = encHuffman;
            newInfos.wordSelect = word_select[i];
            newInfos.frequencyWord = glossary.at(word_select[i]).occurrences;

            info_files[fileName] = newInfos;

            outputFile(fileName, newInfos, "data/Output.data");
        }
        else{
            newInfos.wordSelect = word_select[i];
            newInfos.frequencyWord = 0;
            outputFile(fileName, newInfos, "data/Output.data");
        }
        newHeap = heap;
        cleaningVariables(heap_aux, encHuffman ,rootBT, rootAVL, newInfos, fifo);
    }
}

void callingBuildFunctions(vector<WordInfo*>& newHeap, vector<Node*>&heap_aux, Node *&rootBT, Node *&rootAVL)
{
    for(int h=0; h<(int)newHeap.size(); h++){ // Pegando cada item do heap e montando as arovres AVL e Binárias
            WordInfo newWord;
            newWord.word = newHeap[h]->word;
            newWord.occurrences = newHeap[h]->occurrences;
            
            //Necessario para utilizar no CodigoHuffaman
            Node *node_aux = new Node;
            node_aux->words=newWord;

            heap_aux.push_back(node_aux);

            auto start = chrono::high_resolution_clock::now();
            buildBinaryTree(newWord, rootBT);
            auto end = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
            //cout << "Tempo para buildBinaryTree: " << duration.count() << " nanossegundos" << endl;
            

            start = chrono::high_resolution_clock::now();
            insertTree(rootAVL, newWord);
            end = chrono::high_resolution_clock::now();

            duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
            //cout << "Tempo para insertTree: " << duration.count() << " nanossegundos" << endl;
    }   
}


bool callingBuildFunctionsHuffman(const unordered_map<string, WordInfo>& glossary, string word_select,vector<pair<string, string>> &encHuffman,  priority_queue<Node*, vector<Node*>, Compare> &fifo, vector<Node*>&heap_aux)
{
    if(glossary.find(word_select) != glossary.end()){
        string code="";
        encHuffman.clear();
        indexHuffman=0;
        HuffmanCode(heap_aux, fifo, code, encHuffman);
        return 1;
    }
    else return 0;
}

void cleaningVariables(vector<Node*>&heap_aux, vector<pair<string, string>> &encHuffman ,Node *&rootBT, Node *&rootAVL, FilesInfo &newInfos, priority_queue<Node*, vector<Node*>, Compare> &fifo)
{
    heap_aux.clear();
    encHuffman.clear();
    indexHuffman=0;
    rootBT = NULL;
    rootAVL = NULL;
    newInfos.wordSelect = "";
    newInfos.frequencyWord = 0;
    while (!fifo.empty()) {
        fifo.pop(); // Remove o elemento do topo da fila
    }
}


void heapify(vector<WordInfo*>& newHeap, int n, int index){
    int minimum = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    if (leftChild < n && newHeap[leftChild]->occurrences < newHeap[minimum]->occurrences)
        minimum = leftChild;
    if (rightChild < n && newHeap[rightChild]->occurrences < newHeap[minimum]->occurrences)
        minimum = rightChild;
    if(minimum!=index){
        swap(newHeap[index], newHeap[minimum]);
        heapify(newHeap, n, minimum);
    }
}



bool emptyLine(const string linha)
{
    for (char c : linha){
        if (!isspace(c)){ // Se o caractere não for espaço em branco, a linha não está vazia
            return false;
        }
    }
    // Se todos os caracteres forem espaços em branco, a linha está vazia
    return true;
}

void readText(string fileName, ifstream &file, unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords)
{
  file.open(fileName);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }
    regex exceptions("[a-zA-Z0-9'À-ÿ\\-“”]+");

    string line;
    bool aux=false;

    while (getline(file, line))
    {
        sregex_iterator it(line.begin(), line.end(),exceptions); //criado um objeto que vai percorrer a frase salva em line e vai utlizar a expressao regular exceptions
        sregex_iterator end; //objeto criado para representar o fim da frase salva em line
        
        while (it != end) //percorre todas as correspondências encontradas pela expressão regular na linha.
        { 
            string word = it->str(); //aqui é pq cheguei a alguma coisa que nao é minha expressao regular, por exemplo, um espaco ou ponto, enfim ai passo ela para uma variavel de string
            
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if(word == "É"){
                word = "é";
            }
            if(glossaryStopWords.find(word) == glossaryStopWords.end()) //se nao achar no de StopWords posso adicionar ao meu glossary
            {   
                aux = treatments(word);
                if(!aux){
                    WordInfo newWord;
                    newWord.occurrences = 1;
                    newWord.word = word;
                    if(glossary.find(word) != glossary.end()) glossary[word].occurrences++;
                    else glossary[word] = newWord;
                } 
            }
            ++it;
            aux=false;
        }
    }
    glossary.erase("-");
    glossary.erase("—");

    file.close();
}

void buildBinaryTree(WordInfo word, Node *&root)
{
    Node *newNode = new Node;
    newNode->words = word;
    newNode->left_son = NULL;
    newNode->right_son = NULL;

    if(root == NULL){
        root = newNode;
    }
    else{
        Node *tmp = root;

        while(tmp != NULL){
            if(newNode->words.occurrences >= tmp->words.occurrences){
                if(tmp->right_son == NULL){
                    tmp->right_son = newNode;
                    break;
                }
                else{
                    tmp = tmp->right_son;
                }
            }
            else{
                if(tmp->left_son == NULL){
                    tmp->left_son = newNode;
                    break;
                }
                else{
                    tmp = tmp->left_son;
                }
            }
        }
    }   
}

void fillGlossaryStopWords(unordered_map<string, WordInfo> &glossaryStopWords)
{
    ifstream fileStopWords;

    fileStopWords.open("data/stopwords.txt");
    if (!fileStopWords.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string line;
    while(getline(fileStopWords, line)){
        if(!fileStopWords.eof()){
            line.pop_back();
        }
        WordInfo newWord;
        newWord.occurrences = 1;
        newWord.word = line;

        glossaryStopWords[line] = newWord;
    }

    fileStopWords.close();

}

void printGlossary(unordered_map<string,WordInfo> glossary)
{
  for (const auto& entry : glossary) {
    cout << "Chave no map: " << entry.first << ": " << entry.second.occurrences << endl;
  }
}

bool treatments(string &word)
{   
    if ( word.length() >= 2 && (word[0] == '-' && word[1] == '-') ){
        word.erase(0,2);
        if(word.length()==0) return true;
        else return false;
    } 

    if(word.length() >= 2 && word[0] == '-' && word[(int)word.size()-1] == '-'){
        word.erase(0,1);
        word.pop_back();
        if(word.length()==0) return true;
        else return false;
    }
    
    if(word[0] == '-'){
        word.erase(0,1);
        if(word.length()==0) return true;
        else return false;
    }

    if(word[word.size()-1] == '-'){
        word.pop_back();
        if(word.length()==0) return true;
        else return false;
    }
    
    if( (word.length() >= 3 && (word.substr(word.size()-3, word.size()-1) == "”" )) ){
        word.erase(word.size()-3, word.size()-1);
        if(word.length()==0) return true;
        else return false;
    }
    
    if(word.length() >= 3 && word.substr(0,3) == "“"){
        word.erase(0,3);
        if(word.length()==0) return true;
        else return false;
    }

    return false;
}

void printLevels(Node* root, ostream& output) 
{
    if (!root) {
        output << "Árvore vazia." << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* curr = q.front();
            q.pop();
            output << curr->words.word << " ";

            if (curr->left_son)
                q.push(curr->left_son);
            if (curr->right_son)
                q.push(curr->right_son);
        }
        output << endl;
    }
}


void printOrder(Node* current_No, ostream& output)
{
    //visita os da esquerda dps o atual e dps os da direita
    if(current_No != NULL){
        //visita os da esquerda
        printOrder(current_No->left_son, output);

        //visita o  atual
        output << current_No->words.word << ": ";
        output << current_No->words.occurrences << " || " ;

        //visita os da direita
        printOrder(current_No->right_son, output);
    }
}

void getWordsSelect(vector<string>&wordsSelect)
{
    ifstream filewordsSelect;

    filewordsSelect.open("data/input.data");
    if (!filewordsSelect.is_open()) {
        cout << "!ERROR OPENING THE FILE!" << endl;
        return;
    }

    string line;
    while(getline(filewordsSelect, line)){
        if(!filewordsSelect.eof()){
            line.pop_back();
        }
        string newWord;
        newWord = line;

        wordsSelect.push_back(newWord);
    }

    filewordsSelect.close();
}


void insertTree(Node *&t, WordInfo r){

  if(t == NULL){
    
    t = new Node;
    (t)->left_son  = NULL; 
    (t)->right_son  = NULL; 
    (t)->weight = 0;
    (t)->words   = r; 

  } 
  else {
    
    if(r.occurrences < (t)->words.occurrences){
        insertTree((t)->left_son, r);
      if ((getWeight((t)->left_son) - getWeight((t)->right_son)) == 2){
      	if(r.occurrences < (t)->left_son->words.occurrences){
            rotacaoSimplesDireita(t);
        }
      		
      	else{
            rotacaoDuplaDireita(t);
        }
      		
      }
    }

    else if(r.occurrences >= (t)->words.occurrences){
        //cout << "veio?? 3 " << t->words.word  << "- " << r.word << endl;
      insertTree((t)->right_son, r);
      if ((getWeight((t)->right_son) - getWeight((t)->left_son)) == 2){
        //cout << "GET HEIGHT 3 " <<  getWeight((t)->right_son) - getWeight((t)->left_son) << endl;
      	if(r.occurrences >= (t)->right_son->words.occurrences){
            //cout << "entraaa 4" <<  t->words.word << "- " << r.word << endl;
            rotacaoSimplesEsquerda(t);
            //cout << "saiu 4" << t->words.word << "- " << r.word << endl;
        }
      		
      	else{
            //cout << "entraaa 5" <<  t->words.word << "- " << r.word << endl;
            rotacaoDuplaEsquerda(t);
            //cout << "saiuu 5" <<  t->words.word << "- " << r.word << endl;
        }
      }
    }  
  }

  (t)->weight = getMaxWeight(getWeight((t)->left_son), getWeight((t)->right_son)) + 1;
}

void rebalanceTree(Node *&t){
	int balance;
  	int left = 0;
  	int right = 0;

	balance = getWeight((t)->left_son) - getWeight((t)->right_son);
	if((t)->left_son)
		left = getWeight((t)->left_son->left_son) - getWeight((t)->left_son->right_son);
	if((t)->right_son)
		right = getWeight((t)->right_son->left_son) - getWeight((t)->right_son->right_son);

	if(balance == 2 && left >= 0)
		rotacaoSimplesDireita(t);
	if(balance == 2 && left < 0)
		rotacaoDuplaDireita(t);

	if(balance == -2 && right <= 0)
		rotacaoSimplesEsquerda(t);
	if(balance == -2 && right > 0)
		rotacaoDuplaEsquerda(t); 	
}

int getWeight(Node *&t){
	if(t == NULL)
		return -1;
	return (t)->weight;
}

int getMaxWeight(int left, int right){
	if(left > right)
		return left;
	return right;
}

void rotacaoSimplesDireita(Node *&t){
	Node *aux;
	aux = (t)->left_son;
	(t)->left_son = aux->right_son;
	aux->right_son = (t);
	(t)->weight = getMaxWeight(getWeight((t)->left_son), getWeight((t)->right_son)) + 1;
	aux->weight  = getMaxWeight(getWeight(aux->left_son), (t)->weight) + 1;
	(t) = aux;
}

void rotacaoSimplesEsquerda(Node *&t){
	Node *aux;
	aux = (t)->right_son;
	(t)->right_son = aux->left_son;
	aux->left_son = (t);
	(t)->weight = getMaxWeight(getWeight((t)->left_son), getWeight((t)->right_son)) + 1;
	aux->weight  = getMaxWeight(getWeight(aux->left_son), (t)->weight) + 1;
	(t) = aux;
}

void rotacaoDuplaDireita(Node *&t){
	rotacaoSimplesEsquerda((t)->left_son);
	rotacaoSimplesDireita(t);
}

void rotacaoDuplaEsquerda(Node *&t){
	rotacaoSimplesDireita((t)->right_son);
	rotacaoSimplesEsquerda(t);
}



void putWordsInQueue(vector<Node*>heap, priority_queue<Node*, vector<Node*>, Compare> &fifo)
{
    for(auto entry : heap){
        fifo.push(entry);
	}
}

void printQueue(priority_queue<Node*, vector<Node*>, Compare> fifo)
{
    while(!fifo.empty())
    {
        fifo.pop();
    }
}

void HuffmanTree(priority_queue<Node*, vector<Node*>, Compare> &fifo)
{
    while(fifo.size() != 1)
    {
        Node *left, *right;
        Node newNode;

        left = fifo.top();
        fifo.pop();

        right = fifo.top();
        fifo.pop();

        newNode.words.word = "\0";
        newNode.words.occurrences = left->words.occurrences + right->words.occurrences;

        Node* mergedNode = new Node(newNode);
        mergedNode->left_son = left;
        mergedNode->right_son = right;

        fifo.push(mergedNode);
        printQueue(fifo);
    }
}

void printPreOrder(Node* current_No)
{
    //visita o atual e dps os da esquerda e dps os da direita
    if(current_No != NULL){
        //visita no atual
        cout << current_No->words.word << ": ";
        cout << current_No->words.occurrences << endl;

        //vai para os filhos da esquerda e dps pro da direita
        printPreOrder(current_No->left_son);
        printPreOrder(current_No->right_son);
    }
}

void buildHuffmanCodes(Node* root, string code, vector<pair<string, string>> &encHuffman)
{
    if (!root)
        return;

    code.push_back('0');
    buildHuffmanCodes(root->left_son, code, encHuffman);
    code.pop_back(); // Remove o último caractere ("0") após retornar da chamada recursiva à esquerda
    
    code.push_back('1');
    buildHuffmanCodes(root->right_son, code, encHuffman);
    code.pop_back(); // Remove o último caractere ("1") após retornar da chamada recursiva à direita

    if (root->left_son == nullptr && root->right_son == nullptr) {
        encHuffman.push_back(make_pair(code, root->words.word));
        indexHuffman++; 
    }
}

void HuffmanCode(vector<Node*>heap_aux, priority_queue<Node*, vector<Node*>, Compare> &fifo, string code, vector<pair<string, string>> &encHuffman)
{
    putWordsInQueue(heap_aux, fifo);
    printQueue(fifo);

    HuffmanTree(fifo);

    //cout << "FILA " << endl;
    //printPreOrder(fifo.top());

    // cout << "--------------------------------------------------" << endl;

    buildHuffmanCodes(fifo.top(), code, encHuffman);
    // cout << "CODIFICAÇÃO HUFFMAN" << endl;
    // for(auto entry: encHuffman){
    //     cout << "CHAR: " << entry.first << " CODE: " << entry.second << endl;
    // }
    // cout << "--------------------------------------------------" << endl;
}

void outputFile(const string fileName, FilesInfo info_files, string OutputFinal)
{
    ofstream outputFile(OutputFinal, ios::app);
    if (!outputFile.is_open()) {
        cerr << "Unable to open the file: " << fileName << endl;
        return;
    }

    outputFile << "FILE: " << fileName << endl;
    if(info_files.frequencyWord != 0){
        outputFile << "WORD \t\t FREQEUNCY" << endl;
        outputFile << ">" << info_files.wordSelect << "\t\t    " << info_files.frequencyWord << endl;
        outputFile << "-----BINARY TREE BY LEVEL-----" << endl;
        printOrder(info_files.rootBinaryTree, outputFile);
        //printLevels(info_files.rootBinaryTree, outputFile);
        outputFile << "\n\n-----AVL TREE BY LEVEL-----" << endl;
        printOrder(info_files.rootAVL, outputFile);
        //printLevels(info_files.rootAVL, outputFile); 
        outputFile << "\n\n-----HUFFMAN CODES-----" << endl;

        for(auto entry: info_files.encHuffman){
            outputFile <<  entry.first << ": " << entry.second <<" || ";

        }
        outputFile << "\n-----------------------------------------------------------------------------------------------------------------------" << endl << endl;
    }
    else{
        outputFile << "WORD \t\t FREQEUNCY" << endl;
        outputFile << ">" << info_files.wordSelect << "\t\t    " << info_files.frequencyWord << endl;
        outputFile << "THIS WORD DOESN'T EXIST IN THIS FILE" << endl;
        outputFile << "-----BINARY TREE BY LEVEL-----" << endl;
        outputFile << "\t\tNULL" << endl;
        outputFile << "\n-----AVL TREE BY LEVEL-----" << endl;
        outputFile << "\t\tNULL" << endl;
        outputFile << "\n-----HUFFMAN CODES-----" << endl;
        outputFile << "\t\tNULL" << endl;
        outputFile << "-----------------------------------------------------------------------------------------------------------------------" << endl << endl;
    }
    

}