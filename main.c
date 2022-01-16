#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int INPUT_SIZE = 512;
const int Nb = 4;

unsigned char xtime(unsigned char in){
    unsigned char a = in << 1;
    return a ^ ((in >> 7) * 0x1b);
}

unsigned char ffMultiply(unsigned char a, unsigned char b){
    unsigned char out = 0;
    unsigned char x = a;
    unsigned char pow = 1;
    for (int i = 0; i < 8; i++){
        if (pow & b){
            out ^= x;
        }
        x = xtime(x);
        pow *= 2;
    }
    return out;
}

void mixColumns(unsigned char stateMatrix[]){
    for (int col = 0; col < Nb; col++){
        unsigned char x1[4];
        unsigned char x2[4];
        unsigned char x3[4];
        for (int i = 0; i < 4; i++){
            x1[i] = stateMatrix[(i * Nb) + col];
            x2[i] = xtime(x1[i]);
            x3[i] = x1[i] ^ x2[i];
        }
        stateMatrix[0 + col] =          x2[0] ^ x3[1] ^ x1[2] ^ x1[3];
        stateMatrix[Nb  + col] =        x1[0] ^ x2[1] ^ x3[2] ^ x1[3];
        stateMatrix[(Nb*2)  + col] =    x1[0] ^ x1[1] ^ x2[2] ^ x3[3];
        stateMatrix[(Nb*3)  + col] =    x3[0] ^ x1[1] ^ x1[2] ^ x2[3];

    }

}

void printState(unsigned char stateMatrix[]){
    for (int row = 0; row < 4; row++){    
        for (int col = 0; col < Nb; col++){
            printf("%02x ", stateMatrix[(Nb* row)  + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void cipher(unsigned char stateMatrix[], unsigned char key[]){
    printState(stateMatrix);
    mixColumns(stateMatrix);
    printState(stateMatrix);
}

void toHex(unsigned char in[], unsigned char out[]){
    for (int i = 0; i < 16; i++){
        unsigned char hex[2];
        memcpy(hex, &in[i*3], 2);
        out[i] = (unsigned char) strtol(hex, NULL, 16);
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("usage: %s [-x] <file.txt>\n", argv[0]);
        exit(1);
    }

    FILE *fp;
    unsigned char str[INPUT_SIZE];
    unsigned char beginState[16];

    /* opening file for reading */
    fp = fopen(argv[argc-1] , "r");
    if(fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    if(fgets(str, 60, fp) == NULL) {
        perror("Error reading file");
        exit(1);
    }
    fclose(fp);

    if (argc == 3){
        toHex(str, beginState);
    } else {
        memcpy(beginState, str, 16);
    }

    printf("%s\n", beginState);
    cipher(beginState, NULL);

}