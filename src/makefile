all :
	cd init; make; cd ..;
	cd http; make; cd ..;
	cd work; make; cd ..;
	cd net; make; cd ..;
	cd main; make; cd ..;
	cd ..;
	$(CC) -o $(ROOT)/bin/main $(ROOT)/bin/*.o -lpthread
	$(ROOT)/bin/main

#  ./$(ROOT)/bin/main ??执行main
