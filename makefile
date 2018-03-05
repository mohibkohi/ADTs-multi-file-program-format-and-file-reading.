CC = gcc
CFLAGS = -g -Wall
default = hw4

hw4: Client.o arraylist.o houses.o main.o
	$(CC) $(CFLAGS) -o hw4 Client.o arraylist.o houses.o main.o

client.o: Client.c 
	$(CC) $(CFLAGS) -c client.c

houses.o: houses.c 
	$(CC) $(CFLAGS) -c houses.c

arraylist.o: arraylist.c 
	$(CC) $(CFLAGS) -c arraylist.c

clean:
	$(RM) hw4 *.o *~ houseView.csv clientsView.csv

