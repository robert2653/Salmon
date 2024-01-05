int N1, N2;				// 字串長度
int length[N1+1][N2+1];	// DP表格
int prev[N1+1][N2+1];	// 記錄每一格的的結果是從哪一格而來
int lcs[min(N1,N2)];

void LCS()
{
	for (int i=0; i<=N1; i++) length[i][0] = 0;
	for (int j=0; j<=N2; j++) length[0][j] = 0;

	for (int i=1; i<=N1; i++)
		for (int j=1; j<=N2; j++)
			if (s1[i] == s2[j])
			{
				length[i][j] = length[i-1][j-1] + 1;
				prev[i][j] = 0;	// 左上格
			}
			else
			{
				if (length[i-1][j] < length[i][j-1])
				{
					length[i][j] = length[i][j-1];
					prev[i][j] = 1;	// 左格
				}
				else
				{
					length[i][j] = length[i-1][j];
					prev[i][j] = 2;	// 上格
				}
			}

	print_LCS(N1, N2);
}
void print_LCS(int i, int j)
{
	int l = length[i][j];			// LCS長度
	while (l > 0)
		if (prev[i][j] == 0)		// 左上格
			l--, lcs[l] = s1[i];
		else if (prev[i][j] == 1)	// 左格
			j--;
		else if (prev[i][j] == 2)	// 上格
			i--;

	l = length[i][j];
	for (int i=0; i<l; ++i)
		cout << lcs[i];
}
int LCSLength(string X, string Y){
    int m = X.length(), n = Y.length();
    int curr[n + 1], prev;
    for (int i = 0; i <= m; i++)
    {
        prev = curr[0];
        for (int j = 0; j <= n; j++)
        {
            int backup = curr[j];
 
            if (i == 0 || j == 0) {
                curr[j] = 0;
            }
            else {
                if (X[i - 1] == Y[j - 1]) {
                    curr[j] = prev + 1;
                }
                else {
                    curr[j] = max(curr[j], curr[j - 1]);
                }
            }
            prev = backup;
        }
    }
    return curr[n];
}