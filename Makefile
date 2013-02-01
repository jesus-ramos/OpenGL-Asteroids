UNAME	= $(shell uname -s)
CC	= gcc
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS	= -framework GLUT -framework OpenGL -lobjc -lm
LDFLAGS =
else
LDLIBS	= -lglut -lGL -lGLU -lm
LDFLAGS = -I /usr/include/GL/ -L /usr/include/GL
endif
RM	= rm

ifdef CONFIG_DEBUG
CFLAGS := -g
LDFLAGS := -g
endif

BINDIR	= bin
DEPSDIR = deps
MKDIRS	= $(CURDIR)/{$(BINDIR),$(DEPSDIR)}

TARGET	= Asteroids
SRCS	= main.c ship.c asteroid.c game.c
OBJS	= $(addprefix $(BINDIR)/,${SRCS:.c=.o})
DEPS	= $(addprefix $(DEPSDIR)/,${SRCS:.c=.d})

.SUFFIXES:
.SUFFIXES: .o .c

$(shell `mkdir -p $(MKDIRS)`)

all : $(TARGET)

$(BINDIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEPSDIR)/%.d : %.c
	@$(CC) $(CFLAGS) -M $< > $@.$$$$;			\
	sed -e '1s#^#$(BINDIR)/#'				\
	-e 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	-$(RM) -r $(BINDIR) $(DEPSDIR) $(TARGET)

-include $(DEPS)

.PHONY : clean TAGS
