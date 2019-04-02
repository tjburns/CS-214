all: fileCompressor

huffmanTree: huffmanTree.c
	gcc -O -g -o huffmanTree.o huffmanTree.c

countEntries: countEntries.c
	gcc -O -g -o countEntries.o countEntries.c

fileCompressor: fileCompressor.c huffmanTree.o huffmanTree.h countEntries.o countEntries.h
	gcc -O -g -o fileCompressor fileCompressor.c huffmanTree.o countEntries.o

clean: 
	rm -f fileCompressor huffmanTree.o countEntries.o HuffmanCodebook
