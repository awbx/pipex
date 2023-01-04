#include "pipex.hpp"

static t_ast *pipeline_constructor(t_ast *left, t_ast *right) {
  t_pipeline *node = (t_pipeline *)malloc(sizeof(t_pipeline));  // new t_ast();
  if (!node) return nullptr;
  node->type = PIPE_NODE;
  node->left = left;
  node->right = right;
  return (t_ast *)node;
}

static t_ast *cmdlist_constructor(char **av, size_t len) {
  t_cmdlist *node = (t_cmdlist *)malloc(sizeof(t_cmdlist));  // new t_ast();
  if (!node) return nullptr;
  node->type = CMD_NODE;
  node->av = av;
  node->len = len;
  return (t_ast *)node;
}

static t_ast *parse_command(char *command) {
  char         **av;
  vector<string> vec;
  istringstream  stream(command);

  string str;
  while (getline(stream, str, ' ')) vec.push_back(str);
  av = (char **)malloc(sizeof(char *) * (vec.size() + 1));
  for (size_t idx = 0; idx < vec.size(); idx++) av[idx] = strdup(vec[idx].c_str());
  av[vec.size()] = nullptr;
  t_ast *cmdlist = cmdlist_constructor(av, vec.size());
  return cmdlist;
}

static t_ast *parse_pipeline(char **tokens, int len) {
  if (!*tokens || !len) return nullptr;

  t_ast *ret = parse_command(*tokens);

  while (*tokens++ && --len) {
    ret = pipeline_constructor(ret, nullptr);
    ((t_pipeline *)ret)->right = parse_command(*tokens);
  }

  return ret;
}

t_ast *parser(char **tokens, int len) { return parse_pipeline(tokens, len); }