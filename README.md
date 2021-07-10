<h1 align="center">
  <br>
  <a href="#"><img src="assets/old-computer.png" alt="Just a simple icon" width="80"></a>
  <br>
  Ponto Flutuante
  <br>
</h1>

# Descrição
O programa simula um circuito elétrico RLC em Série e em Paralelo (Resistor Indutor Capacitor) através de métodos iterativos.

```
 ___________________________________
|       _                _ _        |
|      (_)              (_) |       |
|   ___ _ _ __ ___ _   _ _| |_ ___  |
|  / __| | '__/ __| | | | | __/ __| |
| | (__| | | | (__| |_| | | |_\__ \ |
|  \___|_|_|  \___|\__,_|_|\__|___/ |
|___________________________________|


O programa calcula a resposta natural de um circuito RLC série ou paralelo

            R       L      C
   _____/\/\/\/\___⌒⌒⌒____| |____
  |                       | |    |
__|__                            |
 ---  V                          |
  |                              |
  |                              |
  |______________________________|
                SERIE

   ______________________________
  |          |        |          |
  |          \        |_         |
__|__        /         _)       ---
 ---  V      \ R       _)  L    --- C
  |          /         _)        |
  |          \         |         |
  |__________|_________|_________|
              PARALELO

```

Além disso, simula como seriam essas contas em uma máquina com configurações definidas no inicio do programa:

- Mantissa
- Limite inferior e superior
- Método de aproximação

A resposta do circuito é encontrada como uma expressão algébrica no final da execução do programa:
```
A resposta do sistema é:


i(t)=-1.74157e^-10t + -5.61798e^-1.99t
```

## Como usar o programa?
Abaixo tem uma entrada de exemplo:

```c
_____________________________________

O circuito está em série ou paralelo?
1) Série 
2) Paralelo

Opção: 1

Insira o valor de R: 12
Insira o valor de L: 1
Insira o valor de C: 0.05

Insira o valor de x(0): 5
Insira o valor de x'(0): 4
_____________________________________

O método usado é Newton ou Secantes? 
1) Newton 
2) Secantes
Opção: 1
_____________________________________

Agora defina os parâmetros da máquina!

Insira a mantissa da máquina: 3

Defina os limites do expoente:
Insira o limite inferior: -3
Insira o limite superior: 3
_____________________________________

O tipo de aproximacao é Truncamento ou Arrendondamento? 
1) Truncamento 
2) Arrendondamento
Opção: 1
____________________________________

O polinômio característico é: D²+12D+20
_____________________________________

Insira o intervalo da primeira raiz [a,b]
a = -15
b = -5

Insira o intervalo da segunda raiz [c,d]
c = -5
d = 0
____________________________________

Insira o valor da precisão E: 0.01
_____________________________________


A solução admite duas raízes reais! O sistema é sobreamortecido
```

O programa ainda exibe uma tabela resumindo o procedimento de como ele encontrou as raízes:

```c
_____________________________________

Raiz 1:
x0 = -10		x0 = -0.1x10^2
x1 = -10		x1 = -0.1x10^2

Raíz real x = -10
Raíz encontrada x = -10
_____________________________________

Raiz 2:
x0 = -1.25		    x0 = -0.125x10^1
x1 = -1.94079		x1 = -0.194x10^1
x2 = -1.99957		x2 = -0.199x10^1
x3 = -2		        x3 = -0.199x10^1

Raíz real x = -2
Raíz encontrada x = -1.99

A resposta do sistema é:


i(t)=-1.74157e^-10t + -5.61798e^-1.99t
```

Para compilar e executar um programa destes, basta executar o comando com o nome de arquivo, com o terminal dentro da pasta `game`:

```g++ main.cpp && ./a.out```

> O comando acima precisa do compilador g++ instalado na máquina, se você não sabe o que é isso, comece lendo sobre [por aqui](https://pt.wikipedia.org/wiki/GNU_Compiler_Collection)

## Autores
- [Maurício Taffarel](https://github.com/taffarel55/)
- [Breno Amin](https://github.com/brenoamin)
- [Geraldo Júnior](https://github.com/GeraldinJr)

## Contribuindo
Contribuições são o que tornam a comunidade de código aberto um lugar incrível para aprender, inspirar e criar. Todas as contribuições que você fizer são muito bem vindas! 

Se quiser "fortalecer" aí, pode abrir o pull request!! :heart_eyes:

## Licença
[GPL-3.0 License ](https://github.com/taffarel55/Interpolador/blob/master/LICENSE)

<div>Ícones feitos por <a href="https://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/br/" title="Flaticon">www.flaticon.com</a></div>
