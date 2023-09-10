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
- [Resolução do Problema](#Resolução-do-problema)
- [Arquivos](#Arquivos)
- [Estruturas utilizadas](#estruturas-utilizadas)
- [Funções](#Funções)
- [Resultados](#Resultados)
- [Conclusão](#Conclusão)
- [Referências](#Referências)
- [Compilação e execução](#Compilação-e-execução)
- [Contato](#Contato)

  
## 💻Objetivos
Este é um programa desenvolvido em C++ para a disciplina de Algoritmos e Estruturas de Dados II, proposta pelo professor [Michel Pires](https://github.com/nome-de-usuario) <br>
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

## 🗂️Estruturas utlizadas
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
