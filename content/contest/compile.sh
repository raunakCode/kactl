arr=$(echo $1 | tr "." "\n")
name=""
for el in $arr:
do
    name=$el
    break
done
g++ -std=c++17 $1 -fcompare-debug-second -fsanitize=address,undefined -g -static-libasan -DONPC -o $name
