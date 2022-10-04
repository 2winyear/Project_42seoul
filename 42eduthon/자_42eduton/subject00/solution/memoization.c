long long dp[91] = {0, 1};
long long fibbonacci_dynamic(int n) {
  if (dp[n] || n < 2) return dp[n];
  return dp[n] = fibbonacci_dynamic(n - 2) + fibbonacci_dynamic(n - 1);
}