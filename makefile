project6: main.o
	g++ main.o -o project6

main.o: main.cpp linkedbsearchtree.h linkedbtree.h linkedtreenode.h tree.h
	g++ -c main.cpp

clean:
	rm *.o project6
