 
/* Gabriel Arantes Cortines Coelho 1611860 3WB */
/* Pedro da Silveira Carvalho Ripper 1910954 3WB */

#include <stdio.h>
#include "bigint.h" 


/* Funções Auxiliares */

void printtest(BigInt res){
/*Imprime a resposta da questao*/
	for(int i = 15; i >= 0; i --)
		printf("%02x ", res[i]);
	printf("\n");
}



void opBits(BigInt res, BigInt a){
	//troca os bytes pelos seus complementos
	int i;
	unsigned char *p = res;
	for(i = 0; i < 16; i ++){
		*p = ~(a[i]);
		p++;

	}
}



void placeBits(BigInt res, int n){
	int e = 0;
	int nBytes = n/8;
	int nBits = n%8;
	while(nBits){
		res[15-nBytes] += pot(2,7-e);
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



/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b){
	char prox = 0;
	short val;
	int i;
	for(i = 0; i < 16; i ++){
		val = a[i] + b[i] + prox;
		res[i] = val;
		prox = val>>8;
	}
}


/* res = -a */
void big_comp2(BigInt res, BigInt a){
	BigInt one = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	opBits(res, a);
	big_sum(res, res, one);
}


/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b){
	BigInt negB;
	big_comp2(negB, b);
	big_sum(res, a, negB);
}

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b){
    int atual, mod = 8;
    BigInt shi, b_c;
    
	if(b[15] & 0x80){big_comp2(b_c,b);}
	else{big_shl(b_c,b,0);}
	
    
    big_val(res, 0);
    for(atual=0;atual<16;atual++){
        if(b_c[atual]&0x01){big_shl(shi,a,0+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x02){big_shl(shi,a,1+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x04){big_shl(shi,a,2+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x08){big_shl(shi,a,3+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x10){big_shl(shi,a,4+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x20){big_shl(shi,a,5+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x40){big_shl(shi,a,6+atual*mod);big_sum(res,res,shi);}
        if(b_c[atual]&0x80){big_shl(shi,a,7+atual*mod);big_sum(res,res,shi);}
    }
    if(b[15] & 0x80){big_comp2(res,res);}
    return;
}


/* Operações de Deslocamento */

/* res = a << n */
/*void big_shl(BigInt res, BigInt a, int n){
	int i, e, ant = 0;
	long val;

	for(i = 0; i < 16; i ++){
		res[i] = a[i];

	}

	while(n>32){
		n-=32;
		big_shl(res,res,32);
	}

	for(i = 0 && n>0; i < 16; i ++){
		val = res[i];
		for(e=0;e<n;e++){val = val*2;}
		val+=ant;
		res[i] = val%256;
		ant = val/256;
	}
	return;
}*/
void big_shl(BigInt res, BigInt a, int n){
	int i, c=0;
	char ant = 0;
	short val;

	if(n>=8){c=n/8;n=n%8;}

	for(i = c;i < 16; i++){
		res[i] = a[i-c];
	}
	for(i = 0;i < c; i++){
		res[i] = 0x00;
	}
	if(n == 0){return;}

	for(i = 0; i < 16; i ++){
		val = (res[i]<<n) + ant;
		res[i] = val;
		ant = val>>8;
	}
	return;
}

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n){
	int i, e, ant = 0, prox = 0;
	unsigned char val;

	shiftR(res, a, n);
	if((n&0x07) == 0)
		return;

	for(i = 15; i >= 0	; i --){
		val = res[i];
		for(e=0;e<(n&0x07);e++){
			prox += (val&0x01)<<(7-e);
			val = val>>1;
		}
	val = val | ant;
	res[i] = val;  
	ant = prox>>((n&0x07)-1); 
	prox = 0;

 }
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n){
	int i, e, ant = 0, prox = 0;
	unsigned char val;
	if(a[15] & 0x80){
		shiftR(res, a, n);
		if((n&0x07) == 0){
			placeBits(res, n);
			return;
			}

		for(i = 15; i >= 0	; i --){
			val = res[i];
			for(e=0;e<(n&0x07);e++){
				prox += (val&0x01)<<(7-e);
				val = val>>1;
			}
			val = val | ant;
			res[i] = val;  
			ant = prox>>((n&0x07)-1);
			prox = 0;

	 		}
 			placeBits(res, n);
	}
	else{
		big_shr(res,a,n);
	}
}
