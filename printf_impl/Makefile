VLG = valgrind --leak-check=yes --track-origins=yes


#########  #########  ##    ##  #######    #########      
    #      #       #  # #  # #  ##         #       # 
    #      #       #  #  #   #  #######    #########
    #      #       #  #      #  ##         ##  ###
    #      #########  #      #  #######    ##   ###

####################################################
#   				COMPILATION                    #
####################################################
CC:=gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
LDFLAGS = -DNDBUG -O3
CPPFLAGS := -I ../include/
#####################################################


#####################################################
#    				DIR FILES                       #
#####################################################
Folder:=$(shell basename $(CURDIR))
SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o,$(SRC))
HEADER:= ../include/$(Folder).h
EXEC:= a.out
#####################################################


all: build test

vlg: $(EXEC)
	$(VLG) ./$(EXEC)

test : $(EXEC)
	./$(EXEC)

build: $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $? -o $@
		rm -f $(OBJS)

create:

ifeq ($(shell test -e $(Folder).c && echo -n yes),yes)
	echo "already created"
else
	touch $(Folder).c $(Folder)_test.c $(HEADER).h

		code $(HEADER)
		printf '#include <stdio.h>\n\n#include "$(Folder).h"\n#include "utils.h"\n\nint main()\n{\n\n return 0;\n} ' > \
		$(Folder)_test.c
		printf '#include <stdio.h>\n\n#include "$(Folder).h"\n#include "utils.h"\n\n ' > $(Folder).c;\
		printf "#ifndef __STR_PARSE_H__ \n#define __STR_PARSE_H__\n\n\n#endif /* __STR_PARSE_H__ */" > $(HEADER)
endif

push:
	git add ./
	git commit -m "$(m)"
	git push -u origin master

clean:
	rm -f a.out $(OBJS)


# $@ --> introduce the first target
# $? --> introcude all prerequisites newer than the target
# $^ --> introduce all prerequisites

##example:
# hey: one two
# $@ ---> introcude hey.
# $? ---> introcude one two .
# $@ ---> introcude hey one two.
# one:
#touch one
#two:
#touch two
