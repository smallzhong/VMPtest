#include <iostream>
#include <string>
#include <cstring>
#define PM 998244353

using namespace std;

int dp[100010][10];
const string st = "nunhehheh";

int vis[100100];
long long Anum[100010];
long long nn[100010];

long long pt(long long sum) {
	if (sum == 1) {
		return nn[sum];
	}
	if (nn[sum]) return nn[sum];


	return nn[sum] = pt(sum - 1) * sum;
}


int main()
{
	int T;
	cin >> T;
	nn[0] = 1;
	for (int i = 1; i <= 1e5; i++) {
		nn[i] = 2 * nn[i - 1];
		nn[i] %= PM;
	}
	while (T--)
	{
		memset(vis, 0, sizeof(vis));
		memset(Anum, 0, sizeof(Anum));
		memset(dp, 0, sizeof(dp));
		string s, ss;
		cin >> s;

		ss = s;
		int pos = 0;
		int num = 0;
		dp[0][0] = 1;

		//找出序列中有多少个存在子序列
		for (int i = 0; i < ss.size() + 1; i++) {
			dp[i][0] = 1;
		}

		for (int i = 1; i < ss.size() + 1; i++) {
			for (int j = 1; j < st.size() + 1; j++) {
				if (ss[i - 1] == st[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
				else
					dp[i][j] = dp[i - 1][j];
			}
		}


		for (int i = 3; i < ss.size() + 1; i++) {
			if (dp[i][st.size()] != dp[i - 1][st.size()]) {
				vis[i] = dp[i][st.size()] - dp[i - 1][st.size()];
			}
		}
		pos = 0;
		num = 0;


		//确定每一个位置所含的a的数量
		for (auto c : ss) {
			if (num == 0) {
				if (c == 'a') {
					Anum[num] = 1;
				}
				else {
					Anum[num] = 0;
				}
				num++;
				continue;
			}
			if (c == 'a') {
				Anum[num] = Anum[num - 1] + 1;
			}
			else Anum[num] = Anum[num - 1];
			num++;
		}
		//       for(int i = 0; i < ss.size()+1; i++){
		//            cout<<dp[i][st.size()]<<" ";
		//       }
		//        cout<<"\n";
		//       for(int i = 0; i < ss.size()+1; i++){
		//            cout<<Anum[i]<<" ";
		//       }
		//       cout<<"\n";
		//
		//       for(int i = 0; i < ss.size()+1; i++){
		//            cout<<vis[i]<<" ";
		//       }
		//       cout<<"\n";

		num = 0;
		long long ans = 0;
		for (int i = 0; i < ss.size() + 1; i++) {
			if (!vis[i]) continue;
			//确定自某一为开始后a的数量
			int sst = i;
			int ssp = i - 1;
			int skk = ssp + 1;
			int sum = 0;//表示 a的数量
			skk <= ss.size() - 1 ? sum = Anum[ss.size() - 1] - Anum[ssp] : sum = 0;



			long long ansp = 1;
			long long pp = 1;


			//计算 方程
			if (sum >= 1)
				ansp = nn[sum] - 1;
			else
				continue;
			ans += ((ansp * vis[i])) % PM;
			ans %= PM;
		}

		cout << ans << "\n";
	}

	return 0;
}
