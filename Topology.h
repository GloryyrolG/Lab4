#ifndef __TOPOLOGY_H__
#define __TOPOLOGY_H__

#include <bits/stdc++.h>

using namespace std;

class Course {
	friend class Topology;

	private:
		string no;
		string name;
		int hours, term;

	public:
		Course() {}
		~Course() {}
};

class Edge {
	public:
		int ed, nxt;

		Edge() {}
		~Edge() {}
};

const int maxn = 1010, maxm = 1010, maxl = 1010;

class Topology {
	private:
		int vcnt, ecnt[2];
		char data[maxl];
		string fin;
		int sup[9], rk[maxn], hed[2][maxn], in[2][maxn], lev[2][maxn], con[2][maxn], sum[2][10];
		bitset<maxn> anc[maxn];
		stack<int> S;
		priority_queue<pair<int, int> > Q;
		Edge e[2][maxm];
		vector<int> res;
		vector<int> ans[9];
		Course c[maxn];
		map<string, int> no;

		/*Topology() {}
		~Topology() {}*/

	public:
	    Topology() {}
		~Topology() {}
		int getNo(string & su);
		void addEdge(int u, int v, int no);
		bool isCh(char ch);
		string getString(int & i);
		int getInt(int & i);
		void readIn();
		bool cmpl(const int a, const int b);
		void qsort(int a[], int l, int r);
		int topoSort();
		void print();
		void solve(const string & fin);
};

#endif
