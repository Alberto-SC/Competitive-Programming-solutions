for((i = 1; ; ++i)); do
    echo $i
    ./gen.out $i > in1
    ./a.out < in1 > out1
    ./b.out < in1 > out2
    diff -w out1 out2 || break
    # diff -w <(./a.out < in.txt) <(./b.out < in.txt) || break
done
