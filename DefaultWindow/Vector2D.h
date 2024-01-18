#pragma once

#include <cmath>
//#include "Define.h"

// tagInfo ���漱��!!
struct tagInfo;

struct Vector2D
{
    double x; // x�� ����
    double y; // y�� ����

    // �⺻ ������: (0, 0) ���� ����
    Vector2D() : x(0), y(0) {}

    // �Ű������� �ִ� ������
    Vector2D(double x, double y) : x(x), y(y) {}

    // �������ͷ� ����ȭ�ϴ� �޼���
    void normalize() {
        double length = std::sqrt(x * x + y * y);
        if (length > 0) {
            x /= length;
            y /= length;
        }
    }

    // �ٸ� ���Ϳ��� ����
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // �ٸ� ���Ϳ��� ����
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // ��Į���
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // ���� + INFO ���
    Vector2D operator+(const tagInfo& other) const;
};

// ���� ��Į�� * ���� ���� ������ �����ε�
Vector2D operator*(double scalar, const Vector2D& vec);