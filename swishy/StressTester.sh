set -e
g++ -std=c++20 code.cpp -o code
g++ -std=c++20 gen.cpp -o gen
g++ -std=c++20 brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    if diff -Z myAnswer correctAnswer > /dev/null; then
        echo -e "$Passed test: $i$"
    else
        echo -e "$Failed test: $i$"
        echo -e "$WA on the following test:$"
        cat input_file
        echo -e "$Your answer is:$"
        cat myAnswer
        echo -e "$Correct answer is:$"
        cat correctAnswer
        break
    fi
done