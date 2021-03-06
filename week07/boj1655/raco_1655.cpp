/*
 *  BOJ 1655. 가운데를 말해요
 *
 *  시간복잡도 : O(NlogN)
 *  
 *  mxh, mih을 만들고 mih의 값들은 항상 모든 mxh의 원소들보다 크다.
 *  둘의 사이즈가 같으면 mxh에 값을 넣어주고, 아니면 mih에 값을 넣어준다.
 *  mih.top()보다 mxh.top()의 값이 크면 둘의 값을 swap한다.
 *  이런식으로 N만큼 반복하면서 mxh.top()을 출력해 주면 된다.
 *  
 */

#include <iostream>
#include <queue>
using namespace std;

int N;
priority_queue<int> mih, mxh;// minHeap, maxHeap

int main() {
	cin >> N;
	int a;
	for (int i = 0; i < N; i++) {
		cin >> a;
		if (mih.size() == mxh.size()) mxh.push(a);
		else mih.push(-a);
		if (!mih.empty() && !mxh.empty() && -mih.top() < mxh.top()) {
			int t = mxh.top();
			mxh.pop();
			mxh.push(-mih.top());
			mih.pop();
			mih.push(-t);
		}
		cout << mxh.top() << '\n';
	}
	return 0;
}