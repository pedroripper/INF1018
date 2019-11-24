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

static unsigned char movqdi9[] = {0x49, 0x89, 0xf9}; /*movq %rdi %r9*/
static unsigned char movqsi10[] = {0x49, 0x89, 0xf2}; /*movq %rsi %r10*/
static unsigned char movqdx11[] = {0x49, 0x89, 0xd3}; /*movq %rdx %r11*/


static unsigned char movq9di[] = {0x4c, 0x89, 0xcf}; /*movq %r9 %rdi*/
static unsigned char movq10si[] = {0x4c, 0x89, 0xd6}; /*movq %r10 %rsi*/
static unsigned char movq11dx[] = {0x4c, 0x89, 0xda}; /*movq %r11 %rdx*/

static unsigned char movl9di[] = {0x44, 0x89, 0xcf}; /*movl %r9d %edi*/
static unsigned char movl10si[] = {0x44, 0x89, 0xd6}; /*movl %r10d %esi*/
static unsigned char movl11dx[] = {0x44, 0x89, 0xda}; /*movl %r11d %edx*/

static unsigned char movq9si[] = {0x4c, 0x89, 0xce}; /*movq %r9 %rsi*/
static unsigned char movq9dx[] = {0x4c, 0x89, 0xca}; /*movq %r9 %rdx*/

static unsigned char movl9si[] = {0x44, 0x89, 0xce}; /*movl %r9d %esi*/
static unsigned char movl9dx[] = {0x44, 0x89, 0xca}; /*movl %r9d %edx*/

static unsigned char movq10dx[] = {0x4c, 0x89, 0xd2}; /*movq %r10 %rdx*/
static unsigned char movl10dx[] = {0x44, 0x89, 0xd2}; /*movl %r10d %edx*/



static unsigned char call[] = {0x41, 0xff, 0xd0}; /* %r8 call *%r8 */

void libera_func (void* func){
    free(func);
    return;
}

void* cria_func (void* f, DescParam params[], int n){
    unsigned char *codigo;
    unsigned char *p;

    codigo = (unsigned char *)malloc(1000*sizeof(char));
    p = codigo;
    
   
    memcpy(p, movqdi9, sizeof(movqdi9));
    p += sizeof(movqdi9);

    memcpy(p, movqsi10, sizeof(movqsi10));
    p += sizeof(movqsi10);
    
    memcpy(p, movqdx11, sizeof(movqdx11));
    p += sizeof(movqdx11);


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
        if(params[0].orig_val == PARAM){printf("PTR_PARAM\n");/*faz nada*/}
		else{
       	  	if(params[0].orig_val == FIX){/*"movq 'params[0].valor.v_ptr', %rdi";*/
         	    printf("ptr_fix\n");
                unsigned long l = (unsigned long) params[0].valor.v_ptr;
                memcpy(&movq[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq,sizeof(movq));
                p+=sizeof(movq);
		}

		
                else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                    printf("ptr_ind\n");
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
      		if(params[1].orig_val == PARAM){
		printf("int_PARAM\n");
			if(params[0].orig_val != PARAM) {
			memcpy(p, movl9si, sizeof(movl9si));
			p += sizeof(movl9si);
		} else {
			memcpy(p, movl10si, sizeof(movl10si));
			p += sizeof(movl10si);
		}	
	    }
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
        if(params[1].orig_val == PARAM){
		
	printf("ptr_PARAM\n");
  
	if(params[0].orig_val != PARAM) {
			memcpy(p, movq9si, sizeof(movq9si));
			p += sizeof(movq9si);
		} else {
			memcpy(p, movq10si, sizeof(movq10si));
			p += sizeof(movq10si);
		}	
	 

	
	}
		else{
       	    if(params[1].orig_val == FIX){
         	 printf("ptr_FIX\n");
                unsigned long l = (unsigned long) params[1].valor.v_ptr;
                memcpy(&movq2[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq2,sizeof(movq2));
                p+=sizeof(movq2);
		    }
                else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                printf("ptr_IND\n");
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
      	  	if(params[2].orig_val == PARAM){
				printf("int_PARAM\n");
				if(params[0].orig_val != PARAM && params[1].orig_val != PARAM) {
				memcpy(p, movl9dx, sizeof(movl9dx));
				p += sizeof(movl9dx);
		 		}	
		 	else {
			//segunda checagem
		 	if(params[0].orig_val != PARAM || params[1].orig_val != PARAM) {
			memcpy(p, movl10dx, sizeof(movl10dx));
			p += sizeof(movl10dx);
		    } else {
		 	memcpy(p, movl11dx, sizeof(movl11dx));
			p += sizeof(movl11dx); 
		}
		} 
		  
		}

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
        // if(params[0].orig_val == PARAM){
		
		
		if(params[2].orig_val == PARAM){
				printf("ptr_PARAM\n");
				if(params[0].orig_val != PARAM && params[1].orig_val != PARAM) {
				memcpy(p, movq9dx, sizeof(movq9dx));
				p += sizeof(movq9dx);
		 		}	
		 	else {
    			//segunda checagem
    		 	if(params[0].orig_val != PARAM || params[1].orig_val != PARAM) {
    			memcpy(p, movq10dx, sizeof(movq10dx));
    			p += sizeof(movq10dx);
    		    } 
                else {
    		 	memcpy(p, movq11dx, sizeof(movq11dx));
    			p += sizeof(movq11dx);
    		    }
		    } 
		  
	    }


	// }
		else{
       	  	 if(params[2].orig_val == FIX){
         	 printf("ptr_FIX\n");
                unsigned long l = (unsigned long) params[2].valor.v_ptr;
                memcpy(&movq3[2],(unsigned char*) &l,sizeof(l));
                memcpy(p,movq3,sizeof(movq3));
                p+=sizeof(movq3);
		    }     

		
            else{/*codigo += "movq ('params[0].valor.v_ptr'), %rdi";*/
                printf("ptr_IND\n");
                unsigned long l = (unsigned long) params[2].valor.v_ptr;
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


