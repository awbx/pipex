#include "pipex.hpp"





int main(int ac, char **av) {
  if (ac >= 5) {
    int infile = open(av[1], O_RDONLY);
    int outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup2(infile, STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);

    t_ast *tree = parser(av + 2, ac - 3);
    // dump_dot(tree);
    executor(tree);
  }
}