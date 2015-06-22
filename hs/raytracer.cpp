/**
 * CS Exercise 12
 * Title: ray tracer
 * Author: Martin Giger
 * Date: 22.06.2015
 * Vastly based off the provided structures in teh exercise (for obvious reasons)
 */

#include <cmath>

#include "bitmap.cpp"

const double DELTA = 0.0000001;
const double RAY_OFFSET = 0.0001;

double min(double a, double b) {
    if(a > b && b >= 0) {
        return b;
    }
    else if(a >= 0) {
        return a;
    }
    else {
        return 0;
    }
}

struct Vector {
    double x;
    double y;
    double z;
    // POST: vector should be initialized as null-vector
    Vector(): x(0), y(0), z(0) {};
    // POST: coordinates (x,y,z) set to (x_,y_,z_)
    Vector(double x_, double y_, double z_): x(x_), y(y_), z(z_) {};

    Vector& operator-=(const Vector& w) {
        this->x -= w.x;
        this->y -= w.y;
        this->z -= w.z;
        return *this;
    }

    Vector& operator+=(const Vector& w) {
        this->x += w.x;
        this->y += w.y;
        this->z += w.z;
        return *this;
    }

    Vector& operator*=(const double r) {
        this->x *= r;
        this->y *= r;
        this->z *= r;
        return *this;
    }
};

Vector operator-(const Vector& v) {
    Vector r(-v.x,-v.y,-v.z);
    return r;
}

Vector operator-(const Vector& v, const Vector& w) {
    Vector r(v.x - w.x, v.y - w.y, v.z - w.z);
    return r;
}

Vector operator+(const Vector& v, const Vector& w) {
    Vector r(v.x + w.x, v.y + w.y, v.z + w.z);
    return r;
}

double operator*(const Vector& v, const Vector& w) {
    return v.x * w.x + v.y * w.y + v.z * w.z;
}

Vector operator*(const Vector& v, const double r) {
    Vector a(v.x * r, v.y * r, v.z * r);
    return a;
}

Vector operator*(const double r, const Vector& v) {
    return v * r;
}

Vector operator/(const Vector& v, const double r) {
    Vector a(v.x / r, v.y / r, v.z / r);
    return a;
}

Vector operator/(const double r, const Vector& v) {
    return v / r;
}

