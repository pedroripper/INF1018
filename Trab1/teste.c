#include <stdio.h>
#include "bigint.h"

void printRes(BigInt res){
/*Imprime a resposta da questao*/
	for(int i = 15; i >= 0; i --)
		printf("%02x ", res[i]);
	printf("\n");
}

int main(void){
	BigInt res;
	BigInt a = {0xAE, 0x01, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	//Teste de big_val
	printf("TESTE DE big_val:\n");
	printf("Signed long: %02x\n", 10);
	big_val(res, 10);
	printf("Extendido para 128 bits:\n");
	printRes(res);
	printf("TESTE DE big_val:\n");
	printf("Signed long: %02x\n", -5);
	big_val(res, -5);
	printf("Extendido para 128 bits:\n");
	printRes(res);

	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	//Teste de big_shl
	printf("TESTE DE big_shl:\n");
	printf("Valor de 'a':\n");
	printRes(a);
	printf("SHIFT LEFT 1:\n");
	big_shl(res, a, 1);
	printRes(res);
	printf("SHIFT LEFT 3:\n");
	big_shl(res, a, 3);
	printRes(res);

	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	//Teste de big_shr
	printf("TESTE DE big_shr:\n");
	printf("Valor de 'a':\n");
	printRes(a);
	printf("SHIFT LEFT 1:\n");
	big_shr(res, a, 1);
	printRes(res);
	printf("SHIFT LEFT 3:\n");
	big_shr(res, a, 3);
	printRes(res);



	return 0;
}