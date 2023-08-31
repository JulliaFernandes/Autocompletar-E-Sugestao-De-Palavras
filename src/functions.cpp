#include"functions.hpp"

using namespace std;

void fillHeap(vector<WordInfo*>& heap, const unordered_map<string, WordInfo>& glossary, int k, string word_select) {
    int num = min(k, static_cast<int>(glossary.size()));
    heap.reserve(num);
    

    auto it = glossary.begin();
    for (int i = 0; i < num; ++i) {
        if(it->second.word != word_select){
            heap.push_back(const_cast<WordInfo*>(&it->second));
        }
        ++it;
    }

    while(it!=glossary.end()) {
        if(it->second.word != word_select){
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
        }
        ++it;
    }

    int width = 20;
    cout << "+" << setfill('-') << setw(width - 2) << "+" << endl;
    for (int i = 0; i <(int)heap.size() ; ++i) {
        cout << i+1 << ") " << "\033[31m" << heap[i]->word << "\033[0m" << ": " << heap[i]->occurrences << endl;
    }
    cout << "+" << setfill('-') << setw(width - 2) << "+" << endl;

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
            if(newNode->words.occurrences > tmp->words.occurrences){
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

void printLevels(Node* root) 
{
    if (!root) {
        std::cout << "Árvore vazia." << std::endl;
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* curr = q.front();
            q.pop();
            std::cout << curr->words.word << " ";

            if (curr->left_son)
                q.push(curr->left_son);
            if (curr->right_son)
                q.push(curr->right_son);
        }
        std::cout << std::endl;
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
        // WordInfo newWord;
        // newWord.occurrences = 1;
        // newWord.word = line;
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
    //cout << "veio?? " << t->words.word << "- " << r.word << endl;

  } 
  else {
    
    if(r.occurrences <= (t)->words.occurrences){
        //cout << "veio?? 2 " << t->words.word << "- " << r.word << endl;
        insertTree((t)->left_son, r);
      if ((getWeight((t)->left_son) - getWeight((t)->right_son)) == 2){
        //cout << "GET HEIGHT 2 " <<  getWeight((t)->left_son) - getWeight((t)->right_son) << endl;
      	if(r.occurrences <= (t)->left_son->words.occurrences){
            //cout << "ntrou " <<  t->words.word << "- " << r.word << endl;
            rotacaoSimplesDireita(t);
            //cout << "saiu?? " << t->words.word << "- " << r.word << endl;
        }
      		
      	else{
            //cout << "ntrou 2" << t->words.word << "- " << r.word << endl;
            rotacaoDuplaDireita(t);
            //cout << "siu 2" << t->words.word << "- " << r.word << endl;
        }
      		
      }
    }

    if(r.occurrences > (t)->words.occurrences){
        //cout << "veio?? 3 " << t->words.word  << "- " << r.word << endl;
      insertTree((t)->right_son, r);
      if ((getWeight((t)->right_son) - getWeight((t)->left_son)) == 2){
        //cout << "GET HEIGHT 3 " <<  getWeight((t)->right_son) - getWeight((t)->left_son) << endl;
      	if(r.occurrences > (t)->right_son->words.occurrences){
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
        //fifo.push(entry.second); //Qaundo é o sem ponteiro
	}
}

void printQueue(priority_queue<Node*, vector<Node*>, Compare> fifo)
{
    while(!fifo.empty())
    {
        cout << "Caractere: " << fifo.top()->words.word << " Frequency: " << fifo.top()->words.occurrences << endl;
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
        //cout << "----WORD: " << left->words.word << endl;

        right = fifo.top();
        fifo.pop();
        //cout << "----WORD2: " << right->words.word << endl;

        newNode.words.word = "\0";
        newNode.words.occurrences = left->words.occurrences + right->words.occurrences;
        //cout << "OCURRENCES: " << newNode.words.occurrences << endl;

        Node* mergedNode = new Node(newNode);
        mergedNode->left_son = left;
        mergedNode->right_son = right;

        fifo.push(mergedNode);

        // cout << "*************" << endl;
        // printQueue(fifo);
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

void buildHuffmanCodes(Node* root, string code, unordered_map<string, string>& huffmanCodes)
{
    if (!root)
        return;

    //if (root->huffman_node.carac != '\0') huffmanCodes[root->huffman_node.carac] = code;

    code.push_back('0');
    buildHuffmanCodes(root->left_son, code, huffmanCodes);
    code.pop_back(); // Remove o último caractere ("0") após retornar da chamada recursiva à esquerda
    
    //cout << "CODE: " << code << endl;
    // Adiciona "1" ao caminho
    code.push_back('1');
    buildHuffmanCodes(root->right_son, code, huffmanCodes);
    code.pop_back(); // Remove o último caractere ("1") após retornar da chamada recursiva à direita

    //cout << "1CODE: " << code << endl;
    // Se o nó atual não tiver filhos (for uma folha), armazene o código binário no mapa
    if (root->left_son == nullptr && root->right_son == nullptr) {
        huffmanCodes[root->words.word] = code;
    }
}

void HuffmanCode(vector<Node*>heap_aux, priority_queue<Node*, vector<Node*>, Compare> &fifo, string code, unordered_map<string, string>& encodedHuffman)
{
    //cout << "------------------[CODIGO HUFFMAN]----------" << endl;
    putWordsInQueue(heap_aux, fifo);
    //cout << "\nFIFO" << endl;
    //printQueue(fifo);

    HuffmanTree(fifo);

    //cout << "FILA " << endl;
    //printPreOrder(fifo.top());
    cout << "--------------------------------------------------" << endl;

    //string code="";
    buildHuffmanCodes(fifo.top(), code, encodedHuffman);
    
    cout << "CODIFICAÇÃO HUFFMAN" << endl;

    for(auto entry: encodedHuffman){
        cout << "CHAR: " << entry.first << " CODE: " << entry.second << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

