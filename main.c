#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const __uint8_t sbox[] = {      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
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
                                0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  };

const __uint8_t invSbox[] = {   0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
                                0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
                                0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
                                0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
                                0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
                                0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
                                0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
                                0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
                                0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
                                0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
                                0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
                                0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
                                0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
                                0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
                                0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
                                0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  };

const int INPUT_SIZE = 512;
const int Nb = 4;
int Nk;
int Nr;
int VERBOSE = 0;
int true = 1;

__uint8_t sboxVal(__uint8_t in){
	__uint8_t x = in >> 4;
	__uint8_t y = in << 4;
	y = y >> 4;
	return sbox[(x * 16) + y];
}

__uint8_t invSboxVal(__uint8_t in){
	__uint8_t x = in >> 4;
	__uint8_t y = in << 4;
	y = y >> 4;
	return invSbox[(x * 16) + y];
}

__uint32_t word(__uint8_t a, __uint8_t b, __uint8_t c, __uint8_t d){
    return (a << 24) | (b << 16) | (c << 8) | d;
}

__uint32_t subWord(__uint32_t in){
    return word(sboxVal(in >> 24), sboxVal(in >> 16), sboxVal(in >> 8), sboxVal(in));
}

__uint32_t rotWord(__uint32_t in){
    __uint8_t temp = in >> 24;
    return (in << 8) | temp;
}

__uint8_t xtime(__uint8_t in){
    __uint8_t a = in << 1;
    return a ^ ((in >> 7) * 0x1b);
}

__uint8_t ffMultiply(__uint8_t a, __uint8_t b){
    __uint8_t out = 0;
    __uint8_t x = a;
    __uint8_t pow = 1;
    for (int i = 0; i < 8; i++){
        if (pow & b){
            out ^= x;
        }
        x = xtime(x);
        pow *= 2;
    }
    return out;
}

void subBytes(__uint8_t stateMatrix[]){
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < Nb; col++){
			stateMatrix[(row * Nb) + col] = sboxVal(stateMatrix[(row * Nb) + col]);
		}
	}
}

void invSubBytes(__uint8_t stateMatrix[]){
	for (int row = 0; row < 4; row++){
		for (int col = 0; col < Nb; col++){
			stateMatrix[(row * Nb) + col] = invSboxVal(stateMatrix[(row * Nb) + col]);
		}
	}
}

void shiftRows(__uint8_t stateMatrix[]){
	for (int i = 1; i < 4; i++){
		int row = i * Nb;
		__uint8_t temp[Nb];
		for (int col = 0; col < Nb; col++){
			int index = row + ((col + i) % Nb);
			temp[col] = stateMatrix[index];
		}
		memcpy(&stateMatrix[row], temp, Nb);
	}
}

void invShiftRows(__uint8_t stateMatrix[]){
	for (int i = 1; i < 4; i++){
		int row = i * Nb;
		__uint8_t temp[Nb];
		for (int col = 0; col < Nb; col++){
			int index = row + (((col + Nb) - i) % Nb);
			temp[col] = stateMatrix[index];
		}
		memcpy(&stateMatrix[row], temp, Nb);
	}
}

void mixColumns(__uint8_t stateMatrix[]){
    for (int col = 0; col < Nb; col++){
        __uint8_t c[4];
        for (int i = 0; i < 4; i++){
            c[i] = stateMatrix[(i * Nb) + col];
        }
        stateMatrix[0 + col] =          ffMultiply(c[0], 2) ^ ffMultiply(c[1], 3) ^ c[2] ^ c[3];
        stateMatrix[Nb  + col] =        ffMultiply(c[1], 2) ^ ffMultiply(c[2], 3) ^ c[3] ^ c[0];
        stateMatrix[(Nb*2)  + col] =    ffMultiply(c[2], 2) ^ ffMultiply(c[3], 3) ^ c[0] ^ c[1];
        stateMatrix[(Nb*3)  + col] =    ffMultiply(c[3], 2) ^ ffMultiply(c[0], 3) ^ c[1] ^ c[2];
    }
}