//POST: returns the Euclidean norm ||v|| of the vector v
double norm(const Vector& v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

//PRE: non-zero vector v
//POST: returns the normalized vector, ||v||=1
Vector normalize(const Vector& v) {
    return v / norm(v);
}

struct Ray {
    Vector start;
    Vector direction; // INV: normalized
    // constructor
    // PRE: non-zero vector d
    // POST: ray with offset s and normalized direction vector d
    Ray(Vector s, Vector d): start(s), direction(normalize(d)) {};
};

struct Shape {
    int type;
    Vector v;
    double d;
    // INV: either 0 (sphere) or 1 (plane)
    // sphere: center, plane: plane normal
    // sphere: radius, plane: distance from origin
    Color ambientColor; // ambient color ("Eigenleuchten")
    Color diffuseColor; // diffuse color ("Diffuse Lichtreflektion")
    Color reflectionColor; // reflection color ("Spiegelung")
    // POST: shape is initialized with type = Type, v = V
    // d = D, ambientColor = aC, diffuseColor=dC and reflectionColor = rC
    Shape(int Type, Vector V, double D, Color aC, Color dC, Color rC)
    : type(Type),
      v(V),
      d(D),
      ambientColor(aC),
      diffuseColor(dC),
      reflectionColor(rC)
    {};
    // POST: if there is an intersection between ray and
    // this shape, return true and return intersection
    // point as the parameter t in ray.start + ray.direction * t.
    // return false otherwise
    bool intersect(const Ray& ray, double& t) const {
        if(this->type == 0) {
            Vector n = ray.start - this->v;
            double d = pow(n * ray.direction, 2) - n * n + pow(this->d, 2);
            if(d >= 0) {
                double a = -n * ray.direction;
                double b = sqrt(d);

                double t1 = a + b;
                double t2 = a - b;

                t = min(t1, t2);

                return t1 >= 0 || t2 >= 0;
            }
            else {
                return false;
            }
        }
        else {
            double angle = ray.direction * this->v;
            if(angle > DELTA || angle < -DELTA) {
                t = (this->d - ray.start * this->v) / angle;
                return t >= 0;
            }
            else {
                return false;
            }
        }
    }
    // PRE: vector "at" lies on the surface of this object
    // POST: return a normal vector of the shape at position "at"
    Vector get_normal(const Vector& at) const {
        if(type == 0) {
            return normalize(at - this->v);
        }
        else {
            // We already have the normal of a plane, and it's the same everywhere \o/
            return normalize(v);
        }
    }
};

struct Scene {
    Vector cameraVector;
    // camera position
    Vector lightVector;
    // light position
    Color lightColor;
    // light color
    unsigned int plane_width; // observation window width
    unsigned int plane_height; // observation window height
    std::vector<Shape> shapes; // vector of shapes
    // POST: scene is initialized with cameraVector = cV, lightVector lV,
    // lightColor lC, plane_width w, plane_height h and
    // and empty vector shapes
    Scene(Vector cV, Vector lV, Color lC, int w, int h)
    : cameraVector(cV),
      lightVector(lV),
      lightColor(lC),
      plane_width(w),
      plane_height(h),
      shapes()
    {};
    // POST: shape is added to the list of shapes
    void add_shape(const Shape& shape) {
        this->shapes.push_back(shape);
    }
    // POST: Return pointer to shape that has closest intersection with ray, if any
    // return null otherwise
    // t contains the parameter of the ray for the intersection point, if any
    const Shape* intersect(const Ray& ray, double& t) const {
        const Shape* min = 0;
        const Shape* s;
        double i;
        t = HUGE_VAL;
        for(std::vector<Shape>::const_iterator it = this->shapes.begin(); it != this->shapes.end(); ++it) {
            s = &(*it);
            bool inter = s->intersect(ray, i);
            if(inter && i < t) {
                t = i;
                min = s;
            }
        }

        if(min == 0) {
            t = 0;
        }

        return min;
    }

    // POST: return a ray from camera origin through x,y on the pixel grid
    Ray create_ray(int x, int y) const {
        Vector pixel(
            ( 2.0 * x + 1 - this->plane_width ) / (2 * this->plane_width),
            (-2.0 * y - 1 + this->plane_height) / (2 * this->plane_height),
            0
        );
        return Ray(pixel, (pixel - this->cameraVector));
    }

    // POST: return color returned by ray
    Color trace_ray(const Ray& ray, const int depth) const {
        Color c = Black;
        const Shape* S = 0;
        double t;

        S = this->intersect(ray, t);

        if(S) {
            Vector intersection = ray.start + ray.direction * t;

            // i) ambient light
            c += S->ambientColor;

            // ii) diffuse light and shadow
            Vector shadowDirection = this->lightVector - intersection;
            Ray shadow(intersection + RAY_OFFSET * shadowDirection, shadowDirection);

            const Shape* T = 0;
            double u;

            T = intersect(shadow, u);

            
            Vector normal = S->get_normal(intersection);
            Vector reflectionDirection = ray.direction - 2 * (normal * ray.direction) * normal;
            Ray reflection(intersection + RAY_OFFSET * reflectionDirection, reflectionDirection);

            if(T == 0 || u > norm(shadowDirection)) {
                c += this->lightColor * S->diffuseColor * (shadow.direction * normal);

            // iii) specular highlighting
                if(reflection.direction * shadow.direction > 0) {
                    c += this->lightColor * S->reflectionColor * pow(reflection.direction * shadow.direction, 16);
                }
            }

            // iv) reflection recursion
            if(depth > 0) {
                Color reflected = trace_ray(reflection, depth - 1);
                c += reflected * S->reflectionColor;
            }
        }

        return c;
    }
    // POST: run raytracer on bitmap
    void raytrace(Bitmap& bitmap, const int depth) const {
        for(unsigned int x = 0; x < bitmap.GetWidth(); ++x) {
            for(unsigned int y = 0; y < bitmap.GetHeight(); ++y) {
                bitmap(x, y) = trace_ray(create_ray(x, y), depth);
            }
        }
    }
};

