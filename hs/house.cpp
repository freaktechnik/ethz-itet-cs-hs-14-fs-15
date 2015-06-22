/**
 * CS Exercise 13.2
 * Title: house
 * Author: Martin Giger
 * Date: 22.06.2015
 * Based on the provided template
 */

#include <iostream>
#include <vector>
#include <cmath>

class Shape {
public:
    Shape(bool p) : paintable(p) {}

    // PRE:-
    // POST: Returns true if area is paintable.
    bool can_paint() const
    {
        return paintable;
    }

    // PRE: -
    // POST: Returns the area of the shape.
    virtual double get_area() const = 0;

private:
    bool paintable;
};

class Triangle : public Shape {
public:
    Triangle(bool p, double w, double h): Shape(p), width(w), height(h) {}

    double get_area() const {
        return this->width * this->height / 2.0;
    }

private:
    double width;
    double height;
};

class Rectangle : public Shape {
public:
    Rectangle(bool p, double w, double h): Shape(p), width(w), height(h) {}

    double get_area() const {
        return this->width * this->height;
    }

private:
    double width;
    double height;
};

class Circle : public Shape {
public:
    Circle(bool p, double r): Shape(p), radius(r) {}

    double get_area() const {
        return pow(this->radius, 2) * M_PI;
    }

private:
    double radius;
};

int main() {
    Triangle roof         = Triangle(true,   5.4, 2.5);
    Rectangle wall        = Rectangle(true,  5.4, 3.6);
    Rectangle door        = Rectangle(false, 1.2, 2.3);
    Rectangle wall_window = Rectangle(false, 1.2, 1.1);
    Circle roof_window    = Circle(false, 0.45);

    std::vector<Shape*> shapes;
    shapes.push_back(&roof);
    shapes.push_back(&wall);
    shapes.push_back(&door);
    shapes.push_back(&wall_window);
    shapes.push_back(&roof_window);

    double area = 0;
    for(std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
        const Shape* shape = *it;

        if (shape->can_paint()) {
            area += shape->get_area();
        } else {
            area -= shape->get_area();
        }
    }

    std::cout << "Area = " << area << std::endl;
}
