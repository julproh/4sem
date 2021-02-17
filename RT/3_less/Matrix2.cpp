#include "Matrix2.h"

void Matrix2::set_x1(double x1)
{
    this->x1 = x1;
}

void Matrix2::set_y1(double y1)
{
    this->y1 = y1;
}

double Matrix2::get_x1()
{
    return x1;
}

double Matrix2::get_y1()
{
    return y1;
}

void Matrix2::set_x2(double x1)
{
    this->x1 = x1;
}

void Matrix2::set_y2(double y1)
{
    this->y1 = y1;
}

double Matrix2::get_x2()
{
    return x1;
}

double Matrix2::get_y2()
{
    return y1;
}

Matrix2::Matrix2()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
}

Matrix2::Matrix2(double number)
{
    x1 = number;
    x2 = number;
    y1 = number;
    y2 = number;
}

Matrix2::Matrix2(double x1, double x2, double y1, double y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

Matrix2::~Matrix2()
{
    
}

Matrix2* Matrix2::operator*(double a)
{
    Matrix2* newMatrix = new Matrix2(a * this->get_x1(), a * this->get_x2(), a * this->get_y1(), a * this->get_y2());
    return newMatrix;
}

Vector2D* Matrix2::operator*(Vector2D* a)
{
    Vector2D* newMatrix = new Vector2D(this->get_x1() * a->get_x() + this->get_x2() * a->get_y(), this->get_y1() * a->get_x() + this->get_y2() * a->get_y());
    return newMatrix; 
}

Matrix2* Matrix2::operator*(Matrix2* a)
{
    Matrix2* newMatrix = new Matrix2(this->get_x1() * a->get_x1() + this->get_x2() * a->get_y1(), this->get_x1() * a->get_x2() + this->get_x2() * a->get_y2(), this->get_y2() * a->get_x1() + this->get_y2() * a->get_y1(), this->get_y2() * a->get_x2() + this->get_y2() * a->get_y2());
    return newMatrix; 
}

Matrix2* Matrix2::operator+(double a)
{
    Matrix2* newMatrix = new Matrix2(this->get_x1() + a, this->get_x2() + a, this->get_y1() + a, this->get_y2() + a);
    return newMatrix;
}

Matrix2* Matrix2::operator+(Matrix2* a)
{
    Matrix2* newMatrix = new Matrix2(this->get_x1() + a->get_x1(), this->get_x2() + a->get_x2(), this->get_y1() + a->get_y1(), this->get_y2() + a->get_y2());
    return newMatrix;
}

Matrix2* Matrix2::operator-(double a)
{
    Matrix2* newMatrix = new Matrix2(this->get_x1() - a, this->get_x2() - a, this->get_y1() - a, this->get_y2() - a);
    return newMatrix;
}

Matrix2* Matrix2::operator-(Matrix2* a)
{
    Matrix2* newMatrix = new Matrix2(this->get_x1() - a->get_x1(), this->get_x2() - a->get_x2(), this->get_y1() - a->get_y1(), this->get_y2() - a->get_y2());
    return newMatrix;
}

/*Matrix2* Matrix2::operator/(double a)
{
    Vector2D* newVector = new Matrix2(this->get_x() / a, this->get_y() / a);
    return newVector;
}*/