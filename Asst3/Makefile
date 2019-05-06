all: wtfserver wtfclient

wtfserver: wtfserver.c
	gcc -std=gnu90 wtfserver.c -o WTFserver -lpthread
	
wtfclient: wtfclient.c
	gcc -std=gnu90 wtfclient.c -o WTF

clean:
	rm WTFserver WTF
