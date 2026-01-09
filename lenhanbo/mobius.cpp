
int mob[nmax];
void mobcalc(){ // calculate in nlog
    mob[1] = 1;
    for(int i = 1;i<nmax;++i){
        for(int j = i * 2;j<nmax;j+=i){
            mob[j]  -= mob[i];
        }
    }
}

//ta co sum(mob[d | n]) = [n == 1] (n co bang 1 hay ko) nen tim cach bien doi cong thuc ve dang nay
// sum gcd(i,j) = sum(x) sum(x | i) sum(x | j) [gcd(i/x, j/x) == 1] = sum(x) 
// sau do thay  [gcd(i/x, j/x) == 1] = sum(d|gcd(i/x, j/x)) mob[d], sau do tim cach dua d ra ngoai hoac co the dat T = d*x roi xu ly
