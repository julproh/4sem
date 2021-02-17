#include "Vector2D.h"

void Vector2D::set_x(double x)
{
    this->x = x;
}

void Vector2D::set_y(double y)
{
    this->y = y;
}

double Vector2D::get_x()
{
    return x;
}

double Vector2D::get_y()
{
    return y;
}

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double number)
{
    x = number;
    y = number;
}

Vector2D::Vector2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2D::~Vector2D()
{
    
}

Vector2D* Vector2D::operator*(double a)
{
    Vector2D* newVector = new Vector2D(a * this->get_x(), a * this->get_y());
    return newVector;
}

double Vector2D::operator*(Vector2D* a)
{
    return this->get_x() * a->get_x() + this->get_y() * a->get_y(); 
}

Vector2D* Vector2D::operator+(Vector2D* a)
{
    Vector2D* newVector = new Vector2D(this->get_x() + a->get_x(), this->get_y() + a->get_y());
    return newVector;
}

Vector2D* Vector2D::operator-(Vector2D* a)
{
    Vector2D* newVector = new Vector2D(this->get_x() - a->get_x(), this->get_y() - a->get_y());
    return newVector;
}

Vector2D* Vector2D::operator/(double a)
{
    Vector2D* newVector = new Vector2D(this->get_x() / a, this->get_y() / a);
    return newVector;
}