Zachary Job
25/25/25
README_PTGEN.txt

Notes:
				This simply is a point bucket system. The points in a window are bucketed from 0 to 255. The Sample allowed is a 25 by 25 window.

Build:
				I N S T A L L
					libnetpbm. Just in case the tarball is included. Extract and follow the readme.
					I have portable loaders, but they are borrowed and I do not trust them.
					I'll come back to this if I have time...
					TECHNICALLY portable still, I've inlcuded everything. This can compile to all OS's.
				
				C D   T O   S R C _ P T G E N
					Clean: make clean
					Clean and build: make re
					Build: make

Usage:	
				C D   T O   S R C _ P T G E N
					./generateCSVS.sh
				
				C U S T O M
					./CSVS Filename.pgm Output.csv [Newfile (0)|Appendfile (1)] (1->N)[x y]
													
					SEE...
						The local script used to run the code, generateCSVS.sh
					For examples
