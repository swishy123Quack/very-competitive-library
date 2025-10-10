SparseTable<int> rmq(a, [](int a, int b){
    return min(a, b);
});