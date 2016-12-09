cd ./SRC_DISP
make re
./generateDisps.sh
cd ..
cd ./SRC_PTGEN
make re
./generateCSVS.sh
cd ..
cd ./SRC_RANALYZE
./generateResults.sh
