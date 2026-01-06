int query(int root, int l, int r, int lowerbound, int k) {
    if (st[root] > k) return -1; //nếu cả đoạn [l, r] đều lớn hơn k thì không thỏa mãn
    if (r < lowerbound) return -1; //ta chỉ xét những vị trí không nhỏ hơn lowerbound
    if (l == r) return l; //khi đoạn có 1 phần tử thì đó là kết quả
    int mid = (l + r) / 2;
    int res = -1;
    if (st[root * 2] <= k) //nếu min cây con trái không vượt quá k
        res = query(root * 2, l, mid, lowerbound, k);
    //nếu cây con trái không tìm được kết quả <=> min nằm ngoài lowerbound
    //thì ta sẽ tìm kết quả ở cây con phải
    if (res == -1)
        res = query(root * 2 + 1, mid + 1, r, lowerbound, k);
    return res;
}
