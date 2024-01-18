#pragma once

#include <cmath>
//#include "Define.h"

// tagInfo 전방선언!!
struct tagInfo;

struct Vector2D
{
    double x; // x축 성분
    double y; // y축 성분

    // 기본 생성자: (0, 0) 벡터 생성
    Vector2D() : x(0), y(0) {}

    // 매개변수가 있는 생성자
    Vector2D(double x, double y) : x(x), y(y) {}

    // 단위벡터로 정규화하는 메서드
    void normalize() {
        double length = std::sqrt(x * x + y * y);
        if (length > 0) {
            x /= length;
            y /= length;
        }
    }

    // 다른 벡터와의 덧셈
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // 다른 벡터와의 뺄셈
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // 스칼라곱
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // 벡터 + INFO 계산
    Vector2D operator+(const tagInfo& other) const;
};

// 전역 스칼라 * 벡터 곱셈 연산자 오버로딩
Vector2D operator*(double scalar, const Vector2D& vec);