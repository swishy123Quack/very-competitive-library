
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
