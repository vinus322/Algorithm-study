
//
//  algo_jaehasafe.cpp
//  알고리즘 문제해결전략 - 재하의 금고
//
//  Created by Hubring on 2020. 2. 8.
//  Copyright © 2020년 Hubring. All rights reserved.
// 
//  시간복잡도 :  O( N * (|L| + |L*2|) )  1<= N <=100 , 1<= L <=10000

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>
using namespace std;


//KMP 알고리즘 부분일치 테이블 생성
//시간복잡도 O(|N|)
vector<int> getPartialMatch(const string& N) {
	int size = N.size();
	vector<int> pi(size, 0);

	int begin = 1, matched = 0;

	while (begin+matched < size) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched - 1];
			}
		}

	}

	return pi;
}

//시간복잡도 O(|N|) + O(|H|) = O(|N| + |H|)
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();

	vector<int> ret;

	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;

	//반복문 시간복잡도 O(|H|)
	while (begin<=n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			matched++;
			//모두 일치했을 경우 결과에 추가
			if (matched == m) ret.push_back(begin); 
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return ret;

}

int shifts(const string& original, const string& target) {
	return kmpSearch(original+ original, target)[0];
}


/// <summary>
///	원형의 다이얼 금고가 주어지며, 시계방향 혹은 반시계방향으로 돌린 후의 금고를 열어야할 상태가 여러개 주어질때
/// 최종 다이얼을 돌리는 횟수를 구하여라 (처음 시계방향으로 돌리며 다음상태는 이전상태와 반대방향으로 돌린다.)
/// </summary>
///<param name = 'n'>다디얼 상태 수< / param>
///<param name = 'states'> 금고의 상태< / param>
int solveJaehasafe(int n, vector<string> states) {

	int ret = 0;
	bool isClockwise = true; 

	for (int i = 0; i < n; i++) {
		string currState = states[i];
		string nextState = states[i+1];
		int cnt;

		if (!isClockwise) {
			//반시계방향
			cnt = shifts(currState, nextState);
		}
		else {
			//시계방향
			cnt = shifts(nextState, currState);
		}
		ret += cnt;
		isClockwise = !isClockwise;
	}
	return ret;
}


void solve() {
	int n;
	vector<string> states;
	cin >> n;
	for (int i = 0; i <= n; i++) {
		string state;
		cin >> state;
		states.push_back(state);
	}

	cout << solveJaehasafe(n, states) << endl;
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}