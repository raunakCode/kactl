g++ sol.cpp -o sol      # your incorrect sol
g++ brute.cpp -o brute  # the bruteforce sol
g++ gen.cpp -o gen  # generator file

for ((i = 1; ;++i)); do
    ./gen $i > randomInput
    ./sol < randomInput > myOutput
    ./brute < randomInput > bruteOutput
    diff -w myOutput bruteOutput || break
    echo "Passed test: " $i
done

echo -e "WA on the following test:"
cat randomInput
echo "Your answer is: "
cat myOutput
echo "Correct answer is: "
cat bruteOutput
