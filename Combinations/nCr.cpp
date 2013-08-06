int c[33][33] = { 0 };
/////no.1
void play_table(void)
{
  for (int i = 0; i <= 32; i++)
		for (int j = 0; j <= i; j++)
			if (!j || i == j)
				c[i][j] = 1;
			else
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	//  c[0][0]=0;  
	return;
}
/////no.2
int getcombination(int n, int m)
{
	int c[35];
	c[0] = 1;
	for (int k = 0; k <= m; k++)
	{
		c[k + 1] = c[k] * (n - k) / (k + 1);
	}
	return c[m];
}
