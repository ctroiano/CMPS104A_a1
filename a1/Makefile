#
#	This is a basic Makefile by Chris Troiano
#        github 
#          git add . 
#          git commit -m "msg"
#          git push origin master

CC = g++ -g -O0 -Wall -Wextra -std=gnu++11 
OBJS = oc.cpp auxlib.cpp stringset.cpp

oc: $(OBJS)
	$(CC) -o $@ $^
	
clean:
	-rm -f *.o core *.core
