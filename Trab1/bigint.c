/* Nome_do_Aluno1 Matricula Turma */
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
	int i, e, ant = 0;
	unsigned char prox = 0;
	long val;

	for(i = 15; i >= 0; i --){
		val = a[i];
		printf("val antes: %02lx\n", val);
		for(e=0;e<n;e++){
			if(val & 0x0000000000000001){
				prox += 1*pow(2,8-e);
				printf("tamo junto %d\n", prox);
			}
			val = val/2;
		}
		val = val | ant;
		printf("antes da merda acontecer %02lx\n", val);
		res[i] = val;
		printf("valor pra res[%d]: %02x\n", i, res[i]);
		ant = prox;
		prox = 0;
	}
	return;

 
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);
