#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cria_func.h"





static unsigned char movls[] = {0xbf, 0x00, 0x00, 0x00, 0x00}; /* movl $i, %edi */

static unsigned char movlp[] = {0x49, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /* movq &i, %r8 */

static unsigned char movlr[] = {0x41, 0x8b, 0x38}; /* movl (%r8), %edi */


static unsigned char movqr[] = {0x49, 0x8b, 0x38}; /* movq (%r8), %rdi */
static unsigned char movq[] = {0x48, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /* movq $l, %rdi */

static unsigned char movls2[] = {0xbe, 0x00, 0x00, 0x00, 0x00}; /* movl $i, %esi */

static unsigned char movlr2[] = {0x41, 0x8b, 0x30}; /* movl (%r8), %esi */


static unsigned char movqr2[] = {0x49, 0x8b, 0x30}; /* movq (%r8), %rsi */
static unsigned char movq2[] = {0x48, 0xbe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /* movq $l, %rsi */


static unsigned char movls3[] = {0xba, 0x00, 0x00, 0x00, 0x00}; /* movl $i, %edx */

static unsigned char movlr3[] = {0x41, 0x8b, 0x10}; /* movl (%r8), %edx */


static unsigned char movqr3[] = {0x49, 0x8b, 0x10}; /* movq (%r8), %rdx */
static unsigned char movq3[] = {0x48, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /* movq $l, %rdx */





static unsigned char call[] = {0x41, 0xff, 0xd0}; /* %r8 call *%r8 */



void* cria_func (void* f, DescParam params[], int n){
    unsigned char *codigo;
    unsigned char *p;

    codigo = (unsigned char *)malloc(1000*sizeof(char));
    p = codigo;
    
    
    if(params[0].tipo_val == INT_PAR){printf("int\n");
        if(params[0].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
        else{
            if(params[0].orig_val== FIX){printf("int_FIX\n");
                int i = params[0].valor.v_int;
                memcpy(&movls[1],(unsigned char*) &i,sizeof(i));
                memcpy(p,movls,sizeof(movls));
                p+=sizeof(movls);
                }
            else{printf("int_IND\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movlr,sizeof(movlr));
                p+=sizeof(movlr);
            }
        }
    }
    else{
        if(params[0].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
		else{
       	  	 if(params[0].orig_val == FIX){/*"movq 'params[0].valor.v_ptr', %rdi";*/
         	 printf("int_FIX\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movq[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq,sizeof(movq));
                p+=sizeof(movq);
		}

		
                      else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                printf("int_IND\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movqr,sizeof(movqr));
                p+=sizeof(movqr);
		}
        }
    
    }

//Dois parametros
	if(n > 1) {
		if(params[1].tipo_val == INT_PAR){printf("int\n");
      	  if(params[1].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
       		 else{
            if(params[1].orig_val== FIX){printf("int_FIX\n");
                int i = params[1].valor.v_int;
                memcpy(&movls2[1],(unsigned char*) &i,sizeof(i));
                memcpy(p,movls2,sizeof(movls2));
                p+=sizeof(movls2);
                }
            else{printf("int_IND\n");
                unsigned long l = (unsigned long) params[1].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movlr2,sizeof(movlr2));
                p+=sizeof(movlr2);
            }
        }
    }
    else{
        if(params[1].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
		else{
       	  	 if(params[1].orig_val == FIX){
         	 printf("int_FIX\n");
                unsigned long l = (unsigned long) params[1].valor.v_ptr;
                memcpy(&movq2[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq2,sizeof(movq2));
                p+=sizeof(movq2);
		}

		
                      else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                printf("int_IND\n");
                unsigned long l = (unsigned long) params[1].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movqr2,sizeof(movqr2));
                p+=sizeof(movqr2);
		}
        }
    }

	
	}

	if(n > 2) {
		if(params[2].tipo_val == INT_PAR){printf("int\n");
      	  if(params[2].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
       		 else{
            if(params[2].orig_val== FIX){printf("int_FIX\n");
                int i = params[2].valor.v_int;
                memcpy(&movls3[1],(unsigned char*) &i,sizeof(i));
                memcpy(p,movls3,sizeof(movls3));
                p+=sizeof(movls3);
                }
            else{printf("int_IND\n");
                unsigned long l = (unsigned long) params[2].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movlr3,sizeof(movlr3));
                p+=sizeof(movlr3);
            }
        }
    }
    else{
        if(params[0].orig_val == PARAM){printf("int_PARAM\n");/*faz nada*/}
		else{
       	  	 if(params[0].orig_val == FIX){
         	 printf("int_FIX\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movq3[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq3,sizeof(movq3));
                p+=sizeof(movq3);
		}

		
                      else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                printf("int_IND\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movlp,sizeof(movlp));
                p+=sizeof(movlp);
                memcpy(p,movqr3,sizeof(movqr3));
                p+=sizeof(movqr3);
		}
        }
    }

	
	}


    unsigned long l = (unsigned long) f;
    memcpy(&movlp[2],(unsigned char*) &l,sizeof(l));
    memcpy(p,movlp,sizeof(movlp));
    p+=sizeof(movlp);
    memcpy(p,call,sizeof(call));
    p+=sizeof(call);
    *p = 0xC3;    //codigo += "ret";

    return (void*)codigo;
}


