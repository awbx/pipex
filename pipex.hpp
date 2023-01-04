#ifndef __PIPE_NODEX_HPP__
#define __PIPE_NODEX_HPP__

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#define CMD_NODE 1
#define PIPE_NODE 2

#define READ_END 0
#define WRITE_END 1

#define LEFT_SIDE 1
#define RIGHT_SIDE 2

using namespace std;

typedef struct s_ast {
  int type;
} t_ast;

typedef struct s_cmdlist {
  int    type;
  char **av;
  size_t len;
} t_cmdlist;

typedef struct s_pipeline {
  int    type;
  t_ast *left;
  t_ast *right;
} t_pipeline;

// parser functions
t_ast *parser(char **, int);

// executor functions
void executor(t_ast *);

// utils
void dump_dot(t_ast *tree);

#endif