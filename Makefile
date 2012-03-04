UNAME  	= $(shell uname -s)
CC 	= gcc
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS 	= -framework GLUT -framework OpenGL -lobjc
LDFLAGS =
else
LDLIBS 	= -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm
LDFLAGS = -I /usr/include/GL/ -L /usr/include/GL
endif
RM	= rm

TARGET 	= Asteroids
SRCS 	= main.c ship.c
HEADERS = ship.h asteroid.h physics.h list.h
OBJS	= ${SRCS:.c=.o}

.SUFFIXES: .o .c

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.c.o :
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

TAGS : $(SRCS) $(HEADERS)
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean
clean :
	-$(RM) $(TARGET) $(OBJS) .depend
