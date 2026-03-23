
// Proteção contra inclusão múltipla
#ifndef POINT_H
#define POINT_H

class P3 {
public:
    double x, y, z;
    P3(double x, double y, double z) : x(x), y(y), z(z) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

};

#endif // POINT_H