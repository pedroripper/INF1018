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
void libera_func (void* func){
    free(func);
    return;
}



typedef int (*func_ptr) ();

int mult(int x) {
  return x * 2;
}

void vetchar(char *s) {
	printf("%s\n", s);
	return;
}


int main(){
    DescParam params[1];
    func_ptr f_mult;
    int i=100;
    char fixa[] = "quero saber se a outra string é um prefixo gabriel gabriel";
    char *c[] = {fixa};
    


printf("endereco de i = %p\n",&i);
    params[0].tipo_val = PTR_PAR;
     params[0].orig_val = IND;
     params[0].valor.v_ptr = c;
//    params[0].valor.v_int = i;

    f_mult = (func_ptr) cria_func (vetchar, params, 1);
    dump(f_mult, 50);
//    printf("             %d\n", f_mult(i));
    f_mult();
    libera_func(f_mult);
    return 0;
}


