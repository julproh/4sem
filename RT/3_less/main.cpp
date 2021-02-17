#include <iostream>
#include "Matrix2.h"

double sum(double x, double y)
{
    return x + y;
};

Vector2D* sum(Vector2D* a, Vector2D* b)
{
    Vector2D* newVector = new Vector2D(a->get_x() + b->get_x(), a->get_y() + b->get_y());
    return newVector;
};

int main()
{
    /*Vector2D* null = new Vector2D();
    Vector2D* a = new Vector2D(2);
    Vector2D* b = new Vector2D(0, 2);

    std::cout << "Vector null: " << null->get_x() << " "<< null->get_y() << std::endl;

    std::cout << "Vector a: " << a->get_x() << " "<< a->get_y() << std::endl;

    std::cout << "Vector b: " << b->get_x() << " "<< b->get_y() << std::endl;

    std::cout << "Sum 1.5 + 3.4566: " << sum(1.5, 3.4566) << std::endl;

    Vector2D* Sum = *a + b;
    std::cout << "Sum vector a and vector b: " << Sum->get_x() << " "<< Sum->get_y() << std::endl;

    Vector2D* Sub = *a - b;
    std::cout << "Subtraction vector a and vector b: " << Sub->get_x() << " "<< Sub->get_y() << std::endl;

    Vector2D* Mul = *a * 5.5;
    std::cout << "Multiplication vector a and double 5.5: " << Mul->get_x() << " "<< Mul->get_y() << std::endl;

    Vector2D* Mulv = *a * 5.5;
    std::cout << "Multiplication vector a and vector b: "<< Mulv->get_x() << " "<< Mulv->get_y() << std::endl;

    Vector2D* Div = *a / 5.5;
    std::cout << "Division vector a and double 5.5: " << Div->get_x() << " "<< Div->get_y() << std::endl;*/


    
    Matrix2* null = new Matrix2();
    Matrix2* a = new Matrix2(2);
    Matrix2* b = new Matrix2(1, 2, 3, 4);

    std::cout << "Matrix null:" << std::endl;
    std::cout << null->get_x1() << " "<< null->get_x2() << std::endl;
    std::cout << null->get_y1() << " "<< null->get_y2() << std::endl;

    std::cout << "Matrix a:" << std::endl;
    std::cout << a->get_x1() << " "<< a->get_x2() << std::endl;
    std::cout << a->get_y1() << " "<< a->get_y2() << std::endl;

    std::cout << "Matrix b:" << std::endl;
    std::cout << b->get_x1() << " "<< b->get_x2() << std::endl;
    std::cout << b->get_y1() << " "<< b->get_y2() << std::endl;

    Matrix2* Sum = *a + 5.5;
    std::cout << "Sum matrix a and double 5.5: " << std::endl;
    std::cout << Sum->get_x1() << " "<< Sum->get_x2() << std::endl;
    std::cout << Sum->get_y1() << " "<< Sum->get_y2() << std::endl;
    
    Matrix2* Summ = *a + b;
    std::cout << "Sum matrix a and matrix b: " << std::endl;
    std::cout << Summ->get_x1() << " "<< Summ->get_x2() << std::endl;
    std::cout << Summ->get_y1() << " "<< Summ->get_y2() << std::endl;

    Matrix2* Sub = *a - 5.5;
    std::cout << "Substraction matrix a and double 5.5 b: " <<  std::endl;
    std::cout << Sub->get_x1() << " "<< Sub->get_x2() << std::endl;
    std::cout << Sub->get_y1() << " "<< Sub->get_y2() << std::endl;

    Matrix2* Subm = *a - b;
    std::cout << "Substraction matrix a and matrix b: " <<  std::endl;
    std::cout << Subm->get_x1() << " "<< Subm->get_x2() << std::endl;
    std::cout << Subm->get_y1() << " "<< Subm->get_y2() << std::endl;

    Matrix2* Mul = *a * 5.5;
    std::cout << "Multiplication matrix a and double 5.5: " << std::endl;
    std::cout << Mul->get_x1() << " "<< Mul->get_x2() << std::endl;
    std::cout << Mul->get_y1() << " "<< Mul->get_y2() << std::endl;

    Vector2D* Mulv = *a * new Vector2D(5, 5);
    std::cout << "Multiplication matrix a and vector (5,5): " << std::endl;
    std::cout << Mulv->get_x() << " "<< Mulv->get_y() << std::endl;

    Matrix2* Mulm = *a * b;
    std::cout << "Multiplication matrix a and vector (5,5): " << std::endl;
    std::cout << Mulm->get_x1() << " "<< Mulm->get_x2() << std::endl;
    std::cout << Mulm->get_y1() << " "<< Mulm->get_y2() << std::endl;
    return 0;
}

