void xorconv(vector<int> &a,int modul){ // chuyen tu dang binh thuong sang dang dac biet, xong cu lay a[i] = b[i] * c[i] ...
    int n = a.size();
    for(int m = n/2; m; m/=2){
        for(int i = 0 ; i < n; i+= 2 * m){
            for(int j = 0;j <m;++ j){
                int x = a[i + j];
                int y = a[i + j + m];
                a[i + j] = (x + y)%modul;
                a[i + j + m] = (x-y+modul) % modul;
            }
        }
    }
}
void xorconv2(vector<int> &a,int modul){ // chuyen tu dang dac biet ve dang binh thuong => dap an sau khi fft
    int n = a.size();
    for(int m = 1; m<n; m*=2){
        for(int i = 0 ; i < n; i+= 2 * m){
            for(int j = 0;j <m;++ j){
                int x = a[i + j];
                int y = a[i + j + m];
                a[i + j] = (x + y)%modul;
                a[i + j + m] = (x-y+modul) % modul;
            }
        }
    }
    for(int i = 0;i<n;++i){
        a[i] = 1LL * (ll)a[i] * binpow(n,modul - 2, modul) %modul;
    }
}