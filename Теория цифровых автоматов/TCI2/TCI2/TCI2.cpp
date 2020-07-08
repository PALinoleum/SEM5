my f_var2(int x1, int x2, int x3, int x4, int x5)
{
	my ff;

	int z1 = x2 && !x4;
	int z2 = x2 && x3;

	int u1 = x3 && z1;
	int u2 = !x3 && x4;
	int u3 = !x2 && x4;
	int u4 = x4 && !x5;
	int u5 = x3;
	int u6 = x3 && !x4;
	int u7 = !x4 && !x5;
	int u8 = z2 && !x5;
	int u9 = z1;

	int v1 = u1 || u2;
	int v2 = u3 || u4;
	int v3 = u6 || u7;
	int v4 = u8 || u9;

	int f1 = v2 || v1;
	int f2 = !u5;
	int f3 = v3 || v4;

	ff.f1 = f1;
	ff.f2 = f2;
	ff.f3 = f3;

	return ff;
}
int main()
{
	//f123(0, 1, 1, 0, 1);
	setlocale(LC_ALL, "Russian");
	int n = 5;
	int m = 32;
	auto a = GetTableTrue(m, n);
	fun(a, m, n);
	//auto arr = gt_lab6(a, m, n);
	//compsk(a, m, n);

	int nn = 5;
	int mm = 32;
	auto aa = GetTableTrue2(m, n);
	fun2(aa, mm, nn);

}