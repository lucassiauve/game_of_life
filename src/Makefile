include ../config.mk

TARGET 	= game_of_life
OBJS 	= game_of_life.o 		\
		  graphics/graphics.o 	\

DEPS 	= $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)

debug: CFLAGS += -O0 -g3
debug: LDFLAGS += -fsanitize=address
debug: $(TARGET)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)
