#include "pipex.hpp"

#include <readline/readline.h>

int heredoc(char *delim) {
  int         hfd[2];
  int         len;
  const char *buff;

  if (!delim || pipe(hfd) == -1) return (-1);
  len = strlen(delim);
  while (true) {
    string str;
    getline(cin, str);
    buff = str.c_str();
    if (!buff || memcmp(delim, buff, len + 1) == 0) break;
    write(hfd[WRITE_END], buff, strlen(buff));
    write(hfd[WRITE_END], "\n", 1);
  }
  return (close(hfd[WRITE_END]), hfd[READ_END]);
}

int main(int ac, char **av) {
  if (ac >= 5) {
    int io[2];

#if !DEBUG
    int infile;
    int flags = O_WRONLY | O_CREAT;
    if (!strcmp(av[1], "here_doc")) {
      infile = heredoc(av[2]);
      ac--, av++;
      flags |= O_APPEND;
    } else {
      infile = open(av[1], O_RDONLY);
      flags |= O_TRUNC;
    }
    int outfile = open(av[ac - 1], flags, 0644);
    dup2(infile, STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
#endif

    t_ast *tree = parser(av + 2, ac - 3);

#if DEBUG
    dump_dot(tree);
#else
    executor(tree);
#endif
  }
}