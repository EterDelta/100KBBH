#include "100KBBH/util/Util.h"

float MathUtil::table[65536];

float MathUtil::fastSin(float angle) {
    return table[(int) (angle * 10430.378F) & 0xFFFF];
}

float MathUtil::fastCos(float angle) {
    return table[(int) (angle * 10430.378F + 16384.0F) & 0xFFFF];
}

float MathUtil::lerp(float start, float end, float alpha) {
    return start + alpha * (end - start);
}

std::vector<int> MathUtil::digitize(int number) {
    std::vector<int> digits;
    do {
        digits.push_back(number % 10);
        number /= 10;
    } while (number != 0);
    return digits;
}

void MathUtil::init() {
    for (int i = 0; i < 65536; ++i) {
        table[i] = std::sin(i * PI * 2.0F / 65536.0F);
    }
}

Vector2::Vector2(float x, float y) : x(x), y(y) {
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);;
}

Vector2 Vector2::normalized() const {
    float mag = length();
    return mag == 0.0F ? Vector2(0, 0) : Vector2(x / mag, y / mag);
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() const {
    float mag = length();
    return mag == 0.0F ? Vector3(0, 0, 0) : Vector3(x / mag, y / mag, z / mag);
}

Matrix4::Matrix4() {
    for (float& element: elements) {
        element = 0.0F;
    }
    elements[0] = 1.0F;
    elements[5] = 1.0F;
    elements[10] = 1.0F;
    elements[15] = 1.0F;
}

void Matrix4::multiply(Matrix4& other, bool backwards) {
    Matrix4 result;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            float sum = 0.0F;
            for (int e = 0; e < 4; e++) {
                sum += backwards ?
                       other.elements[e + x * 4] * elements[y + e * 4] :
                       elements[e + x * 4] * other.elements[y + e * 4];
            }
            result.elements[y + x * 4] = sum;
        }
    }

    for (int i = 0; i < 16; i++) {
        elements[i] = result.elements[i];
    }
}

void Matrix4::translate(float x, float y, float z) {
    Matrix4 translation;
    translation.elements[12] = x;
    translation.elements[13] = y;
    translation.elements[14] = z;

    multiply(translation, false);
}

void Matrix4::rotate(float pitch, float yaw, float roll) {
    float pitchCos = MathUtil::fastCos(pitch);
    float pitchSin = MathUtil::fastSin(pitch);
    float yawCos = MathUtil::fastCos(yaw);
    float yawSin = MathUtil::fastSin(yaw);
    float rollCos = MathUtil::fastCos(roll);
    float rollSin = MathUtil::fastSin(roll);

    Matrix4 rotation;
    rotation.elements[0] = yawCos * rollCos + yawSin * pitchSin * rollSin;
    rotation.elements[1] = -yawCos * rollSin + yawSin * pitchSin * rollCos;
    rotation.elements[2] = yawSin * pitchCos;
    rotation.elements[4] = rollSin * pitchCos;
    rotation.elements[5] = rollCos * pitchCos;
    rotation.elements[6] = -pitchSin;
    rotation.elements[8] = -yawSin * rollCos + yawCos * pitchSin * rollSin;
    rotation.elements[9] = rollSin * yawSin + yawCos * pitchSin * rollCos;
    rotation.elements[10] = yawCos * pitchCos;

    multiply(rotation, true);
}

void Matrix4::scale(float x, float y, float z) {
    Matrix4 scale;
    scale.elements[0] = x;
    scale.elements[5] = y;
    scale.elements[10] = z;

    multiply(scale, true);
}

MatrixStack::MatrixStack() {
    stack.emplace_back();
}

void MatrixStack::push() {
    Matrix4 prevMat = stack.back();
    stack.push_back(prevMat);
}

void MatrixStack::pop() {
    stack.pop_back();
}

Matrix4& MatrixStack::top() {
    return stack.back();
}
