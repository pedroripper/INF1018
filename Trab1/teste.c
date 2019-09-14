#include <stdio.h>
#include "bigint.h"

int main(void){
	int i;
	BigInt res;

	//Teste de big_val
	printf("TESTE DE big_val:\n");
	printf("Signed long: %02x\n", 10);
	big_val(res, 10);
	printf("Extendido para 128 bits:\n");
	for(i = 0; i < 16; i ++)
		printf("%02x ", res[i]);
	printf("\n");
	printf("TESTE DE big_val:\n");
	printf("Signed long: %02x\n", -5);
	big_val(res, -5);
	printf("Extendido para 128 bits:\n");
	for(i = 0; i < 16; i ++)
		printf("%02x ", res[i]);
	printf("\n");


	return 0;
}