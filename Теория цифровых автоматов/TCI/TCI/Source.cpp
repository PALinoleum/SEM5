#include <iostream> 
#include <vector> 

using namespace std;

bool NextSet(int* a, int n, int m) {
	int j = m - 1;
	while (j >= 0 && a[j] == n) j--;
	if (j < 0) return false;
	if (a[j] >= n)
		j--;
	a[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		a[k] = 0;
	return true;
}

void Print(int* a, int n) {
	static int num = 1;
	cout.width(3);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}

void vectPrint(bool* vect, int n) {
	for (int i = 0; i <= n; i++)
		printf("%d ", vect[i]);
}

void vectXOR(bool* vect, bool* vect2, int n) {
	bool vectRes[32];
	for (int i = 0; i <= n; i++)
		vectRes[i] = vect[i] xor vect2[i];
	vectPrint(vectRes, n);
}

void printMatr1 (int matr[11][32]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 32; j++)
			printf("%i ", matr[i][j]);
		printf("\n");
	}
}

void printMatr2(int matr[10][32]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 32; j++)
			printf("%i ", matr[i][j]);
		printf("\n");
	}
}

void XORMatr(int matr[11][32], int xorm[10][32]) {
	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < 32; j++)
			xorm[i-1][j] = matr[0][j] xor matr[i][j];
	}
}

int treeCheck(int x[32]) {
	if (x[1] == 1)
		if (x[6] == 1)
			return 4;
		else
			if (x[10] == 0)
				return 9;
			else
				return 6;
	else
		if (x[25] == 0)
			if (x[29] == 0)
				return 8;
			else
				return 3;
		else
			if (x[30] == 0)
				if (x[5] == 0)
					return 5;
				else
					return 10;
			else
				if (x[18] == 1)
					return 7;
				else
					return 0;

}

