#Zachary Job
#Gsyntax MF

NAME=HAR
SRC=mgr.c openFD.c closeFD.c conv2.c conv2Init.c conv2Clean.c matrixOp.c harrisOperation.c genGaussKernel.c grayToDouble.c kernClean.c kernInit.c getMap.c SADOperation.c cmpQSort.c

RM=rm -f

all: Harris

clean:
	-$(RM) *.o
	-$(RM) *.exe

fclean: clean

re: fclean all

Harris:
	gcc -Wall -pedantic-errors  $(SRC) -lnetpbm -lm -lgsl -lgslcblas -o $(NAME)
