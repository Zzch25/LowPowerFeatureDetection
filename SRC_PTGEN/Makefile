#Zachary Job
#Gsyntax MF

NAME=PTGEN
X=SRC/
SRC=																									\
		mgr.c																							\
																										\
		$(X)openFD.c $(X)closeFD.c $(X)grayToDouble.c $(X)initData.c				\
		$(X)cleanData.c $(X)bucketPoints.c $(X)outCSV.c

RM=rm -f

all: PointGen

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

PointGen:
	gcc -std=c11 -Wall -pedantic-errors $(SRC) -lnetpbm -lm -o $(NAME)
