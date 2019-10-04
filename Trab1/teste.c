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
	BigInt negA = {0xAE, 0x01, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80};
	BigInt a = {0xAE, 0x01, 0x11, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt sumA = {0x01, 0x01, 0x01, 0x01, 0x11, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt sumB = {0x01, 0x01, 0x01, 0x01, 0x11, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt mulA = {0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt mulB = {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	BigInt mulC = {0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	//Teste de big_val
	printf("TESTE DE big_val:\n");
	printf("Signed long: %02lx\n", 9223372036854775807);
	big_val(res, 9223372036854775807);
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

	printf("\n");
	printf("Valor de 'a':\n");
	printRes(a);
	printf("SHIFT LEFT 7:\n");
	big_shl(res, a, 7);
	printRes(res);
	printf("SHIFT LEFT 64:\n");
	big_shl(res, a, 64);
	printRes(res);
	printf("SHIFT LEFT 128:\n");
	big_shl(res, a, 128);
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
	printf("SHIFT RIGHT LOGICO 16:\n");
	big_shr(res, a, 16);
	printRes(res);
	printf("SHIFT RIGHT LOGICO 128:\n");
	big_shr(res, a, 128);
	printRes(res);


	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");


	//Teste de big_sar
	printf("TESTE DE big_sar:\n");
	printf("Valor de 'a':\n");
	printRes(negA);
	printf("SHIFT RIGHT ARITMETICO 15:\n");
	big_sar(res, negA, 15);
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
	printf("RES:\n");
	big_sum(res, sumA, sumB);
	printRes(res);

	printf("TESTE DE big_sum:\n");
	printf("Valor de 'a':\n");
	printRes(sumA);
	printf("Valor de 'b':\n");
	printRes(negA);
	printf("RES:\n");
	big_sum(res, sumA, negA);
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
	printf("RES: :\n");
	printRes(res);


	printf("\n\n\n");
	printf("/***************************/\n");
	printf("\n\n\n");


	printf("TESTE DE big_vmul:\n");
	printf("BigInt: %02d\n", 250);
	printRes(mulA);
	printf("BigInt: %02d\n", 3);
	printRes(mulB);
	printf("big_vmul: ");
	big_mul(res,mulA,mulB);
	printRes(res);
	
	printf("\nBigInt: %02d\n", -5);
	printRes(mulC);
	printf("BigInt: %02d\n", 3);
	printRes(mulB);
	printf("big_vmul: ");
	big_mul(res,mulC,mulB);
	printRes(res);
	
	printf("\nBigInt: %02d\n", 250);
	printRes(mulA);
	printf("BigInt: %02d\n", -5);
	printRes(mulC);
	printf("big_vmul: ");
	big_mul(res,mulA,mulC);
	printRes(res);
	
	printf("\nBigInt: %02d\n", -5);
	printRes(mulC);
	printf("BigInt: %02d\n", -5);
	printRes(mulC);
	printf("big_vmul: ");
	big_mul(res,mulC,mulC);
	printRes(res);


	return 0;
}
