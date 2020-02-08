/*
 *  Date : 2020.02.08
 *  Language : C++
 *  Complexity : O(N^2)
 *  Data Structure : 
 *  Algorithm : 
 *
 *  Problem : https://www.algospot.com/judge/problem/read/HABIT
 */


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


//�� ���̻���� ù t ���ڸ� �������� �� �׷� ��ȣ�� �־��� ��,
//�־��� �� ���̻縦 ù 2 * t ���ڸ� �������� ���Ѵ�
//group[]�� ���̰� 0�� ���̻絵 �����Ѵ�
struct Comparator
{
	const vector<int> &group;
	int t;

	Comparator(const vector<int> &_group, int _t) :group(_group), t(_t)
	{
	}

	bool operator()(int a, int b)
	{
		//ù t ���ڰ� �ٸ��� �̵��� �̿��� ��
		if (group[a] != group[b])
			return group[a] < group[b];
		//�ƴ϶�� S[a+t..]�� S[b+t..]�� ù t ���ڸ� ��
		return group[a + t] < group[b + t];
	}
};

//s�� ���̻� �迭�� ���
vector<int> getSuffixArray(const string &s)
{
	int n = s.size();
	//group[i] = ���̻���� ù t ���ڸ� �������� �������� ��, S[i..]�� ���� �׷� ��ȣ
	//t=1�� ���� ������ �� ���� S[i..]�� ù ���ڷ� �׷� ��ȣ�� ���� �൵ ���� ȿ��
	int t = 1;

	vector<int> group(n + 1);

	for (int i = 0; i < n; i++)
		group[i] = s[i];

	group[n] = -1;
	//��������� ���̻� �迭�� �� ��ȯ ��. �� �迭�� lg(n)�� ����
	vector<int> perm(n);

	for (int i = 0; i < n; i++)
		perm[i] = i;

	while (t < n)
	{
		//group[]�� ù t ���ڸ� �������� ���
		//ù 2t ���ڸ� �������� perm�� �ٽ� ����
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

		//2t ���ڰ� n�� �Ѵ´ٸ� ���� ���̻� �迭 �ϼ�
		t *= 2;

		if (t >= n)
			break;

		//2t ���ڸ� �������� �� �׷� ������ �����
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; i++)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}

//s[i..]�� s[j..]�� ���� ���λ��� �ִ� ���� ���
int commonPrefix(const string &s, int i, int j)
{
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j])
		i++, j++, k++;

	return k;
}

//k�� �̻� �����ϴ� s�� �κ� ���ڿ� �� �ִ� ���̸� ã�´�
int longestFrequent(int k, const string &s)
{
	vector<int> a = getSuffixArray(s);
	int result = 0;

	for (int i = 0; i + k <= s.size(); i++)
		result = max(result, commonPrefix(s, a[i], a[i + k - 1]));

	return result;
}

int main(void)
{
	int test_case;
	cin >> test_case;

	for (int i = 0; i < test_case; i++)
	{
		int K;
		string S;

		cin >> K >> S;
		cout << longestFrequent(K, S) << endl;
	}

	return 0;
}