void invMixColumns(__uint8_t stateMatrix[]){
    for (int col = 0; col < Nb; col++){
        __uint8_t c[4];
        for (int i = 0; i < 4; i++){
            c[i] = stateMatrix[(i * Nb) + col];
        }
        stateMatrix[0 + col] =          ffMultiply(c[0], 0x0e) ^ ffMultiply(c[1], 0x0b) ^ ffMultiply(c[2], 0x0d) ^ ffMultiply(c[3], 0x09);
        stateMatrix[Nb  + col] =        ffMultiply(c[1], 0x0e) ^ ffMultiply(c[2], 0x0b) ^ ffMultiply(c[3], 0x0d) ^ ffMultiply(c[0], 0x09);
        stateMatrix[(Nb*2)  + col] =    ffMultiply(c[2], 0x0e) ^ ffMultiply(c[3], 0x0b) ^ ffMultiply(c[0], 0x0d) ^ ffMultiply(c[1], 0x09);
        stateMatrix[(Nb*3)  + col] =    ffMultiply(c[3], 0x0e) ^ ffMultiply(c[0], 0x0b) ^ ffMultiply(c[1], 0x0d) ^ ffMultiply(c[2], 0x09);
    }
}

void addRoundKey(__uint8_t s[], __uint32_t w[], int round){
    for (int c = 0; c < Nb; c++){
        __uint32_t temp = w[(round*Nb)+c];
        __uint32_t col = word(s[c], s[Nb  + c], s[(Nb*2)  + c], s[(Nb*3) + c]);
        // printf("%08x + %08x = %08x\n", col, temp, col ^ temp);
        col ^= temp;

        for (int r = 0; r < 4; r++){
            s[(r * Nb) + c] = *((__uint8_t*)(&col)+(3-r));
        }
    }
}

void printState(int round, char str[], __uint8_t stateMatrix[], int v){
    if (!v) return;
    printf("round[%2d].%s ", round, str);
    for (int row = 0; row < 4; row++){    
        for (int col = 0; col < Nb; col++){
            printf("%02x", stateMatrix[row + (Nb*col)]);
        }
    }
    printf("\n");
}

void printKeySchedule(int round, int displayRound, char str[], __uint32_t w[], int v){
    if (!v) return;
    printf("round[%2d].%s ", displayRound, str);
    for (int i = round*Nb; i < (round+1)*Nb; i++){    
        printf("%08x", w[i]);
    }
    printf("\n");
}

void cipher(__uint8_t stateMatrix[], __uint32_t w[]){
    printState(0, "input", stateMatrix, true);
    addRoundKey(stateMatrix, w, 0);
    printKeySchedule(0, 0, "k_sch", w, VERBOSE);

    for (int round = 1; round < Nr; round++){
        printState(round, "start", stateMatrix, VERBOSE);
        subBytes(stateMatrix);
        printState(round, "s_box", stateMatrix, VERBOSE);
        shiftRows(stateMatrix);
        printState(round, "s_row", stateMatrix, VERBOSE);
        mixColumns(stateMatrix);
        printState(round, "m_col", stateMatrix, VERBOSE);
        addRoundKey(stateMatrix, w, round);
        printKeySchedule(round, round, "k_sch", w, VERBOSE);
    }
    printState(Nr, "start", stateMatrix, VERBOSE);
    subBytes(stateMatrix);
    printState(Nr, "s_box", stateMatrix, VERBOSE);
    shiftRows(stateMatrix);
    printState(Nr, "s_row", stateMatrix, VERBOSE);
    addRoundKey(stateMatrix, w, Nr);
    printKeySchedule(Nr, Nr, "k_sch", w, VERBOSE);
    printState(Nr, "output", stateMatrix, true);
}

