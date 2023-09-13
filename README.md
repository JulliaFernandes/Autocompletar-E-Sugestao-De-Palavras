<h1 align="center" font-size="200em"><b> Sugestao De Palavras </b></h1>

<div align = "center" >
<!-- imagem -->

[![requirement](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![Make](https://img.shields.io/badge/Compilacao-Make-orange)
![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)
</div>

## 📌Sumário
- [Objetivos](#Objetivos)
- [Introdução](#Introdução)
- [Logica adotada](#Lógica-adotada)
- [Resolução do Problema](#Resolução-do-problema)
- [Arquivos](#Arquivos)
- [Estruturas utilizadas](#estruturas-utilizadas)
- [Funções](#Funções)
- [Resultados](#Resultados)
- [Tempo] (#Tempo)
- [Conclusão](#Conclusão)
- [Referências](#Referências)
- [Compilação e execução](#Compilação-e-execução)
- [Contato](#Contato)

  
## 💻Objetivos
Este é um programa desenvolvido em C++ para a disciplina de Algoritmos e Estruturas de Dados II, proposta pelo professor [Michel Pires](https://github.com/mpiress) <br>
O objetivo desta atividade consiste em verificar a existencia de uma palavra digitada pelo usuario em determinado texto e apartir dela criar uma árvore binaria, AVL e uma codificação Huffman, deve-se entao criar um sistema que possibilite a funcionalidade de oferecer sugestões de palavras aos usuários.
Sendo assim ao final dessa atividade teremos um algoritmo que realiza as operações:
- [✔️] De busca de uma palavra em textos
- [✔️] Seleciona as K palavras mais frequentes presente e cada texto e lhe da de sugestão 
- [✔️] Realiza a montagem de arvores binárias, AVL e codificação de Huffman

Neste programa foi feita a utlização de bibliotecas como `<unordered_map>` que é estrutura propria da linguagem C++ que serve para a utilização da montagem da tabela hash, sendo possivel mais informações sobre essa biblioteca clicando no link a seguir: [<unordered_map>](URL)



## ✒️Introdução

<p align="justify">
<h4><em>Oque é uma arvore na programação</em></h4> Uma árvore é uma forma de organizar informações em que os dados estão organizados de cima para baixo, como ramos de uma árvore, ao contrário de uma lista onde os dados estão em uma linha reta, nas árvores os dados estão dispostos de forma hierárquica.
</p>

<h4><em>Caracteristicas de uma arvore</em></h4>

<li> Raiz: Toda arvore possui o nó raiz que é o nó inicial da árvore;</li>
<li> Grau: o número de filhos que um nó possui; </li>
<li> Nível (ou profundidade): a distância de um nó até a raiz;</li>
<li> Altura: o maior nível encontrado na árvore (altura de uma árvore com n nós pode variar de lg(n) até n-1);</li>
<li> Folha: o nó que não possui filho;</li>
<li> O numero maior que o atual vai para a direita, o menor que o no atual vai para a esquerda, sendo assim possivel as funções de inserção, remoção e procura</li>

A partir disso é possivel implementar varias tipos de arvores, como a AVL, a binária a Red-Black-Tree, mas tendo suas mudanças cada uma.

<h4><em>Codificação de Huffman</em></h4>
Uma árvore de Huffman é uma estrutura binária na qual cada nó interno possui exatamente dois filhos. Importante notar que as árvores de Huffman não consideram a relação de ordem (esquerda ou direita) entre os filhos de um nó.<br>
Uma árvore binária completa, conhecida como árvore de Huffman, é construída de forma recursiva combinando os dois símbolos de menor probabilidade. Esses símbolos, os utilizados nesse trabalho foi o simbolo de vazio: '/0', são agrupados em novamente com o restante dos simbolos. Esse processo é repetido até que todos os símbolos tenham sido agrupados em símbolos auxiliares, formando assim uma árvore binária. Posteriormente, a árvore é percorrida e valores binários, 1 ou 0, são atribuídos a cada aresta. Os códigos são então gerados com base nesse percurso, sendo o 0 a ida para a esquerda e 1 a ida para a direita.







## 🧠Lógica adotada

Nesse programa foi utilizado uma atividade ja realizada a atividade Top K Itens, nela tinhamos que pegar as K palavras mais frequentes de um texto e com isso exibir ao usuário a montagem de arvore tendo como filhos as posições 2*i+1 e 2*i+2, mais informações sobre essa atividade e como foi feita a implementaçõe e como foi feito basta clicar no link a seguir: [Top K Itens](https://github.com/JulliaFernandes/TopKItens). <br> 
Tendo uma parte ja feita foi necessario somente complementar com as funções das criações das arvores.

Buscando uma melhora significativa de tempo foi utlizado a abordagem de fazer a leitura de todas as palavras por arquivo, dessa maneira a cada arquivo de texto aberto é visto se a lista de palavras selecionadas pelo usuario esta presente no texto, se em caso afirmativo é realizado a montagem da arvore das K palavras mais frequentes e realizado a montagem de cada árvore necessaria para a aplicação dessa atividade e a codificação de huffman, importante ressaltar que se a palavra procurada estiver presente no texto e tambem ser uma das palavras mais frequentes no texto e estiver no heap montado é necessario exclui-la de la e colocar a proxima palavra mais frequente.

🚨 <b>INFORMAÇÕES IMPORTANTES</b> 🚨 <br>
- É importante que o usuário especifique a quantidade desejada de palavras de sugestão, que está localizada na linha (XX) do arquivo `main.cpp`. A quantidade desejada deve ser um item a mais; por exemplo, se desejar as 10 palavras mais frequentes, você deve configurar a quantidade como 11. Durante a execução do código, haverá manipulação para excluir uma palavra e, ao final, o programa apresentará ao usuário apenas as 10 palavras mais frequentes
- Certifique-se de nomear os arquivos no formato "input1.txt", "input2.txt" e assim por diante para garantir o funcionamento correto do código. Também é necessário incluir a quantidade de arquivos a serem lidos na linha (XX) do arquivo `main.cpp`.
 

A função principal desse algoritmo é a:<br>
- `fillheap()`: abordamos a lógica de criar um heap com as K palavras mais frequentes. Como mencionado anteriormente, o usuário precisa especificar a quantidade desejada com um item a mais. Nessa função, verificamos se a palavra procurada está presente no heap. Se estiver, ela é removida, e a estrutura do heap é reorganizada para manter a quantidade desejada pelo usuário. Se a palavra não estiver no heap, apenas o primeiro item (com a menor frequência) é excluído, e o heap é ajustado para garantir que os filhos sejam maiores que o pai.<br>
Após essa etapa, com o heap devidamente configurado, chamamos as funções de inserção para as árvores AVL e binária, além de criar a árvore de Huffman. Em seguida, a função responsável por colocar as informações coletadas de uma palavra no output é chamada, seguida pela limpeza das variáveis usadas para garantir o funcionamento adequado na próxima palavra.<br>
Esse processo é repetido até que todas as palavras escolhidas pelo usuário sejam processadas no texto em questão. Somente então podemos avançar para o próximo texto.

- `buildBinaryTree()`: função que tem o objetivo de criar a arvore binária.
- `insertTree()`: função de criação da árvore AVL.
- `HuffmanTree()`: funçõa de criação da árvore de Huffman.
- `HuffmanCode()`: função criada no intuito de salvar os códigos formados de cada palavra da arvore de Huffman.
- `buildHuffmanCodes()`: função criada para a contrução dos codigos na arvore de Huffman.
- `outputFile()`: função para escrever no arquivo de saida.
- `creatHeap()`: função de criação do heap e das K palavras mais frequentes.

## ⚙️ Estruturas utilizadas
Após compreendermos a estrutura de uma árvore binária e seus conceitos básicos, a implementação da árvore AVL exigiu a introdução de funções adicionais. O funcionamento geral de uma árvore AVL segue a mesma lógica de uma árvore binária, mas se diferencia devido aos constantes balanceamentos que ocorrem. Para lidar com isso, foram criadas funções cruciais, incluindo:

- `rebalanceTree`: Responsável por reequilibrar a árvore quando necessário.
- `getWeight`: Usada para calcular o peso de um nó.
- `getMaxWeight`: Utilizada para determinar o peso máximo de um nó.
- `rotacaoSimplesDireita`: Realiza uma rotação simples para a direita.
- `rotacaoSimplesEsquerda`: Executa uma rotação simples para a esquerda.
- `rotacaoDuplaDireita`: Realiza uma rotação dupla para a direita.
- `rotacaoDuplaEsquerda`: Realiza uma rotação dupla para a esquerda.<br>

Essas funções desempenham um papel essencial na manutenção do balanceamento da árvore AVL, especialmente quando um nó atinge uma altura de 2.

No que diz respeito ao código Huffman, a árvore é montada progressivamente. A ideia por trás do código Huffman envolve adicionar todos os elementos do heap a uma priority_queue, organizando-os em ordem crescente. Em seguida, os dois primeiros elementos da fila de prioridades são combinados em um novo nó, um se tornando o filho direito e o outro o filho esquerdo. Esse processo é repetido até que reste apenas um elemento na fila, sinalizando a conclusão da árvore de Huffman.<br>
É importante observar que no código Huffman, as palavras mais frequentes têm códigos menores e estão localizadas mais próximas do topo da árvore. Além disso, a construção da árvore de Huffman segue a lógica "bottom-up", ou seja, começa com os elementos menores e cria a árvore de forma ascendente. Isso garante que as palavras mais comuns sejam representadas por códigos mais curtos, economizando espaço na representação do texto.<br>
Para criar os códigos, seguimos uma lógica simples:

- Ao percorrer à esquerda em direção a um nó, atribuímos o número 0.
- Ao percorrer à direita em direção a um nó, atribuímos o número 1.<br>
Esse processo de atribuição de códigos é repetido até chegarmos a um nó folha, que corresponderá a uma palavra específica no texto. Dessa forma, cada palavra terá um código único baseado em sua posição na árvore de Huffman. 


## 🕗 Tempo:
Os tempos obtidos foram em nanosegundos visto que sua implemntação se deu muito rapida, com isso foi possivel obter o valor de numero para a montagem das arvores AVL, binarias e codigo huffman, a que apresentou melhores resultados foi a arovre binaria com um tempo medio de : XXXXX, o motivo de ela ter sido mais rapida de todas esta diretamente ligado ao fato da forma como os dados estão sendo inseridos visto que a arovre binaria se encontra muito desequilibrada e n realiza rotações, por mais que a AVL tenha gasto nanosegundos a mais sua eficiencia é garantida principalmnte nas operações de busca remoção, algo que pela binaria não ocorre muito bem. O codigo huffman foi o mais demorado em relação aos outros e isso se da tambem devido a como é realizado sua montagem, levando à uma piora no quesito tempo.

## RESULTADOS E ANÁLISE
Antes de procedermos com qualquer análise, é crucial ter em mente que os resultados dos testes podem variar consideravelmente dependendo das máquinas em que o programa é executado. Conforme a intuição sugere, máquinas mais poderosas tendem a produzir resultados superiores. Para referência, os testes a seguir foram realizados em um computador com as seguintes especificações: processador {modelo do processador}, {quantidade de memória RAM} de RAM e GPU {modelo da GPU}.

Referencia

https://www.freecodecamp.org/portuguese/news/tudo-o-que-voce-precisa-saber-sobre-estruturas-de-dados-em-arvore/#:~:text=Uma%20%C3%A1rvore%20%C3%A9%20um%20conjunto,%C3%A1rvore%20%C3%A9%20chamado%20de%20raiz%20.

https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/huffman.html
