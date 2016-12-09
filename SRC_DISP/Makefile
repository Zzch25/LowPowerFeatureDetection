#Zachary Job
#Gsyntax MF

NAME=DISP
X=SRC/
SRC=																									\
		mgr.c																							\
																										\
		$(X)openFD.c $(X)closeFD.c $(X)grayToDouble.c $(X)initData.c				\
		$(X)stereo.c $(X)outGray.c $(X)cleanData.c										\
		$(X)viewPairsToDisps.c $(X)SAD.c $(X)rankTransform.c

RM=rm -f

all: DispGen

clean:
	-$(RM) *.o
	-$(RM) *.c~
	-$(RM) .*.c~
	-$(RM) *~
	-$(RM) .*~
	-$(RM) .swp
	-$(RM) *.swp
	-$(RM) .*.swp
	-$(RM) SRC/*.o
	-$(RM) SRC/*.c~
	-$(RM) SRC/.*.c~
	-$(RM) SRC/*~
	-$(RM) SRC/.*~
	-$(RM) SRC/.swp
	-$(RM) SRC/*.swp
	-$(RM) SRC/.*.swp
	-$(RM) *.exe
	-$(RM) *.stackdump
	-$(RM) $(NAME)

fclean: clean

re: fclean all

DispGen:
	gcc -std=c11 -Wall -pedantic-errors $(SRC) -lnetpbm -lm -o $(NAME)
