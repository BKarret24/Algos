#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>

int main() {
    double x1 = 1.0;
    double y1 = 1.0;
    double r1 = 1.0;
    double x2 = 1.5;
    double y2 = 2.0;
    double r2 = std::sqrt(5.0) / 2.0;
    double x3 = 2.0;
    double y3 = 1.5;
    double r3 = std::sqrt(5.0) / 2.0;
    double S_exact;
    {
        double pi = std::acos(-1.0);
        double part1 = 0.25 * pi;
        double part2 = 1.25 * std::asin(0.8);
        double part3 = 1.0;
        S_exact = part1 + part2 - part3;
    }

    double wide_xmin = x1 - r1;
    if (x2 - r2 < wide_xmin) {
        wide_xmin = x2 - r2;
    }
    if (x3 - r3 < wide_xmin) {
        wide_xmin = x3 - r3;
    }
    double wide_xmax = x1 + r1;
    if (x2 + r2 > wide_xmax) {
        wide_xmax = x2 + r2;
    }
    if (x3 + r3 > wide_xmax) {
        wide_xmax = x3 + r3;
    }
    double wide_ymin = y1 - r1;
    if (y2 - r2 < wide_ymin) {
        wide_ymin = y2 - r2;
    }
    if (y3 - r3 < wide_ymin) {
        wide_ymin = y3 - r3;
    }
    double wide_ymax = y1 + r1;
    if (y2 + r2 > wide_ymax) {
        wide_ymax = y2 + r2;
    }
    if (y3 + r3 > wide_ymax) {
        wide_ymax = y3 + r3;
    }

    double tight_xmin = 0.88;
    double tight_xmax = 2.00;
    double tight_ymin = 0.88;
    double tight_ymax = 2.00;
    std::ofstream out_wide("wide_results.csv");
    std::ofstream out_tight("tight_results.csv");
    out_wide << "N,оценочно,погрешность\n";
    out_tight << "N,оценочно,погрешность\n";
    std::mt19937_64 rng(139);
    for (int n = 100; n <= 100000; n += 500) {
        long long inside_wide = 0;
        long long inside_tight = 0;
        double wx = wide_xmax - wide_xmin;
        double wy = wide_ymax - wide_ymin;
        double tx = tight_xmax - tight_xmin;
        double ty = tight_ymax - tight_ymin;
        std::mt19937_64 rng_wide = rng;
        std::mt19937_64 rng_tight = rng;

        for (int i = 0; i < n; i++) {
            double rx = rng_wide() / double(std::mt19937_64::max());
            double ry = rng_wide() / double(std::mt19937_64::max());
            double xx = wide_xmin + wx * rx;
            double yy = wide_ymin + wy * ry;
            bool ok1 = ((xx - x1)*(xx - x1) + (yy - y1)*(yy - y1) <= r1*r1);
            bool ok2 = ((xx - x2)*(xx - x2) + (yy - y2)*(yy - y2) <= r2*r2);
            bool ok3 = ((xx - x3)*(xx - x3) + (yy - y3)*(yy - y3) <= r3*r3);
            if (ok1 && ok2 && ok3) {
                inside_wide++;
            }
        }
        double sq_wide = wx * wy;
        double sq_pogr_wide = sq_wide * (double(inside_wide) / double(n));
        double err_wide = std::fabs(sq_pogr_wide - S_exact) / S_exact;
        out_wide << n << "," << std::setprecision(15)
                 << sq_pogr_wide << "," << err_wide << "\n";

        for (int i = 0; i < n; i++) {
            double rx = rng_tight() / double(std::mt19937_64::max());
            double ry = rng_tight() / double(std::mt19937_64::max());
            double xx = tight_xmin + tx * rx;
            double yy = tight_ymin + ty * ry;
            bool ok1 = ((xx - x1)*(xx - x1) + (yy - y1)*(yy - y1) <= r1*r1);
            bool ok2 = ((xx - x2)*(xx - x2) + (yy - y2)*(yy - y2) <= r2*r2);
            bool ok3 = ((xx - x3)*(xx - x3) + (yy - y3)*(yy - y3) <= r3*r3);
            if (ok1 && ok2 && ok3) {
                inside_tight++;
            }
        }
        double sq_tight = tx * ty;
        double sq_pogr_tight = sq_tight * (double(inside_tight) / double(n));
        double err_tight = std::fabs(sq_pogr_tight - S_exact) / S_exact;
        out_tight << n << "," << std::setprecision(15)
                  << sq_pogr_tight << "," << err_tight << "\n";
    }
    return 0;
}