.data
.text
.globl foo


foo:
movl %esi , %edi
movq %rsi, %rdi
movq %rdx, %rsi
movl %edx, %esi
movq %rdx, %rdi
movl %edx, %edi


ret
