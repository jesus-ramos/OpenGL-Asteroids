UNAME  	= $(shell uname -s)
CC 	= gcc
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS 	= -framework GLUT -framework OpenGL -lobjc -lm
LDFLAGS =
else
LDLIBS 	= -lglut -lGL -lGLU
LDFLAGS = -I /usr/include/GL/ -L /usr/include/GL
endif
RM	= rm

ifdef CONFIG_DEBUG
CFLAGS := -g
LDFLAGS := -g
endif

TARGET 	= Asteroids
SRCS 	= main.c ship.c asteroid.c game.c
OBJS	= ${SRCS:.c=.o}
DEPS	= ${SRCS:.c=.d}

.SUFFIXES:
.SUFFIXES: .o .c

all : $(TARGET)

%.d : %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; 	\
	rm -f $@.$$$$

-include $(DEPS)

.c.o :
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	-$(RM) $(TARGET) $(OBJS) $(DEPS) TAGS

.PHONY : clean TAGS
