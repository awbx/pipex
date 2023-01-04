#include "pipex.hpp"

static void run_cmd(t_cmdlist *cmdlist) {
  int pid;

  pid = fork();
  if (pid == -1)
    return;
  else if (pid == 0) {
    execvp(cmdlist->av[0], cmdlist->av);
    perror("execve");
    exit(1);
  }
  waitpid(pid, NULL, 0);
}

static void close_pipe(int fds[2]) {
  close(fds[READ_END]);
  close(fds[WRITE_END]);
}

static pid_t run_pipe(t_ast *pipleine, int fds[2], int side) {
  pid_t pid;
  int   end;
  int   fileno;

  end = WRITE_END;
  fileno = STDOUT_FILENO;
  if (side == RIGHT_SIDE) {
    end = READ_END;
    fileno = STDIN_FILENO;
  }
  pid = fork();
  if (pid == 0) {
    dup2(fds[end], fileno);
    close_pipe(fds);
    executor(pipleine);
    exit(1);
  }
  return (pid);
}

static void run_pipeline(t_pipeline *pipleine) {
  int status;
  int pids[2];
  int fds[2];

  if (pipe(fds) == -1) return;
  pids[0] = run_pipe(pipleine->left, fds, LEFT_SIDE);
  if (pids[0] == -1) return;
  pids[1] = run_pipe(pipleine->right, fds, RIGHT_SIDE);
  if (pids[1] == -1) return;
  close_pipe(fds);
  wait(&status);
  wait(&status);
}

void executor(t_ast *tree) {
  if (!tree) return;
  if (tree->type == CMD_NODE) run_cmd((t_cmdlist *)tree);
  if (tree->type == PIPE_NODE) run_pipeline((t_pipeline *)tree);
}
