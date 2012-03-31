UNAME  	= $(shell uname -s)
CC 	= gcc
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS 	= -framework GLUT -framework OpenGL -lobjc -lm
LDFLAGS =
else
LDLIBS 	= -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm
LDFLAGS = -I /usr/include/GL/ -L /usr/include/GL
endif
RM	= rm

ifdef CONFIG_DEBUG
CFLAGS := -g
LDFLAGS := -g
endif

TARGET 	= Asteroids
SRCS 	= main.c ship.c asteroid.c game.c keyboard.c
OBJS	= ${SRCS:.c=.o}

.SUFFIXES: #clear
.SUFFIXES: .o .c

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.c.o :
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

TAGS : FORCE
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

FORCE : # force to always happen

.PHONY : clean FORCE mrproper
clean :
	-$(RM) $(TARGET) $(OBJS)

mrproper :
	-$(RM) $(TARGET) $(OBJS) .depend TAGS
