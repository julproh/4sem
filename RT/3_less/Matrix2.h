#include "Vector2D.h"

class Matrix2
{
private:
    double x1, y1, x2, y2;
public:
    Matrix2();
    Matrix2(double);
    Matrix2(double, double, double, double);
    ~Matrix2();
    void set_x1(double);
    void set_x2(double);
    void set_y1(double);
    void set_y2(double);
    double get_x1();
    double get_x2();
    double get_y1();
    double get_y2();
    Matrix2* operator*(double);
    Vector2D* operator*(Vector2D*);
    Matrix2* operator*(Matrix2*);
    Matrix2* operator+(double);
    Matrix2* operator+(Matrix2*);
    Matrix2* operator-(double);
    Matrix2* operator-(Matrix2*);
};