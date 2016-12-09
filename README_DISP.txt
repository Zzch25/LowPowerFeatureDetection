Zachary Job
25/25/25
README_DISP.txt

Notes:
				This is designed for a camera on rails

				I've left the primary setup completely configurable. Trivial things are defined in defs.h. The program order of execution is written into mgr.c
				The wrappers in mgr.c organize stages.
				
				O N   D I S P A R I T Y

						This attempted to handle edges. I left it as is, the accuracy is not terrible vertically. However it does not handle horizontal edges 
						well. Again, an artifact of the design that doesn't really affect the core result. If this is an issue, it can easily modified. If this matters pllllllease 
						contact me.

Build:
				I N S T A L L
					libnetpbm. Just in case the tarball is included. Extract and follow the readme.
					I have portable loaders, but they are borrowed and I do not trust them.
					I'll come back to this if I have time...
					TECHNICALLY portable still, I've inlcuded everything. This can compile to all OS's.
				
				C D   T O   S R C _ D I S P
					Clean: make clean
					Clean and build: make re
					Build: make

Usage:	
				C D   T O   S R C _ D I S P
					./generateDisps.sh
				
				C U S T O M
					./DISP (1->N)[type [baseView targetView distance focallength OutputFile]
									
									(1->N)[...]:		Specify the base image, the target image, their distance apart, and the camera focallength, the output file.
									
					SEE...
						The local script used to run the code, generateDisps.sh
					For examples
