#ifndef COMMON_H
#define COMMON_H

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define die(msg, ...) do { fprintf(stderr, "%s:%d: ", __FILE__, __LINE__); fprintf(stderr, msg, ##__VA_ARGS__); fprintf(stderr, "\n"); exit(EXIT_FAILURE); } while(false);

extern void init();

extern void render();

//! Aktuelle Zeit seit Start in Millisekunden
extern uint32_t timer();

//! Lädt eine Textdatei als nullterminierter String
char const * loadtxt(char const * fileName);

#endif // COMMON_H
