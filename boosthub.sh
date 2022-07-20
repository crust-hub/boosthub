cmake . &&
echo "cmake ." &&
make &&
echo "make ." &&
./bin/boosthub --server 0.0.0.0 20001 &
