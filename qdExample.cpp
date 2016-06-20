#include <qd/qd_real.h>
#include <iostream>
#include <iomanip>

using namespace std;

qd_real newton(qd_real x0, qd_real eps, int n);
qd_real f(qd_real x);
qd_real df(qd_real x);

int main(void) {
	unsigned int old_cw;
	fpu_fix_start(&old_cw);
	cout << setprecision(64) << newton(-5.0, 1.0e-64, 50000) << endl;
	return 0;
}

qd_real f(qd_real x) {
	return sin(x) / (x - 1.0);
}

qd_real df(qd_real x) {
	return ((x - 1.0) * cos(x) - sin(x)) / ((x-1.0) * (x-1.0));
}

qd_real newton(qd_real x0, qd_real eps, int n) {
	qd_real xk = x0;
	qd_real xk1 = 0.0;
	int it = 0;
	for (it = 1; it < n; it++) {
		xk1 = xk - f(xk)/df(xk);
		if (abs(f(xk)) < eps) {
			break;
		} else {
			xk = xk1;
		}
		cout << "e_" << it << "=" << setprecision(64) << xk << endl;
	}
	return xk1;
}
