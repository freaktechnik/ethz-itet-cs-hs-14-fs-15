/**
 * CS Exercise 11.2
 * Title: fractals
 * Author: Martin Giger
 * Date: 22.06.2015
 */

#include "complex.cpp"
#include "bitmap.cpp"

const unsigned int N = 64;
const double BOUNDS = 4;

const double LEFT = -0.95;
const double BOTTOM = 0.25;

const double HEIGHT = 0.01;
const double WIDTH = 0.015;

const int IMAGE_HEIGHT = 1000;
const int IMAGE_WIDTH = 1500;

const double INCREMENT_X = WIDTH / IMAGE_WIDTH;
const double INCREMENT_Y = HEIGHT / IMAGE_HEIGHT;

const Color MANDELBROT_COLOR = Black;

complex next(const complex& last, const complex& c) {
    return last * last + c;
}

unsigned int getIterations(const double x, const double y) {
    unsigned int i;
    complex c = complex(x, y);
    complex z;
    for(i = 0; i < N && z.abs() < BOUNDS; ++i) {
        //cout << i << ":(" << z << ") " << z.abs() << endl;
        z = next(z, c);
    }
    //cout << "(" << z << "): " << i << endl;

    return i;
}

void getMandelbrotSet(
    const double left,
    const double bottom,
    const double incX,
    const double incY,
    unsigned int (&set)[IMAGE_WIDTH][IMAGE_HEIGHT]
) {
    for(int x = 0; x < IMAGE_WIDTH; ++x) {
        for(int y = 0; y < IMAGE_HEIGHT; ++y) {
            set[x][y] = getIterations(left + x * incX, bottom + y * incY);
        }
    }
}

Color getColorForPoint(const unsigned int iterations) {
    if(iterations == N) {
        return MANDELBROT_COLOR;
    }
    else {
        Color top = Red;
        Color bottom = Blue;

        return top + (bottom - top) * ((double)iterations / N);
    }
}

int main(void) {
    Bitmap bitmap (IMAGE_WIDTH, IMAGE_HEIGHT);

    unsigned int set[IMAGE_WIDTH][IMAGE_HEIGHT];
    getMandelbrotSet(LEFT, BOTTOM, INCREMENT_X, INCREMENT_Y, set);

    for(unsigned int x = 0; x < bitmap.GetWidth(); ++x) {
        for(unsigned int y = 0; y < bitmap.GetHeight(); ++y) {
            bitmap(x, bitmap.GetHeight() - y - 1) = getColorForPoint(set[x][y]);
        }
    }

    bitmap.Save("mandelbrot.bmp");
}
