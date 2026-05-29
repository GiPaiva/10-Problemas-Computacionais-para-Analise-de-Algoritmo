# TRAFFICN - Traffic Network

## 📋 Informações do Problema

**Nome do Problema:** TRAFFICN - Traffic Network

**Link para o Problema Original:** https://www.spoj.com/problems/TRAFFICN/

**Plataforma:** SPOJ (Sphere Online Judge)

**Técnica Algorítmica Utilizada:** Algoritmo de Dijkstra (Caminho Mínimo)

---

## 📝 Explicação da Solução

### Descrição do Problema

Você precisa encontrar o caminho mais curto entre duas cidades em uma rede de tráfego. O grafo é não-direcionado (as estradas são bidirecionais) e ponderado (cada estrada tem um custo).

**Entrada:**
- Número de casos de teste
- Para cada caso:
  - n (número de cidades) e m (número de estradas)
  - m linhas com: u, v, w (estrada entre cidade u e v com custo w)

**Saída:**
- Para cada caso: custo mínimo da cidade 1 até a cidade n

### Estratégia de Solução

Utilizamos o **Algoritmo de Dijkstra** para encontrar o caminho mais curto:

**Funcionamento:**
1. Inicializar distâncias: dist[start] = 0, demais = ∞
2. Marcar todos os nós como não visitados
3. Repetir n vezes:
   - Escolher nó não visitado com menor distância
   - Marcar como visitado
   - Atualizar distâncias dos vizinhos: `dist[v] = min(dist[v], dist[u] + custo)`

**Por que Dijkstra?**
- Grafos com pesos positivos ✓
- Caminho mais curto de origem única ✓
- Eficiente: O(n²) com implementação simples

---

## ⚙️ Análise de Complexidade

### Complexidade de Tempo
**O(n²)**
- Loop principal: n iterações
- Busca do mínimo: O(n)
- Atualização de vizinhos: O(grau do nó)
- Total: O(n²)

*Nota: Com heap binário seria O((n + m) log n)*

### Complexidade de Espaço
**O(n + m)**
- Arrays dist e visited: O(n)
- Lista de adjacência: O(m)
- Total: O(n + m)

---

## 💻 Código-Fonte Completo (C)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define INF 1000000000

typedef struct {
    int to;
    int cost;
} Edge;

typedef struct {
    Edge edges[MAX_N];
    int size;
} AdjList;

AdjList adj[MAX_N];
int dist[MAX_N];
int visited[MAX_N];
int n;

void addEdge(int from, int to, int cost) {
    adj[from].edges[adj[from].size].to = to;
    adj[from].edges[adj[from].size].cost = cost;
    adj[from].size++;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void dijkstra(int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[start] = 0;
    
    for (int count = 0; count < n; count++) {
        int u = -1;
        int minDist = INF;
        
        // Find unvisited node with minimum distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        // Update distances to neighbors
        for (int i = 0; i < adj[u].size; i++) {
            int v = adj[u].edges[i].to;
            int cost = adj[u].edges[i].cost;
            
            if (!visited[v] && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int m;
        scanf("%d %d", &n, &m);
        
        // Initialize adjacency list
        for (int i = 0; i < n; i++) {
            adj[i].size = 0;
        }
        
        // Read edges
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            u--; v--; // Convert to 0-indexed
            addEdge(u, v, w);
            addEdge(v, u, w); // Undirected graph
        }
        
        // Run Dijkstra from node 0 (city 1)
        dijkstra(0);
        
        // Output distance to node n-1 (city n)
        printf("%d\n", dist[n-1]);
    }
    
    return 0;
}
```

---

## ✅ Evidência de Execução Correta

### Teste 1: Exemplo Básico

**Entrada:**
```
1
4 5
1 2 5
1 3 10
2 3 2
2 4 8
3 4 5
```

**Saída Esperada:**
```
12
```

**Explicação:**
- Caminho: 1 → 2 → 3 → 4
- Custo: 5 + 2 + 5 = 12

**Saída Obtida:**
```
12
```

**Status:** ✅ **PASSOU**

---

### Teste 2: Grafo Linear

**Entrada:**
```
1
5 4
1 2 10
2 3 20
3 4 30
4 5 40
```

**Saída Esperada:**
```
100
```

**Saída Obtida:**
```
100
```

**Status:** ✅ **PASSOU**

---

### Teste 3: Múltiplos Caminhos

**Entrada:**
```
1
3 3
1 2 100
2 3 100
1 3 50
```

**Saída Esperada:**
```
50
```

**Saída Obtida:**
```
50
```

**Status:** ✅ **PASSOU**

---

## 🎯 Compilação e Execução

### Compilar
```bash
gcc -o trafficn trafficn.c -std=c11
```

### Executar
```bash
./trafficn < input.txt
```

---

## 📚 Conceitos-Chave

### Algoritmo de Dijkstra
- **Objetivo:** Encontrar caminho mais curto de um nó origem para todos os outros
- **Requisito:** Pesos não-negativos
- **Estratégia:** Greedy - sempre escolhe o nó não visitado com menor distância

### Grafo Não-Direcionado
- Arestas bidirecionais
- Se existe aresta u→v, existe v→u com mesmo peso

### Lista de Adjacência
- Representação eficiente para grafos esparsos
- Cada nó mantém lista de vizinhos

---

## 📊 Visualização do Algoritmo

```
Grafo:
    1 --5-- 2
    |       |
   10       2
    |       |
    3 --5-- 4

Passo a Passo:
1. Iniciar: dist[1]=0, demais=∞
2. Visitar 1: atualizar dist[2]=5, dist[3]=10
3. Visitar 2: atualizar dist[3]=7, dist[4]=13
4. Visitar 3: atualizar dist[4]=12
5. Resultado: dist[4]=12
```