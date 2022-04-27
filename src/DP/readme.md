## 背包问题

 1. 0-1背包问题

 问题：
 有 n 个物品和一个容量为 W 的背包，每个物品有重量 w_i 和 价值 v_i 两种属性，
 要求选若干物品放入背包，使得背包中物品的总价值最大而且背包中物品的总重量不超过背包容量。
  每个物品只有取与不取两种状态，对应二进制0和1，所以问题也称为「0-1背包问题」
 
  转移方程：
  设DP状态 f[i][j] 为在只放了前 i 个物品的情况下，容量为 j 的背包所能达到的最大价值。
  状态转移：假设当前已经处理好前 i-1 个物品，那么对于第 i 个物品，
   1. 当其不放人背包时，背包的剩余容量不变，背包中物品的总价值也不变，此时最大价值为 f[i-1][j]
   2. 当其放入背包时，背包的剩余容量会减少 w[i]，背包物品的总价值会增加 v[i]，此时最大价值为 f[i-1][j-w[i]] + v[i]
   故状态转移方程为：f[i][j] = max(dp[i-1][j], f[i-1][j-w[i]] + v[i]) // 这里假设重量和价值数组都从下标1开始
 
  优化：因为对 f[i] 有影响的只有 f[i-1], 所以可以去掉第一维，直接用 f[i] 来表示处理当前物品时，背包容量为 i 的最大价值。
  得到转移方程为：
   f[j] = max(f[j], f[j-w[i]] + v[i])
 
  核心代码：
  ```
   for(int i = 1; i <= n; i++)
     for(int c = W; c >= w[i]; c--) // 注意：这里必须是从W到w[i]，否则一个物品会被多次放入背包。
       f[c] = max(f[c], f[c-w[i]]+v[i])
  ```

  常见错误实现：
  ```
   for(int i = 1; i <= n; i++)
     for(int c = 0; c <= W - w[i]; c++)
       f[c+w[i]] = max(f[c] + v[i], f[c + w[i]]); // f[i][l + w[i]] = max(max(f[i - 1][l + w[i]],f[i - 1][l] + w[i]),f[i][l + w[i]])
  ```   
   原因：当前处理物品 i 和 当前状态 f[i][j]，在 j>=w[i]时，f[i][j]是会被f[i][j-w[i]]所影响的。相当于物品 i 可以被多次放入背包（完全背包问题）。
   为了避免这种情况，可以改变枚举顺序，从W枚举到w[i]。这样就不会出现这种情况，因为 f[i][j] 总在 f[i][j-w[i]] 之前被更新。
 

  完全背包问题
  问题：
  完全背包模型与 0-1 背包类似，与 0-1 背包的区别仅在于一个物品可以选取无限次，而非仅能选取一次。
 
  状态定义： 设 f[i][j] 为只能选前 i 个物品时，容量为 j 的背包可以达到的最大价值。
  转移方程：f[i][j] = max(f[i-1][j - kw[i] + kv[i]) k <= 0 < inf
 
  优化：对于f[i][j] 只要通过 f[i][j-w[i]] 转移就可以了，
  因为 f[i][j-w[i]] 已经由 f[i][j-2w[i]]更新过，那么 f[i][j-w[i]] 就是充分考虑了第 i 件物品所选次数后得到的最优结果。
  换言之，我们通过局部最优子结构的性质重复使用了之前的枚举过程，优化了枚举的复杂度。
 
  优化的状态转移方程为：f[i][j] = max(f[i-1][j], f[i][j-w[i]]+v[i])
 
  核心代码：
  ```
     for (int i = 1; i <= n; i++)
       for (int c = w[i]; c <= W; l++)
         f[c] = max(f[c], f[c-w[i]] + v[i])  // if (f[l - w[i]] + v[i] > f[l]) f[l] = f[l - w[i]] + v[i];
  ```



## 数学模型

给定一个$ n $个元素的集合，和一个背包knapsack，其中有：
$$ p_j = profit \; of\; itme\; j $$
$$ w_j = weight\; of\; itme\; j $$
$$ c = capacity\; of\; the\; knapsack\; j $$

选取一个子集使得下面线性规划成立:
$$ maximize \space  z = \sum_{j=1}^{n} p_jx_j $$
$$ s.t. \space \sum_{j=1}^{n}w_jx_j \leq c $$
$$ x_j = 0 \space or \space 1, j \in N = \{1, \dots n\} $$

$$x_j= \left\{
  \begin{matrix} & 1 & if \; item \; i \; is \; selected\\
  & 0 & otherwise
  \end{matrix}\right.
$$

It can be viewed as the most simplest Interger Linear Programming problem;