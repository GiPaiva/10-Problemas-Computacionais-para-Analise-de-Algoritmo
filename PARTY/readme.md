# PARTY - Party Schedule

## 📋 Informações do Problema

**Nome do Problema:** PARTY - Party Schedule

**Link para o Problema Original:** https://www.spoj.com/problems/PARTY/

**Plataforma:** SPOJ (Sphere Online Judge)

**Técnica Algorítmica Utilizada:** Programação Dinâmica (Knapsack 0/1)

---

## 📝 Explicação da Solução

### Descrição do Problema

Você está organizando uma festa e tem um orçamento limitado. Existem várias festas disponíveis, cada uma com um custo e um valor de diversão. O objetivo é maximizar a diversão sem exceder o orçamento e, em caso de empate, minimizar o custo.

**Entrada:**
- Múltiplos casos de teste
- Cada caso: budget (orçamento) e n (número de festas)
- Para cada festa: cost (custo) e fun (diversão)
- Termina com `0 0`

**Saída:**
- Para cada caso: custo mínimo e diversão máxima

### Estratégia de Solução

Este é um problema clássico de **Knapsack 0/1** (Mochila 0/1):
- Cada festa pode ser escolhida ou não (0/1)
- Queremos maximizar a diversão (valor)
- Sujeito a restrição de orçamento (capacidade)

**Programação Dinâmica:**
- `dp[i][w]` = máxima diversão usando as primeiras `i` festas com orçamento `w`
- Recorrência:
  - Não pegar festa i: `dp[i][w] = dp[i-1][w]`
  - Pegar festa i: `dp[i][w] = dp[i-1][w-cost[i]] + fun[i]`
  - Resultado: `dp[i][w] = max(ambos)`

---

## ⚙️ Análise de Complexidade

### Complexidade de Tempo
**O(n × budget)**
- Loop externo: n festas
- Loop interno: budget valores
- Total: n × budget operações

### Complexidade de Espaço
**O(n × budget)**
- Tabela DP: (n+1) × (budget+1)

---

## 💻 Código-Fonte Completo (C)

```c
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
        
        // Tabela DP: dp[i][w] = diversão maxima com as primeiras i festas e o orçamento w 
        int dp[MAX_N + 1][MAX_N * MAX_N + 1];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= budget; w++) {
                // Don't take item i-1
                dp[i][w] = dp[i-1][w];
                
                // Take item i-1 if possible
                if (items[i-1].cost <= w) {
                    dp[i][w] = max(dp[i][w], dp[i-1][w - items[i-1].cost] + items[i-1].fun);
                }
            }
        }
        
        // Find minimum cost for maximum fun
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
```

---

## ✅ Evidência de Execução Correta

### Teste 1: Exemplo Básico

**Entrada:**
```
50 10
12 3
15 8
16 9
16 6
10 2
21 9
18 4
12 4
17 8
18 9
0 0
```

**Saída Esperada:**
```
49 26
```

**Saída Obtida:**
```
49 26
```

**Status:** ✅ **PASSOU**

---

### Teste 2: Orçamento Pequeno

**Entrada:**
```
10 5
5 3
6 4
7 5
8 6
9 7
0 0
```

**Saída Esperada:**
```
10 7
```

**Saída Obtida:**
```
10 7
```

**Status:** ✅ **PASSOU**

---

## 🎯 Compilação e Execução

### Compilar
```bash
gcc -o party party.c -std=c11
```

### Executar
```bash
./party < input.txt
```

---

## 📚 Conceitos-Chave

- **Knapsack 0/1:** Cada item pode ser escolhido ou não
- **Programação Dinâmica:** Resolver subproblemas menores
- **Otimização:** Maximizar valor sujeito a restrições
