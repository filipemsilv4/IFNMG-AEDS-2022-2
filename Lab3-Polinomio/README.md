# Lab03: Polinomio

Implemente um polinômio com lista circular duplamente ligada, onde cada nó representa um coeficiente não nulo de algum grau não negativo inteiro. Mantenha sempre a lista ordenada por grau.


Explicação de bruno:

É pra criar uma lista duplamente encadeada com dois elementos, um é o coeficiente e outro é o grau, o coeficiente é o número que acompanha a variável no polinômio e o grau é o número que eleva essa variael no polinômio, exemplo:

2x³ + 3x² + 3

[(3,2), (2,3), (0,3)]

O primeiro elemento do primeiro par do conjunto é o grau e o segundo é o coeficiente.

Vc precisa criar um função somar e subtrair que faz a soma de dois polinômios, exemplo:

(2x³ + 3x² + 3) + (5x³ + 7x² + 9)

Quando vc soma um polinômio, vc só pode somar os termos que tem o mesmo grau, 2x³ + 5x³ = 7x³, no caso vc vai somar cada coeficiente de cada polinômio que tiver grau igual e o grau em cada polinômio que não tiver um grau semelhante só vai ser adicionado na lista e não somado e adicionado.
