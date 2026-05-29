#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100

typedef struct {
    int cost;
    int fun;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int budget, n;
    
    while (1) {
        scanf("%d %d", &budget, &n);
        
        if (budget == 0 && n == 0) break;
        
        Item items[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &items[i].cost, &items[i].fun);
        }
        
        int dp[MAX_N + 1][MAX_N * MAX_N + 1];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= budget; w++) {
                dp[i][w] = dp[i-1][w];
                
                if (items[i-1].cost <= w) {
                    dp[i][w] = max(dp[i][w], dp[i-1][w - items[i-1].cost] + items[i-1].fun);
                }
            }
        }
        
        int maxFun = dp[n][budget];
        int minCost = budget;
        
        for (int w = 0; w <= budget; w++) {
            if (dp[n][w] == maxFun) {
                minCost = w;
                break;
            }
        }
        
        printf("%d %d\n", minCost, maxFun);
    }
    
    return 0;
}
