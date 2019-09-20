#include <stdio.h>
#include "bigint.h"

void printRes(BigInt res){
/*Imprime a resposta da questao*/
	for(int i = 15; i >= 0; i --)
		printf("%02x ", res[i]);
	printf("\n");
}

int main(void){

	BigInt res; // Variavel resposta
	
	/*Variaveis Teste*/
	BigInt subA = {0x80, 0x04, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt subB = {0x70, 0x03, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt one = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
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
	printRes(one);
	printf("-a:\n");
	big_comp2(res, one);
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




	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");

	printf("TESTE DE big_sub:\n");
	printf("Valor de 'a':\n");
	printRes(subA);
	printf("Valor de 'b':\n");
	printRes(subB);
	big_sub(res, subA, subB);
	printRes(res);


	return 0;
}
