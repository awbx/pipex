#include "pipex.hpp"

static void label(t_ast *node, int &id) {
  if (!node) return;

  cout << "\tNode" << id << "[label=\"";

  if (node->type == PIPE_NODE) cout << "|";

  if (node->type == CMD_NODE) {
    cout << ((t_cmdlist *)node)->av[0];
  }

  cout << "\"]\n";
}

static void edge(int from, int to) {
  cout << "\tNode" << from << " -> "
       << "Node" << to << "[wieght=10]\n";
}

static int dfs(t_ast *tree, int &id) {
  int my_id = 0, l, r;

  my_id = id++;

  if (tree) {
    label(tree, my_id);
    if (tree->type == PIPE_NODE) {
      l = dfs(((t_pipeline *)tree)->left, id);
      r = dfs(((t_pipeline *)tree)->right, id);
      edge(my_id, l);
      edge(my_id, r);
    }
  }

  return my_id;
}

void dump_dot(t_ast *tree) {
  cout << "digraph {\n";
  int id = 0;
  dfs(tree, id);
  cout << "}\n";
}
