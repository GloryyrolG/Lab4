#include "Topology.h"

using namespace std;

int Topology::getNo(string & su) {
	if (no.find(su) == no.end()) {
		no[su] = vcnt ++;
	}
	return no[su];
}

void Topology::addEdge(int u, int v, int no) {
	in[no][v] ++;
	e[no][ecnt[no]].ed = v;
	e[no][ecnt[no]].nxt = hed[no][u];
	hed[no][u] = ecnt[no] ++;
}

bool Topology::isCh(char ch) {
	//return (ch >= 'a' && ch <= 'z') || (ch >= 'A' ch <= 'Z') || (ch >= '0' && ch <= '9');
	return !(ch == ' ' || ch == '\t');
}

string Topology::getString(int & i) {
	string str = "";
	for (; data[i] && !isCh(data[i]); i ++);
	for (; data[i]; i ++) {
		if (!isCh(data[i])) {
			break;
		}
		str = str + data[i];
	}
	return str;
}

int Topology::getInt(int & i) {
	int x = 0;
	for (; data[i] && !isCh(data[i]); i ++);
	for (; data[i]; i ++) {
		if (!isCh(data[i])) {
			break;
		}
		x = x * 10 + data[i] - '0';
	}
	return x;
}

void Topology::readIn() {
	freopen(fin.c_str(), "r", stdin);
	string str;
	int i, sz;
	for (i = 1; i <= 8; i ++) {
		scanf("%d", &sup[i]);
	}
	cin.getline(data, 1010);
	for (; 1; ) {
		cin.getline(data, 1010);
		if (!(sz = strlen(data))) {
			break;
		}
		int uno = getNo(str = getString(i = 0));
		c[uno].no = str;
		c[uno].name = getString(++ i);
		c[uno].hours = getInt(++ i);
		c[uno].term = getInt(++ i);
		for (; i < sz; ) {
            str = getString(++ i);
            if (!str.length()) {
				break;
			}
			int vno = getNo(str);
			addEdge(vno, uno, 0);
			addEdge(uno, vno, 1);
		}
	}
	freopen("CON", "r", stdin);
}

/*bool Topology::cmp(const int a, const int b) {
	return lev[0][a] < lev[0][b] || (lev[0][a] == lev[0][b] && lev[1][a] < lev[1][b]);
}*/

bool Topology::cmpl(const int a, const int b) {
	return lev[0][a] < lev[0][b] || (lev[0][a] == lev[0][b] && lev[1][a] < lev[1][b]);
}

void Topology::qsort(int a[], int l, int r) {
	int i = l, j = r, mid = a[(l + r) >> 1], t;
	for (; i <= j; ) {
		for (; cmpl(a[i], mid); i ++);
		for (; cmpl(mid, a[j]); j --);
		if (i <= j) {
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			i ++;
			j --;
		}
	}
	if (l < j) {
		qsort(a, l ,j);
	}
	if (i < r) {
		qsort(a, i, r);
	}
}

int Topology::topoSort() {
	int i, j;
	for (i = 0; i < vcnt; i ++) {
		if (c[i].term) {
			lev[0][i] = c[i].term;
			lev[1][i] = 9 - c[i].term;
		}
		anc[i].reset();
	}
	for (i = 0; i < 2; i ++) {
		for (; !S.empty(); S.pop());
		for (j = 0; j < vcnt; j ++) {
			if (!in[i][j]) {
				if (!lev[i][j]) {
					lev[i][j] = 1;
				}
				S.push(j);
			}
			else {
				if (!lev[i][j]) {
					lev[i][j] = 8;
				}
			}
		}
		for (; !S.empty(); ) {
			int u = S.top();
			S.pop();
			int v;
			for (j = hed[i][u]; j != -1; j = e[i][j].nxt) {
				v = e[i][j].ed;
				//con[i][v] += con[i][u] + 1;     // ?
				if (!c[v].term) {
					lev[i][v] = min(lev[i][v], lev[i][u] + 1);
				}
				if (!i) {
                    anc[v] |= anc[u];
                    anc[v][u] = 1;
				}
				if (!(-- in[i][v])) {
					S.push(v);
				}
			}
		}
	}
	for (i = 1; i <= 8; i ++) {
		sum[0][i] = sum[0][i - 1] + sup[i];
	}
	for (i = 8; i >= 1; i --) {
		sum[1][i] = sum[1][i + 1] + sup[i];
	}
	/*for (i = 0; i < 2; i ++) {
		for (j = 0; j < vcnt; j ++) {
			int pos = upper_bound(sum[i] + 1, sum[i] + 9, con[i][j]) - sum[i];
			if (pos == 9) {
                cout << j << ' ' << i << ' ' << con[i][j] << endl;
				return -1;
			}
			lev[i][j] = max(lev[i][j], pos);
		}
	}*/
	for (i = 0; i < vcnt; i ++) {
		lev[1][i] = 9 - lev[1][i];
	}
	for (i = 0; i < vcnt; i ++) {
		rk[i] = i;
	}
	qsort(rk, 0, vcnt - 1);
	for (i = 1, j = 0; i <= 8; i ++) {
		for (; j < vcnt && lev[0][rk[j]] <= i; j ++) {
			Q.push(make_pair(-lev[1][rk[j]], rk[j]));
		}
		bool flag;
		int x, u;
		for (x = sup[i]; x; x --) {
            res.clear();
            for (; 1; ) {
                if (Q.empty()) {
                    return -1;
                }
                u = (Q.top()).second;
                flag = 0;
                for (int v: ans[i]) {
                    if (anc[u][v] || anc[v][u]) {
                        flag = 1;
                        break;
                    }
                }
                Q.pop();
                if (flag) {
                    res.push_back(u);
                }
                else {
                    for (int v: res) {
                        Q.push(make_pair(-lev[1][v], v));
                    }
                    break;
                }
            }
			ans[i].push_back(u);
		}
	}
	return 0;
}

void Topology::print() {
	for (int i = 1; i <= 8; i ++) {
		printf(">>> %d: ", i);
		for (int j: ans[i]) {
			cout << c[j].name << '\t';
		}
		printf("\n");
	}
}

void Topology::solve(const string & fin) {
	this->fin = fin;
	vcnt = ecnt[0] = ecnt[1] = 0;
	memset(hed, -1, sizeof(hed));
	memset(in, 0, sizeof(in));
	memset(lev, 0, sizeof(lev));
	memset(con, 0, sizeof(con));
	int i;
	for (i = 1; i <= 8; i ++) {
		ans[i].clear();
	}
	no.clear();
	for (; !Q.empty(); Q.pop());
	readIn();
	if (topoSort() == -1) {
        printf("Error!\n");
	}
	else {
        print();
	}
}
