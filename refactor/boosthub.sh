cmake . &&
echo "cmake ." &&
make &&
echo "make ." &&
./bin/boosthub -i 0.0.0.0 -p 8080 -l 1
