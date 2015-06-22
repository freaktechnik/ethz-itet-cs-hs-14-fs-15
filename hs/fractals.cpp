/**
 * CS Exercise 10.2
 * Title: fractals
 * Author: Martin Giger
 * Date: 22.06.2015
 */

#include "complex.cpp"
#include "bitmap.cpp"

const int N = 64;
const int BOUNDS = 4;

const double LEFT = -0.95;
const double BOTTOM = 0.25;

const double HEIGHT = 0.01;
const double WIDTH = 0.01;

const int IMAGE_HEIGHT = 512;
const int IMAGE_WIDTH = 512;

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

void getMandelbrotSet(unsigned int (&set)[IMAGE_WIDTH][IMAGE_HEIGHT]) {
    for(int x = 0; x < IMAGE_WIDTH; ++x) {
        for(int y = 0; y < IMAGE_HEIGHT; ++y) {
            set[x][y] = getIterations(LEFT + x * INCREMENT_X, BOTTOM + y * INCREMENT_Y);
        }
    }
}

Color getColorForPoint(const int iterations) {
    if(iterations == N) {
        return MANDELBROT_COLOR;
    }
    else {
        Color top = Red;
        Color bottom = Blue;
        
        //cout << top + (bottom - top) * ((double)iterations / N);
        
        return top + (bottom - top) * ((double)iterations / N);
    }
}

int main(void) {
    Bitmap bitmap (IMAGE_WIDTH, IMAGE_HEIGHT);

    unsigned int set[IMAGE_WIDTH][IMAGE_HEIGHT];
    getMandelbrotSet(set);
    
    for(unsigned int x = 0; x < bitmap.GetWidth(); ++x) {
        for(unsigned int y = 0; y < bitmap.GetHeight(); ++y) {
            bitmap(x, bitmap.GetHeight() - y - 1) = getColorForPoint(set[x][y]);
        }
    }
    
    bitmap.Save("mandelbrot.bmp");
}