bool gun(int* a, int n, int matr[11][32], int count, int x[32]) {
	Print(a, n);

	bool x1 = a[0], x2 = a[1], x3 = a[2], x4 = a[3], x5 = a[4];

	bool z1, z2, u1, u2, u3, u4, u5, u6, v1, v2, v3, v4, f;
	bool not_x1, not_x2, not_x3, not_x4, not_x5, not_z1, not_z2, not_u1, not_u2, not_v1, not_v2, not_v3, not_v4, not_f;

	bool zero = 0, one = 1;
	bool save;

	// исходная модель часично определенной будевой функцииции определенная через ДНФ

	u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[0][count] = f;

	printf(f ? "   1 " : "   0 ");

	// ДНФ x1 = 0

	u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[1][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x1 = 1

	u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[2][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x2 = 0

	u2 = zero and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = zero and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[3][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x2 = 1

	u2 = one and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = one and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[4][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x3 = 0

	u2 = x2 and !x4;
	u3 = zero and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = zero and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[5][count] = f;

	x[count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x3 = 1

	u2 = x2 and !x4;
	u3 = one and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = one and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[6][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x4 = 0

	u2 = x2 and !zero;
	u3 = x3 and !zero;
	u4 = !zero and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[7][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x4 = 1

	u2 = x2 and !one;
	u3 = x3 and !one;
	u4 = !one and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[8][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x5 = 0

	u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !zero;

	z1 = x2 and !zero;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[9][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// ДНФ x5 = 1

	u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !one;

	z1 = x2 and !one;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	matr[10][count] = f;

	// printf(f ? "   1 " : "   0 ");

	// исходная булева функция
	/*f = !x1 and x2 and x3 and !x5 or !x1 and x3 and !x4 or x2 and !x4 or !x4 and !x5;

	printf(f ? "   1 " : "   0 ");*/

	// минимальная ДНФ по неполной булевой функции

	/*f = x2 and x3 and !x5 or !x1 and x2 and !x5 or x2 and !x4 or x3 and !x4 or !x1 and !x4 or !x4 and !x5; 

	printf(f ? "   1 " : "   0 ");*/

	// минимальная КНФ по неполной булевой функции

	/*f = (!x1 or x3 or !x4) and (x2 or !x4) and (!x4 or !x5) and (!x1 or x2 or x3 or !x5);

	printf(f ? "   1 " : "   0 ");*/

	// ДНФ
	/*z1 = !x1 and x3;
	z2 = x2 and !x5;

	u1 = !x4 and !x5;
	u2 = !x4 and z1;
	u3 = z1 and z2;
	u4 = x2 and !x4;

	v1 = u1 or u4;
	v2 = u2 or u3;

	f = v1 or v2;

	printf(f ? "   1 " : "   0 ");*/

	// КНФ
	/*z1 = x2 or !x5;

	u1 = x3 or z1;
	u2 = !x1 or z1;
	u3 = x2 or !x4;
	u4 = x3 or !x4;
	u5 = !x1 or !x5;
	u6 = !x1 or !x4;

	v1 = u3 and u4;
	v2 = u5 and u6;
	v3 = v1 and v2;
	v4 = u1 and u2;

	f = v3 and v4;

	printf(f ? "   1 " : "   0 ");*/

	// неполная ДНФ

	/*u2 = x2 and !x4;
	u3 = x3 and !x4;
	u4 = !x4 and !x5;

	z1 = x2 and !x5;

	u1 = x3 and z1;

	v1 = u2 or u3;
	v2 = u1 or u4;

	f = v1 or v2;

	printf(f ? "   1 " : "   0 ");*/

	// неполная КНФ
	/*u2 = x2 or !x4;
	u3 = !x4 or !x5;

	z1 = !x1 or x3;
	z2 = x2 or !x5;

	u1 = !x4 or z1;
	u4 = z1 or z2;

	v1 = u2 and u3;
	v2 = u1 and u4;

	f = v1 and v2;

	printf(f ? "   1 " : "   0 ");*/

	// ДНФ -> И-НЕ
	/*not_x1 = !(x1 and x1);
	not_x4 = !(x4 and x4);
	not_x5 = !(x5 and x5);

	not_z1 = !(not_x1 and x3);
	z1 = !(not_z1 and not_z1);
	not_z2 = !(x2 and not_x5);
	z2 = !(not_z2 and not_z2);

	u2 = !(not_x4 and z1);
	u3 = !(z1 and z2);

	u1 = !(not_x4 and not_x5);
	u4 = !(x2 and not_x4);

	v1 = !(u1 and u4);
	v2 = !(u2 and u3);

	not_v1 = !(v1 and v1);
	not_v2 = !(v2 and v2);
	f = !(not_v1 and not_v2);

	printf(f ? "   1 " : "   0 ");*/

	// ДНФ -> ИЛИ-НЕ
	/*not_x2 = !(x2 or x2);
	not_x3 = !(x3 or x3);

	z1 = !(x1 or not_x3);
	z2 = !(not_x2 or x5);

	not_z1 = !(z1 or z1);
	not_z2 = !(z2 or z2);
	u2 = !(x4 or not_z1);
	u3 = !(not_z1 or not_z2);

	u1 = !(x4 or x5);
	u4 = !(not_x2 or x4);

	not_v1 = !(u1 or u4);
	not_v2 = !(u2 or u3);
	v1 = !(not_v1 or not_v1);
	v2 = !(not_v2 or not_v2);

	not_f = !(v1 or v2);
	f = !(not_f or not_f);

	printf(f ? "   1 " : "   0 ");*/

	// КНФ -> И-НЕ
	/*not_x2 = !(x2 and x2);
	not_x3 = !(x3 and x3);

	z1 = !(not_x2 and x5);

	u3 = !(not_x2 and x4);
	u4 = !(not_x3 and x4);
	u5 = !(x1 and x5);
	u6 = !(x1 and x4);

	not_z1 = !(z1 and z1);
	u1 = !(not_x3 and not_z1);
	u2 = !(not_z1 and x1);

	not_v1 = !(u3 and u4);
	v1 = !(not_v1 and not_v1);
	not_v2 = !(u5 and u6);
	v2 = !(not_v2 and not_v2);

	not_v3 = !(v1 and v2);
	v3 = !(not_v3 and not_v3);
	not_v4 = !(u1 and u2);
	v4 = !(not_v4 and not_v4);

	not_f = !(v3 and v4);
	f = !(not_f and not_f);

	printf(f ? "   1 " : "   0 ");*/

    // КНФ -> ИЛИ-НЕ
    /*not_x1 = !(x1 or x1);
	not_x4 = !(x4 or x4);
	not_x5 = !(x5 or x5);

	not_z1 = !(x2 or not_x5);
	z1 = !(not_z1 or not_z1);

	u3 = !(x2 or not_x4);
	u4 = !(x3 or not_x4);
	u5 = !(not_x1 or not_x5);
	u6 = !(not_x1 or not_x4);

	u1 = !(x3 or z1);
	u2 = !(z1 or not_x1);

	v1 = !(u3 or u4);
	v2 = !(u5 or u6);

	not_v1 = !(v1 or v1);
	not_v2 = !(v2 or v2);
	v3 = !(not_v1 or not_v2);
	v4 = !(u1 or u2);

	not_v3 = !(v3 or v3);
	not_v4 = !(v4 or v4);
	f = !(not_v3 or not_v4);

	printf(f ? "   1 " : "   0 ");*/

    printf("\n");
	return (f); 
}


int main() {
	vector<vector<int>*>* list = new vector<vector<int>*>();
	int* tmp;

	int matr[11][32];
	int xorm[10][32];
	int count = 0;

	int n = 1, m = 5, * a = new int[m];
	for (int i = 0; i < m; i++) a[i] = 0;

	int x[32];
	int p;

	int i = 0;
	gun(a, m, matr, count, x);
	while (NextSet(a, n, m)) {
		count++;
		gun(a, m, matr, count, x);
	}

	printf("\n");
	printMatr1(matr);
	printf("\n");
	XORMatr(matr, xorm);
	printMatr2(xorm);

	p = treeCheck(x);
	printf("\n");
	if (p == 0)
		printf("no errors found");
	else
		printf("error in %i case", p);

	return 0;
}