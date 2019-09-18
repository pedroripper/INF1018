/* Gabriel Arantes Cortines Coelho 1611860 3WB */
/* Pedro da Silveira Carvalho Ripper 1910954 3WB */

#include <stdio.h>
#include "bigint.h" 
#include <math.h>

/* Funções Auxiliares */

void printtest(BigInt res){
/*Imprime a resposta da questao*/
	for(int i = 15; i >= 0; i --)
		printf("%02x ", res[i]);
	printf("\n");
}

void placeBits(BigInt res, int n){
	int e = 0;
	int nBytes = n/8;
	int nBits = n%8;
	while(nBits){
		res[15-nBytes] += pow(2,7-e);
		e++;
		nBits --;
	}
	while(nBytes){
		res[16-nBytes] = 0XFF;
		nBytes --; 
	}
}

void shiftR(BigInt res, BigInt a, int n){
	int nBytes = n/8;
	for(int i = 0; i+nBytes < 16; i ++){
		res[i] = a[i+nBytes];
	}
	while(nBytes){
		res[16-nBytes] = 0x00;
		nBytes --; 
	}
}


void storeLong(void *p, long n, BigInt res){
 /*passa o signed int para os primeiros 8 índices do BigInt*/
	unsigned char *p1 = p;
	unsigned char *p2 = res;
	int i = 0;
	while(n--){
		*p2 = *p1;
		p1++; p2 ++;
		i ++;
	}
}

/* Atribuição (com extensão) */
void big_val (BigInt res, long val){
	storeLong(&val, sizeof(val), res);
	int i;
	unsigned char *p = res+8;
	//checagem se val é positivo ou negativo
	if(val & 0x80000000){
		for(i = 8; i < 16; i ++){
			*p = 0xFF;
			p ++;
		}
	}
	else{
		for(i = 8; i < 16; i ++){
			*p = 0x00;
			p ++;
		}
	}
}



/* Operações Aritméticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a);

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b);

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n){
	int i, e, ant = 0;
	long val;

	for(i = 0; i < 16; i ++){
		val = a[i];
		for(e=0;e<n;e++){val = val*2;}
		val+=ant;
		res[i] = val%256;
		ant = val/256;
	}
	return;
}

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n){
	shiftR(res, a, n);
	int i, e, ant = 0, prox = 0;
	unsigned char val;
	for(i = 15; i >= 0	; i --){
		val = res[i];
		for(e=0;e<n%8;e++){
			prox += (val%2)*pow(2,7-e);
			//printf("valor do prox %d : %d\n", i, prox);
			val = val>>1;
		}
		val = val | ant;
		res[i] = val;  
		ant = prox/(pow(2,(n%8)-1));
		prox = 0;

 }
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n){
	if(a[15] & 0x80){
		shiftR(res, a, n);
		int i, e, ant = 0, prox = 0;
		unsigned char val;
		for(i = 15; i >= 0	; i --){
			val = res[i];
			for(e=0;e<n%8;e++){
				prox += (val%2)*pow(2,7-e);
				val = val>>1;
			}
			val = val | ant;
			res[i] = val;  
			ant = prox/(pow(2,(n%8)-1));
			prox = 0;

 			}
 			placeBits(res, n);
	}
	else{
		big_shr(res,a,n);
	}
}
