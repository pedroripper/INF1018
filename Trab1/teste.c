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
	BigInt neg5 = {0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	BigInt negA = {0xAE, 0x01, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
	BigInt a = {0xAE, 0x01, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt sumA = {0x01, 0x01, 0x01, 0x01, 0x11, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt sumB = {0x01, 0x01, 0x01, 0x01, 0x11, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


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
	printf("SHIFT LEFT 16:\n");
	big_shl(res, a, 16);
	printRes(res);


	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	//Teste de big_shr
	printf("TESTE DE big_shr:\n");
	printf("Valor de 'a':\n");
	printRes(a);
	printf("SHIFT RIGHT LOGICO 7:\n");
	big_shr(res, a, 7);
	printRes(res);



	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	//Teste de big_sar
	printf("TESTE DE big_sar:\n");
	printf("Valor de 'a':\n");
	printRes(negA);
	printf("SHIFT RIGHT ARITMETICO 17:\n");
	big_sar(res, negA, 17);
	printRes(res);



	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	//Teste de big_comp2
	printf("TESTE DE big_comp2:\n");
	printf("Valor de 'a':\n");
	printRes(neg5);
	printf("-a:\n");
	big_comp2(res, neg5);
	printRes(res);



	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	printf("TESTE DE big_sum:\n");
	printf("Valor de 'a':\n");
	printRes(sumA);
	printf("Valor de 'b':\n");
	printRes(sumB);
	big_sum(res, sumA, sumB);
	printRes(res);



	return 0;
}
