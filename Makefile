smem: smem.o smem_stack.o smem_instructions.o
	gcc smem.o smem_stack.o smem_instructions.o -o smem

smem.o: smem.c smem_instructions.h
	gcc -c smem.c

smem_stack.o: smem_stack.c smem_stack.h
	gcc -c smem_stack.c

smem_instructions.o: smem_instructions.c smem_instructions.h
	gcc -c smem_instructions.c

clean:
	rm *.o smem
