example_exe : BinaryTreeArray.o main.o
	gcc -o example_exe BinaryTreeList.o main.o

BinaryTreeArray.o : BinaryTreeArray.c
	gcc -c -o BinaryTreeList.o BinaryTreeList.c

main.o : main.c
	gcc -c -o main.o main.c
  
clean : 
	rm *.o example_exe