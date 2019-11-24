.data
.text
.globl foo


foo:
movq %rdi, %r9  
movq %rsi, %r10
movq %rdx, %r11
movq %r9, %rdi
movq %r10, %rsi
movq %r11, %rdx
movl %r9d, %edi
movl %r10d, %esi
movl %r11d, %edx

movq %r9, %rsi
movq %r9, %rdx
movl %r9d, %esi
movl %r9d, %edx

movq %r10, %rdx
movl %r10d, %edx

ret
