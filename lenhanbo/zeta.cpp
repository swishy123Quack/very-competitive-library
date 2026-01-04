// for "online" 
for(int mask = 0;mask < (1<<n);++mask){
        for(int i = 1;i<=n;++i){
            if(mask & (1<<(i-1))){
                add(dp[mask][i], dp[mask][i-1] + dp[mask ^ (1<<(i-1))][i-1]);
            } else {
                add(dp[mask][i], dp[mask][i - 1]);
            }
        }
    }

// to optimize memory "online" method
int cur[2][1<<n];
for(int mask = 0;mask <(1<<n);++mask){
      int fibit = 0;
      if(mask){
        for(int i = 0;i<n;++i){ // find biggest different bit between mask and mask-1
            if((mask ^ (mask-1)) & (1<<i)) fibit = i;
        }
        for(int mask2 = mask-1; mask2 >= mask - (1<<fibit);--mask2){ // update useful i in dp[mask][i] for each previous mask
              while(cur[mask2] <= fibit){
                  ++cur[mask2];
                  int ii = cur[mask2] - 1;
                  if(mask2 & (1<<ii)){
                      add(dp[mask2], dp[mask2 ^ (1<<ii)]);
                  }
              }
            
        }
        for(int i = 1;i<=n;++i){ // 
              if(mask & (1<<(i-1))){
                  add(dp[mask], dp[mask ^ (1<<(i-1))]);
              }
           
        }
    }
}

// if offline 
for(int i = 0;i<n;++i){
  for(int mask = 0;mask < (1<<n);mask++){
    if(mask & (1<<i)){
      dp[mask] += dp[mask ^ (1<<i)];
    }
  }
}
