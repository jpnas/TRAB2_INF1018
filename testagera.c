

#include <stdlib.h>
#include <string.h>
#include "gera.h"

int testa_gera (char nome[], unsigned char codigo[]){
    FILE *f = fopen(nome, "r");
    if(f == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    if (gera(f, codigo) != NULL){
        funcp funcaoSimples = gera(f, codigo);
        return funcaoSimples(1, 2, 3);
    }
    else{
        return -1;
    }
    return 0;
}

int main(void){
    unsigned char codigo[1000];

    // Caso de retornos simples de variáveis e atribuição de parâmetros
    if (testa_gera("simples.txt", codigo) == 4){
        printf("OK -> retorno e atribuição de uma variável (v1)\n");
    }else{
        printf("ERRO -> retorno e atribuição de uma variável (v1)\n");
    }
    
    if (testa_gera("testes/simples2.txt", codigo) == 4){
        printf("OK -> retorno e atribuição de uma variável (v1)\n");
    }else{
        printf("ERRO -> retorno e atribuição de uma variável (v1)\n");
    }

    if (testa_gera("testes/simples3.txt", codigo) == 4){
        printf("OK -> retorno e atribuição de uma variável (v3)\n");
    }else{
        printf("ERRO -> retorno e atribuição de uma variável (v3)\n");
    }
    
    if (testa_gera("testes/simples4.txt", codigo) == 4){
        printf("OK -> retorno e atribuição de uma variável (v4)\n");
    }else{
        printf("ERRO -> retorno e atribuição de uma variável (v4)\n");
    }

    if (testa_gera("testes/simples5.txt", codigo) == 4){
        printf("OK -> retorno e atribuição de uma variável (v5)\n");
    }else{
        printf("ERRO -> retorno e atribuição de uma variável (v5)\n");
    }

    if (testa_gera("testes/simples6.txt", codigo) == 1){
        printf("OK -> retorno de uma constante positiva\n");
    }else{
        printf("ERRO -> retorno de uma constante positiva\n");
    }

    if (testa_gera("testes/simples7.txt", codigo) == -1){
        printf("OK -> retorno de uma constante negativa\n");
    }else{
        printf("ERRO -> retorno de uma constante negativa\n");
    }
    
    if (testa_gera("testes/simples8.txt", codigo) == 0){
        printf("OK -> retorno de uma constante igual a 0\n");
    }else{
        printf("ERRO -> retorno de uma constante igual a 0\n");
    }

    // Atribuição variavel = parametro
    if (testa_gera("testes/simples9.txt", codigo) == 1){
        printf("OK -> variavel = parametro\n");
    }else{
        printf("ERRO -> variavel = parametro\n");
    }

    // Atribuição variavel = varivavel 
    if (testa_gera("testes/simples10.txt", codigo) == 10){
        printf("OK -> variavel = variavel\n");
    }else{
        printf("ERRO -> variavel = variavel\n");
    }

    // Soma 
    if (testa_gera("testes/simples11.txt", codigo) == 3){
        printf("OK -> variavel = variavel + variavel\n");
    }else{
        printf("ERRO -> variavel = variavel + variavel\n");
    }

    if (testa_gera("testes/simples12.txt", codigo) == 3){
        printf("OK -> variavel = variavel + constante\n");
    }else{
        printf("ERRO -> variavel = variavel + constante\n");
    }
    
    if (testa_gera("testes/simples13.txt", codigo) == 3){
        printf("OK -> variavel = constante + variavel\n");
    }else{
        printf("ERRO -> variavel = constante + variavel\n");
    }

    // Subtração 
    if (testa_gera("testes/simples14.txt", codigo) == 0){
        printf("OK -> variavel = variavel - variavel\n");
    }else{
        printf("ERRO -> variavel = variavel - variavel\n");
    }

    if (testa_gera("testes/simples15.txt", codigo) == 0){
        printf("OK -> variavel = variavel - constante\n");
    }else{
        printf("ERRO -> variavel = variavel - constante\n");
    }
    
    if (testa_gera("testes/simples16.txt", codigo) == 1){
        printf("OK -> variavel = constante - variavel\n");
    }else{
        printf("ERRO -> variavel = constante - variavel\n");
    }

    // Multiplicação 
    if (testa_gera("testes/simples17.txt", codigo) == 1){
        printf("OK -> variavel = variavel * variavel\n");
    }else{
        printf("ERRO -> variavel = variavel * variavel\n");
    }

    if (testa_gera("testes/simples18.txt", codigo) == 2){
        printf("OK -> variavel = variavel * constante\n");
    }else{
        printf("ERRO -> variavel = variavel * constante\n");
    }
    
    if (testa_gera("testes/simples19.txt", codigo) == 3){
        printf("OK -> variavel = constante * variavel\n");
    }else{
        printf("ERRO -> variavel = constante * variavel\n");
    }

    // Desvio 
    if (testa_gera("testes/simples20.txt", codigo) == 0){
        printf("OK -> Desvio para linha depois do if\n");
    }else{
        printf("ERRO -> Desvio para linha depois do if\n");
    }

    if (testa_gera("testes/simples21.txt", codigo) == 1){
        printf("OK -> Não desvia, pois é maior que 0\n");
    }else{
        printf("ERRO -> Não desvia, pois é maior que 0\n");
    }

    // Função Recursiva a partir de parâmetros (p1, p2, p3)
    if (testa_gera("testes/simples22.txt", codigo) == 24){
        printf("OK -> Desvio para linha anterior (loop) -> Função Fatorial\n");
    }else{
        printf("ERRO -> Desvio para linha anterior (loop) -> Função Fatorial\n");
    }

    // Teste para quando exceder número de variáveis ou parâmetros
    if (testa_gera("testes/simples23.txt", codigo) == -1){
        printf("OK -> Retorno NULL quando passa de 5 variáveis locais\n");
    }else{
        printf("ERRO -> Retorno NULL quando passa de 5 variáveis locais\n");
    }
    if (testa_gera("testes/simples24.txt", codigo) == -1){
        printf("OK -> Retorno NULL quando passa de 3 variáveis locais\n");
    }else{
        printf("ERRO -> Retorno NULL quando passa de 3 variáveis locais\n");
    }

    // Teste para quando uma operação não está de acordo com a Linguagem Simples
    if (testa_gera("testes/simples25.txt", codigo) == -1){
        printf("OK -> Retorno NULL quando operação não está de acordo com a Linguagem Simples\n");
    }else{
        printf("ERRO -> Retorno NULL quando operação não está de acordo com a Linguagem Simples\n");
    }

    // Teste para quando é chamada uma função com várias operações
    if (testa_gera("testes/simples26.txt", codigo) == -3){
        printf("OK -> Função que utiliza várias variáveis e realiza várias operações\n");
    }else{
        printf("ERRO -> Função que utiliza várias variáveis e realiza várias operações\n");
    }
    return 0;
}