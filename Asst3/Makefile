all: wtfserver wtfclient clean

wtfserver: wtfserver.c
	gcc wtfserver.c -o WTFserver -lpthread
	
wtfclient: wtfclient.c
	gcc wtfclient.c -o WTFclient

clean:
	rm WTFserver WTFclient
