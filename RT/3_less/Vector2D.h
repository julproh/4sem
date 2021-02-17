class Vector2D
{
private:
    double x, y;
public:
    Vector2D();
    Vector2D(double);
    Vector2D(double, double);
    ~Vector2D();
    void set_x(double);
    void set_y(double);
    double get_x();
    double get_y();
    Vector2D* operator*(double);
    double operator*(Vector2D*);
    Vector2D* operator+(Vector2D*);
    Vector2D* operator-(Vector2D*);
    Vector2D* operator/(double a);
};