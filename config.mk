CC = gcc
CPPFLAGS = -Isrc/
CFLAGS = -Wall -Werror -Wextra -Wvla -pedantic -std=c99 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)
