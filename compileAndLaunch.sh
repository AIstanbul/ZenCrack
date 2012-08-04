#compile
g++ main.cpp -std=gnu++0x -O3 -lcrypto -fopenmp -o zencrack

#Test md5 with mask attack
./zencrack -h ./Demo/md5 -m ulld -t 0 -a 4

#Test md5 with rules attack
./zencrack -h ./Demo/md5 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 0 -a 1

#Test md5 with bruteforce attack
./zencrack -h ./Demo/md5 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -min 1 -max 5 -c "0123456789abcdef" -t 0 -a 3

#Test sha1 with rules attack
./zencrack -h ./Demo/sha1 -r ./Demo/best64.rule -w ./Demo/rockyou.dic -t 1 -a 1
