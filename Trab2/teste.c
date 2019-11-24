#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cria_func.h"



void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

void libera_func (void* func);

typedef int (*func_ptr) ();



int calcula(int x, int y, int z){ 
  return (x + y) * z;
}


// typedef int (*func_ptr) (void* candidata, size_t n);

// char fixa[] = "quero saber se a outra string é um prefixo dessa";

int main (void) {
  DescParam params[3];
  func_ptr conta;
  // char uma[] = "quero saber tudo";
  // int tam;

  int v[] = {10,20,30};
  void *p[] = {v,v+1, v+2};

  params[0].tipo_val = INT_PAR; /* o primeiro parâmetro de memcmp é um ponteiro para char */
  params[0].orig_val = IND;     /* a nova função passa para memcmp o endereço da string "fixa" */
  params[0].valor.v_ptr = v;

  params[1].tipo_val = INT_PAR; /* o segundo parâmetro de memcmp é também um ponteiro para char */
  params[1].orig_val = FIX;   /* a nova função recebe esse ponteiro e repassa para memcmp */
  params[1].valor.v_int = *(v+1);


  params[2].tipo_val = INT_PAR; /* o terceiro parâmetro de memcmp é um inteiro */
  params[2].orig_val = PARAM;   /* a nova função recebe esse inteiro e repassa para memcmp */
  // params[2].valor.v_ptr = v+2;
  conta = (func_ptr) cria_func (calcula, params, 3);
  dump(conta, 60);
  // tam = 12;
  // printf ("'%s' tem mesmo prefixo-%d de '%s'? %s\n", uma, tam, fixa, conta (uma, tam)?"NAO":"SIM");
  // tam = strlen(uma);
  // printf ("'%s' tem mesmo prefixo-%d de '%s'? %s\n", uma, tam, fixa, conta (uma, tam)?"NAO":"SIM");
  printf("Valor da conta:  %d \n", conta(*(v+2)));


  libera_func(conta);
  return 0;
}
