#compile
g++ main.cpp -std=gnu++0x -O3 -lcrypto -fopenmp -o cracker

echo ""
echo "---- MD5 ----"
echo ""

#Test md5 with rules attack
./cracker -h ./Demo/md5 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 0 -a 1

#Test md5 with bruteforce attack
./cracker -h ./Demo/md5 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -min 1 -max 5 -c "0123456789abcdef" -t 0 -a 3

echo ""
echo "---- SHA 1 ----"
echo ""

#Test sha1 with rules attack
./cracker -h ./Demo/sha1 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 1 -a 1
