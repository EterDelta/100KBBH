#pragma once

#include <cmath>
#include <vector>

class MathUtil {
private:
    static float table[65536];

public:
    static constexpr float PI = 3.14159265358979323846F;

    static float fastSin(float angle);
    static float fastCos(float angle);

    static float lerp(float start, float end, float alpha);

    static std::vector<int> digitize(int number);

    static void init();
};

class Vector2 {
public:
    float x;
    float y;

    Vector2(float x, float y);

    Vector2 operator+(const Vector2& other) const;

    Vector2 operator-(const Vector2& other) const;

    Vector2 operator*(float scalar) const;

    float lengthSqr() const;
    float length() const;

    Vector2 normalized() const;
};

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3& other) const;

    Vector3 operator-(const Vector3& other) const;

    float lengthSqr() const;
    float length() const;

    Vector3 normalized() const;
};

class Matrix4 {
public:
    float elements[16];

    Matrix4();

    void multiply(Matrix4& other);
    void multiplyInv(Matrix4& other);

    void translate(float x, float y, float z);

    void rotate(float pitch, float yaw, float roll);

    void scale(float x, float y, float z);
};

class MatrixStack {
private:
    std::vector<Matrix4> stack;

public:
    MatrixStack();

    void push();

    void pop();

    Matrix4& top();
};