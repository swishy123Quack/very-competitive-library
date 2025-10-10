template <typename T>
struct Matrix{
    vector<vector<T>> m;
    Matrix (vector<vector<T>> &m) : T(m){}
    Matrix (int r, int c) {
        m = vector<vector<T>>(r, vector<T>(c));
    }

    int row() const {return m.size();}
    int col() const {return m[0].size();}

    static Matrix identity(int n){
        Matrix res = Matrix(n, n);
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        return res;
    }

    auto & operator [] (int i) { return m[i]; }
    const auto & operator[] (int i) const { return m[i]; }

    Matrix operator * (const Matrix &b){
        Matrix a = *this;
        assert(a.col() == b.row());

        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); i++)
            for (int j = 0; j < b.col(); j++)
                for (int k = 0; k < a.col(); k++)
                    c[i][j] += a[i][k] * b[k][j];
        return c;
    }

    Matrix pow(ll x){
        assert(row() == col());
        Matrix crr = *this, res = identity(row());
        while (x > 0){
            if (x % 2 == 1) 
                res = res * crr;
            crr = crr * crr;
            x /= 2;
        }
        return res;
    }
};