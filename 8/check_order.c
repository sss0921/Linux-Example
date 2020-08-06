#include <stdio.h>

typedef union {
	unsigned short int value;
	unsigned char byte[2];
} to;

int main(int agrc, char *agrv[])
{
	to typeorder;
	typeorder.value = 0xabcd;

	if(typeorder.byte[0] == 0xcd && typeorder.byte[1] == 0xab) {
		printf("Low endian byte order byte[0]:0x%x,byte[1]:0x%x\n",typeorder.byte[0], typeorder.byte[1]);
	}

	if(typeorder.byte[0] == 0xab && typeorder.byte[1] == 0xcd) {
		printf("Hight endian byte order byte[0]:0x%x,byte[1]:0x%x\n", typeorder.byte[0], typeorder.byte[1]);	
	}

	return 0;
}
