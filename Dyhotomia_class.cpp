#include "Dyhotomia_class.h"
#include <cmath>
#include <iostream>
using namespace std;

Dyhotomia_class::Dyhotomia_class(void) {
    a = 1.0;
    b = 2.0;
    eps = 1e-6;
}

Dyhotomia_class::~Dyhotomia_class(void) {}

void Dyhotomia_class::setVolumes(double vol_a, double vol_b) {
    a = vol_a;
    b = vol_b;
}

void Dyhotomia_class::setTolerance(double vol_eps) {
    eps = vol_eps;
}

double Dyhotomia_class::calcFunction(double x) {
    if (x == 0) return NAN;
    return cos(2.0 / x) - 2.0 * sin(1.0 / x) + 1.0 / x;
}

double Dyhotomia_class::derivate(double x) {
    return (calcFunction(x + eps) - calcFunction(x)) / eps;
}

double Dyhotomia_class::calcRoot() {
    double a = this->a;
    double b = this->b;

    if (calcFunction(a) * calcFunction(b) > 0)
        return NAN;

    double c;
    do {
        c = (a + b) / 2.0;
        if (calcFunction(a) * calcFunction(c) > 0)
            a = c;
        else
            b = c;
    } while ((b - a) > eps);

    return (a + b) / 2.0;
}

double Dyhotomia_class::calcRootNewton() {
    if (calcFunction(a) * calcFunction(b) > 0)
        return NAN;

    double x = b;

    while (fabs(calcFunction(x)) > eps) {
        double d = derivate(x);
        if (fabs(d) < 1e-12) return NAN;
        x -= calcFunction(x) / d;
    }

    return x;
}

void Dyhotomia_class::run() {
    setVolumes(1.0, 2.0);
    setTolerance(1e-6);

    cout << "Function: f(x) = cos(2/x) - 2*sin(1/x) + 1/x" << endl;
    cout << "Interval: [" << a << "; " << b << "]" << endl;
    cout << "Tolerance: " << eps << endl << endl;

    double rootBis    = calcRoot();
    double rootNewton = calcRootNewton();

    if (!isnan(rootBis))
        cout << "Bisection method: x = " << rootBis << endl;
    else
        cout << "Bisection method: no root found on interval" << endl;

    if (!isnan(rootNewton))
        cout << "Newton's method:  x = " << rootNewton << endl;
    else
        cout << "Newton's method: no root found on interval" << endl;
}