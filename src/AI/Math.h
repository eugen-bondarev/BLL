#ifndef __AI_Math_h__
#define __AI_Math_h__

#pragma once

#include "Common.h"

#define AI_MATRIX_OPERATION_CONDITION(cond, msg)\
    if (!(cond))\
    {\
        throw std::runtime_error(msg);\
    }(void(0))

namespace AI
{
    class Matrix
    {
    public:
        using InitList = std::initializer_list<Num>;
        using InitList2D = std::initializer_list<InitList>;

        Matrix() = default;
        Matrix(const InitList2D& data);
        Matrix(const size_t rows, const size_t cols);
        Matrix(const size_t rows, const size_t cols, const Vec<Num>& data);
        Matrix(const size_t rows, const size_t cols, const Function& generator);

        Matrix& Transpose();
        Matrix& Nullify();

        size_t GetRows() const;
        size_t GetCols() const;
        bool IsTransposed() const;

        static size_t SubscriptToIndex(const size_t row, const size_t col, const size_t rows, const size_t cols, const bool transposed);
        Num& operator()(const size_t row, const size_t col);
        Num  operator()(const size_t row, const size_t col) const;

        Matrix Apply(const Function& function) const;

        Matrix EntrywiseProduct(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Num scalar) const;

        Matrix& operator*=(const Matrix& other);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);

        Str ToString() const;

    private:
        size_t rows {0};
        size_t cols {0};
        bool transposed {false};
        Vec<Num> data;
    };
}

#endif