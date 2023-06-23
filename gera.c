/* DavidWolff 1920468 Turma 3WB */
/* João Pedro Nascimento 2210028 Turma 3WB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera.h"

#define MAX_LINHAS 30

unsigned char *codigo;
int i;

typedef struct pulo {
    int posCodigo;
    int destino;
    int prox;
} Pulo;

void registraVarLocal(int n, int linha) {
    codigo[i++] = 0xff - 4 * n + 1;
}

void opera(char op, char var1, char var2, int idx0, int idx1, int idx2, int linha) {
    if (var1 == '$' && var2 == '$') {
        codigo[i++] = 0xb8;
        *((int*)&codigo[i]) = idx1; i += 4;
        if (op == '+') {
            codigo[i++] = 0x05;
            *((int*)&codigo[i]) = idx2; i += 4;
        }
        else if (op == '-') {
            codigo[i++] = 0x83;
            codigo[i++] = 0xe8;
            *((int*)&codigo[i]) = idx2; i += 4;
            i++;
        }
        else { // op == '*'
            codigo[i++] = 0x6b;
            codigo[i++] = 0xc0;
            *((int*)&codigo[i]) = idx2; i += 1;
        }
    }
    else if (var1 == 'v' && var2 == '$') {   
        codigo[i++] = 0x8b;
        codigo[i++] = 0x45;
        registraVarLocal(idx1, linha);
        if (op == '+') {
            codigo[i++] = 0x83;
            codigo[i++] = 0xc0;
        }
        else if (op == '-') {
            codigo[i++] = 0x83;
            codigo[i++] = 0xe8;
        }
        else {
            codigo[i++] = 0x6b;
            codigo[i++] = 0xc0;
        }
        *((int*)&codigo[i]) = idx2; i += 1;
    }
    else if (var1 == '$' && var2 == 'v') {
        codigo[i++] = 0xb8;
        *((int*)&codigo[i]) = idx1; i += 4;
        if (op == '+') {
            codigo[i++] = 0x03;
        }
        else if (op == '-') {
            codigo[i++] = 0x2b;
        }
        else {
            codigo[i++] = 0x0f;
            codigo[i++] = 0xaf;
        }
        codigo[i++] = 0x45;
        registraVarLocal(idx2, linha);
    }
    else if (var1 == 'v' && var2 == 'v') {
        codigo[i++] = 0x8b;
        codigo[i++] = 0x45;
        registraVarLocal(idx1, linha);
        if (op == '+') {
            codigo[i++] = 0x03;
        }
        else if (op == '-') {
            codigo[i++] = 0x2b;
        }
        else {
            codigo[i++] = 0x0f;
            codigo[i++] = 0xaf;
        }
        codigo[i++] = 0x45;
        registraVarLocal(idx2, linha);
    }
    codigo[i++] = 0x89;
    codigo[i++] = 0x45;
    registraVarLocal(idx0, linha);
    return;
}

funcp gera(FILE* f, unsigned char codigo[]) {
    funcp cod;
    char c;
    int pos, linha = 1, numPulos = 0;
    long int destino, prox, endereco[MAX_LINHAS];
    Pulo pulos[MAX_LINHAS];
    i = 0;

    codigo[i++] = 0x55; codigo[i++] = 0x48; codigo[i++] = 0x89; codigo[i++] = 0xe5;
    codigo[i++] = 0x48; codigo[i++] = 0x83; codigo[i++] = 0xec; codigo[i++] = 0x20;

    while ((c = fgetc(f)) != EOF) {

        endereco[linha - 1] = (long)(&codigo[i]);
        switch (c) {
            case 'r': {
                char var0;
                int idx0;
                fscanf(f, "et %c%d", &var0, &idx0);
                switch (var0) {
                    case '$': {
                        codigo[i++] = 0xb8;
                        *((int*)&codigo[i]) = idx0; i += 4;
                        break;
                    }
                    case 'v': {
                        codigo[i++] = 0x8b;
                        codigo[i++] = 0x45;
                        registraVarLocal(idx0, linha);
                        break;
                    }
                }
                codigo[i++] = 0xc9;
                codigo[i++] = 0xc3;
                printf("%d ret %c%d\n", linha, var0, idx0);
                break;
            }
            case 'v': {
                char var0 = c, c0, var1;
                int idx0, idx1;
                fscanf(f, "%d %c", &idx0, &c0);
                switch (c0) {
                    case '<': {
                        fscanf(f, " %c%d", &var1, &idx1);
                        switch (var1) {
                            case '$': {
                                codigo[i++] = 0xc7;
                                codigo[i++] = 0x45;
                                registraVarLocal(idx0, linha);
                                *((int*)&codigo[i]) = idx1; i += 4;
                                break;
                            }
                            case 'v': {
                                codigo[i++] = 0x44;
                                codigo[i++] = 0x8b;
                                codigo[i++] = 0x55;
                                registraVarLocal(idx1, linha);
                                codigo[i++] = 0x44;
                                codigo[i++] = 0x89;
                                codigo[i++] = 0x55;
                                registraVarLocal(idx0, linha);
                                break;
                            }
                            case 'p': {
                                codigo[i++] = 0x89;
                                switch (idx1) {
                                    case 1:
                                        codigo[i++] = 0x7d;
                                        break;
                                    case 2:
                                        codigo[i++] = 0x75;
                                        break;
                                    case 3:
                                        codigo[i++] = 0x55;
                                        break;
                                }
                                registraVarLocal(idx0, linha);
                                break;
                            }
                        }
                        printf("%d %c%d < %c%d\n", linha, var0, idx0, var1, idx1);
                        break;
                    }
                    case '=': {
                        char var2, op;
                        int idx2;
                        fscanf(f, " %c%d %c %c%d", &var1, &idx1, &op, &var2, &idx2);
                        opera(op, var1, var2, idx0, idx1, idx2, linha);
                        printf("%d %c%d = %c%d %c %c%d\n", linha, var0, idx0, var1, idx1, op, var2, idx2);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 'i': {
                char var0;
                int idx0, n;
                fscanf(f, "flez %c%d %d", &var0, &idx0, &n);
                codigo[i++] = 0x7e;
                pulos[numPulos].posCodigo = i;
                pulos[numPulos].destino = n;
                pulos[numPulos++].prox = linha+1;
                for (int j = 0; j < 4; j++)
                    codigo[i++] = 0x00;
                i++;
                printf("%d iflez %c%d %d\n", linha, var0, idx0, n);
                break;
            }
            default:
                break;
        }
        linha++;
        fscanf(f, " ");
    }

    for (int j = 0; j < numPulos; j++) {
        pos = pulos[j].posCodigo;
        destino = endereco[pulos[j].destino-1];
        prox = endereco[pulos[j].prox - 1];
        *((int*)&codigo[pos]) = (int)(destino - prox);
    }

    cod = (funcp)codigo;
    
    return cod;
}