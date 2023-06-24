/* David Wolff 1920468 Turma 3WB */
/* João Pedro Nascimento 2210028 Turma 3WB */

#include <stdlib.h>
#include <string.h>
#include "gera.h"

int testa_gera(char nome[], unsigned char codigo[]) {
    FILE *f = fopen(nome, "r");
    if(f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    if (gera(f, codigo) != NULL){
        funcp funcaoSimples = gera(f, codigo);
        return funcaoSimples(1, 10, 100);
    }
    else {
        return -1;
    }
    return 0;
}

void execute_test(char* filename, unsigned char codigo[], int expected_value, char* test_message) {
    if (testa_gera(filename, codigo) == expected_value){
        printf("PASSOU - %s\n", test_message);
    }else{
        printf("ERRO - %s\n", test_message);
    }
}

int main(void) {
    unsigned char codigo[1000];

    struct Test {
        char* filename;
        int expected_value;
        char* message;
    };

    struct Test tests[] = {
        {"testes/1.txt", 100, "retorno de um valor inteiro"},
        {"testes/2.txt", -100, "retorno de um valor inteiro negativo"},
        {"testes/3.txt", 5, "atribuição e retorno de um valor inteiro a uma variável"},
        {"testes/4.txt", 3, "atribuição e retorno da soma de um valor inteiro (3) a uma variável"},
        {"testes/5.txt", 40, "multiplicação e retorno de duas variáves"},
        {"testes/6.txt", 1, "atribuição e retorno de um parâmetro à uma variável"},
        {"testes/7.txt", 30, "atribuição de um parâmetro à uma variável e retorno da soma com uma constante"},
        {"testes/8.txt", 2, "atribuição de uma constante à uma variável e retorno da subtração com uma constante"},
        {"testes/9.txt", 5, "atribuição de um parâmetro à uma variável e retorno da multiplicação com uma constante"},
        {"testes/10.txt", 0, "desvio iflez"},
    };

    int num_tests = sizeof(tests) / sizeof(struct Test);

    for (int i = 0; i < num_tests; i++) {
        execute_test(tests[i].filename, codigo, tests[i].expected_value, tests[i].message);
    }

    return 0;
}
