#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cria_fun.h"

static unsigned char movls[] = {0xbf, 0x00, 0x00, 0x00, 0x00}; /* movl $i, %edi */
static unsigned char movlp[] = {0x49, 0xBb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x8b, 0x38}; /* movq &i, %r8 movl (%r8), %edi */



void* cria_func (void* f, DescParam params[], int n){
        unsigned char *codigo;
        unsigned char *p;

        codigo = (unsigned char *)malloc(1000*sizeof(char));
        p = codigo;

        if(params[0].tipo_val == INT_PAR){printf("int\n");
                if(params[0].orig_val == PARAM){/*faz nada*/}
                else{
                        if(params[0].orig_val== FIX){printf("int_IND\n");
                                int i = params[0].valor.v_int;
                                memcpy(&movls[1],(unsigned char*) &i,sizeof(i));
                                memcpy(p,movls,sizeof(movls));
                                p+=sizeof(movls);
                                }
                        else{printf("int_PAR\n");
                                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                                memcpy(p,movlp,sizeof(movlp));
                                p+=sizeof(movlp);
                        }
                }
        }
        else{
                if(params[0].orig_val == PARAM){/*faz nada*/}
                else{
                        if(params[0].orig_val == FIX){/*"movq 'params[0].valor.v_ptr', %rdi";*/}
                        else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/}
                }
        }

        *p = 0xC3;      //codigo += "ret";



        return (void*)codigo;
}



void libera_func (void* func){
	free(func);
		return;
}
