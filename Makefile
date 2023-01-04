

all:
	c++ pipex.cpp parser.cpp executor.cpp utils.cpp -o pipex -g #-fsanitize=address