void invCipher(__uint8_t stateMatrix[], __uint32_t w[]){
    printState(0, "iinput", stateMatrix, true);
    addRoundKey(stateMatrix, w, Nr);
    printKeySchedule(Nr, 0, "ik_sch", w, VERBOSE);

    for (int round = Nr-1; round > 0; round--){
        printState(Nr-round, "istart", stateMatrix, VERBOSE);
        invShiftRows(stateMatrix);
        printState(Nr-round, "is_row", stateMatrix, VERBOSE);
        invSubBytes(stateMatrix);
        printState(Nr-round, "is_box", stateMatrix, VERBOSE);
        printKeySchedule(round, Nr-round, "ik_sch", w, VERBOSE);
        addRoundKey(stateMatrix, w, round);
        printState(Nr-round, "ik_add", stateMatrix, VERBOSE);
        invMixColumns(stateMatrix);
    }
    printState(Nr, "istart", stateMatrix, VERBOSE);
    invShiftRows(stateMatrix);
    printState(Nr, "is_row", stateMatrix, VERBOSE);
    invSubBytes(stateMatrix);
    printState(Nr, "is_box", stateMatrix, VERBOSE);
    addRoundKey(stateMatrix, w, 0);
    printKeySchedule(0, Nr, "ik_sch", w, VERBOSE);
    printState(Nr, "ioutput", stateMatrix, true);
}

void toHex(__uint8_t in[], __uint8_t out[], int len){
    for (int i = 0; i < len; i++){
        __uint8_t hex[2];
        memcpy(hex, &in[i*2], 2);
        out[i] = (__uint8_t) strtol(hex, NULL, 16);
    }
}

void readFile(__uint8_t str[], __uint8_t filename[]){
    FILE *fp;

    /* opening file for reading */
    fp = fopen(filename , "r");
    if(fp == NULL) {
        __uint8_t err[256];
        sprintf(err, "Error opening file %s", filename);
        perror(err);
        exit(1);
    }
    if(fgets(str, INPUT_SIZE, fp) == NULL) {
        __uint8_t err[256];
        sprintf(err, "Error reading file %s", filename);
        perror(err);
        exit(1);
    }
    fclose(fp);
}

void keyExpansion(__uint8_t key[], __uint32_t w[]){
    __uint32_t temp;
    __uint8_t rcon[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};
    unsigned int i = 0;

    while (i < Nk){
        w[i] = word(key[4*i], key[4*i+1], key[4*i+2], key[4*i+3]);
        i++;
    }
    
    i = Nk;
    while (i < Nb * (Nr + 1)){
        temp = w[i-1];

        if (i % Nk == 0){
            temp = subWord(rotWord(temp)) ^ (rcon[i/Nk] << 24);
        } else if (Nk > 6 && i % Nk == 4){
            temp = subWord(temp);
        } else {
        }
        w[i] = w[i-Nk] ^ temp;
        i++;
    }
}

void transpose(__uint8_t s[]){
    __uint8_t t[4 * Nb];
    for (int row = 0; row < 4; row++){    
        for (int col = 0; col < Nb; col++){
            t[(Nb*col) + row] = s[(Nb* row) + col];
        }
    }
    memcpy(s, t, Nb*4);
}

int main(int argc, char* argv[]){
    if (argc < 4){
        printf("usage: %s [-x] infile {128|192|256} keyfile\n", argv[0]);
        exit(1);
    }
    unsigned int keysize = (unsigned int) strtol(argv[2], NULL, 10);
    if (!(keysize == 128 || keysize == 192 || keysize == 256)){
        printf("usage: %s infile {128|192|256} keyfile [-d]\n", argv[0]);
        exit(1);
    }
    Nk = keysize / 32;
    Nr = Nk + 6;

    __uint8_t str[INPUT_SIZE];

    __uint8_t beginState[4 * Nb];
    readFile(str, argv[1]);

    toHex(str, beginState, 4 * Nb);
    transpose(beginState);

    if (argc == 5 && strcmp("-d", argv[4]) == 0){
        VERBOSE = 1;
    }

    __uint32_t w[Nb * (Nr + 1)];
    __uint8_t key[keysize/8];
    readFile(str, argv[3]);
    toHex(str, key, keysize/8);
    
    keyExpansion(key, w);    

    printf("CIPHER (ENCRYPT):\n");
    cipher(beginState, w);
    printf("\nINVERSE CIPHER (DECRYPT):\n");
    invCipher(beginState, w);
}
