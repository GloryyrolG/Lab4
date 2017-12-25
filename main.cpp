#include "Topology.h"

using namespace std;

int main() {
    FILE* fp;
    string fin;
    for (; 1; ) {
        for (; 1; ) {
            cout << ">>>Please input the filename: ";
            cin >> fin;
            if (fp = fopen(fin.c_str(), "rb")) {
                fclose(fp);
                break;
            }
            cout << "File does not exist!" << endl;
            fclose(fp);
        }
        Topology work;
        work.solve(fin);
    }
	return 0;
}

/*
course_inf.txt
*/
