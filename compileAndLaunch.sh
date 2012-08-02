#compile
g++ main.cpp -std=gnu++0x -O3 -lcrypto -fopenmp -o cracker

echo ""
echo "---- MD5 ----"
echo ""

#Test md5 with rules attack
./cracker -h ./Demo/md5 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 0 -a 0

echo ""
echo "---- SHA 1 ----"
echo ""

#Test sha1 with rules attack
./cracker -h ./Demo/sha1 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 1 -a 0
