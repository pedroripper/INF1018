/* Nome_do_Aluno1 Matricula Turma */
/* Pedro da Silveira Carvalho Ripper 1910954 3WB */

#include <stdio.h>
#include 'bigint.h'



/* Atribuição (com extensão) */
void big_val (BigInt res, long val);

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
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);
