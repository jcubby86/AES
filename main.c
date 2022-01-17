#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const unsigned char sbox[] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

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


unsigned char sboxVal(unsigned char in){
	unsigned char x = in >> 4;
	unsigned char y = in << 4;
	y = y >> 4;
	return sbox[(x * 16) + y];
}

void subBytes(unsigned char stateMatrix[]){
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < Nb; col++){
			stateMatrix[(row * Nb) + col] = sboxVal(stateMatrix[(row * Nb) + col]);
		}
	}
}

void shiftRows(unsigned char stateMatrix[]){
	for (int i = 1; i < 4; i++){
		int row = i * Nb;
		unsigned char temp[Nb];
		for (int col = 0; col < Nb; col++){
			int index = row + ((col + i) % Nb);
			temp[col] = stateMatrix[index];
		}
		memcpy(&stateMatrix[row], temp, Nb);
	}
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
    subBytes(stateMatrix);
	shiftRows(stateMatrix);
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
