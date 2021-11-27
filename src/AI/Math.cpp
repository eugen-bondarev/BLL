#include "Math.h"

#include <sstream>

namespace AI
{
    Matrix::Matrix(const size_t rows, const size_t cols, const Vec<Num>& data) : rows {rows}, cols {cols}, data {data}
    {
    }

    Matrix::Matrix(const InitList2D& data)
    {
        Vec<Num> dataCopy;
        dataCopy.reserve(data.size() * 1);

        for (auto& row : data)
        {
            for (auto& value : row)
            {
                dataCopy.push_back(value);
            }
        }

        rows = data.size(); 
        cols = dataCopy.size() / data.size();
        this->data = dataCopy;
    }

    Matrix::Matrix(const size_t rows, const size_t cols) : rows {rows}, cols {cols}
    {
        data.resize(rows * cols, 0.0f);
    }

    Matrix::Matrix(const size_t rows, const size_t cols, const Function& generator) : rows {rows}, cols {cols}
    {
        data.reserve(rows * cols);

        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                data.push_back(generator(0.0f));
            }
        }
    }

    Matrix& Matrix::Transpose()
    {
        transposed = !transposed;
        return (*this);
    }

    size_t Matrix::GetRows() const
    {
        return !transposed ? rows : cols;
    }

    size_t Matrix::GetCols() const
    {
        return !transposed ? cols : rows;
    }

    bool Matrix::IsTransposed() const
    {
        return transposed;
    }

    size_t Matrix::SubscriptToIndex(const size_t row, const size_t col, const size_t rows, const size_t cols, const bool transposed)
    {
        const size_t i {!transposed ? (row * cols + col) : (col * rows + row)};
        return i;
    }

    Num& Matrix::operator()(const size_t row, const size_t col)
    {
        const size_t i {SubscriptToIndex(row, col, GetRows(), GetCols(), transposed)};
        return data[i];

    }

    Num Matrix::operator()(const size_t row, const size_t col) const
    {
        const size_t i {SubscriptToIndex(row, col, GetRows(), GetCols(), transposed)};
        return data[i];
    }

    Matrix Matrix::Apply(const Function& function) const
    {
        Matrix result {Matrix(GetRows(), GetCols())};

        for (size_t i = 0; i < result.GetRows(); ++i)
        {
            for (size_t j = 0; j < result.GetCols(); ++j)
            {
                result(i, j) = function((*this)(i, j));
            }
        }

        return result;
    }

    Matrix Matrix::operator*(const Matrix& other) const
    {
        AI_MATRIX_OPERATION_CONDITION(
            (*this).GetCols() == other.GetRows(), 
            StringFormat("[operator *] the dimensions of given matrices mismatch. m0.cols != m1.rows (%i != %i).", static_cast<int>((*this).GetCols()), static_cast<int>(other.GetRows()))
        );

        Matrix result = Matrix(GetRows(), other.GetCols());

        for (size_t i = 0; i < result.GetRows(); ++i)
        {
            for (size_t j = 0; j < result.GetCols(); ++j)
            {
                result(i, j) = 0.0f;

                for (size_t k = 0; k < GetCols(); ++k)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }

        return result;
    }

    Matrix Matrix::operator+(const Matrix& other) const
    {
        AI_MATRIX_OPERATION_CONDITION(
            (*this).GetCols() == other.GetCols() && (*this).GetRows() == other.GetRows(), 
            StringFormat("[operator +] the dimensions of given matrices mismatch. [m0.rows, m0.cols] != [m1.rows, m1.cols] ([%i, %i] != [%i, %i]).", 
                static_cast<int>((*this).GetRows()), static_cast<int>((*this).GetCols()), 
                static_cast<int>(other.GetRows()), static_cast<int>(other.GetCols())
            )
        );

        Matrix result {Matrix(GetRows(), GetCols())};

        for (size_t i = 0; i < result.GetRows(); ++i)
        {
            for (size_t j = 0; j < result.GetCols(); ++j)
            {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }

        return result;
    }

    Matrix Matrix::operator-(const Matrix& other) const
    {
        AI_MATRIX_OPERATION_CONDITION(
            (*this).GetCols() == other.GetCols() && (*this).GetRows() == other.GetRows(), 
            StringFormat("[operator +] the dimensions of given matrices mismatch. [m0.rows, m0.cols] != [m1.rows, m1.cols] ([%i, %i] != [%i, %i]).", 
                static_cast<int>((*this).GetRows()), static_cast<int>((*this).GetCols()), 
                static_cast<int>(other.GetRows()), static_cast<int>(other.GetCols())
            )
        );

        Matrix result {Matrix(GetRows(), GetCols())};

        for (size_t i = 0; i < result.GetRows(); ++i)
        {
            for (size_t j = 0; j < result.GetCols(); ++j)
            {
                result(i, j) = (*this)(i, j) - other(i, j);
            }
        }

        return result;
    }

    Matrix& Matrix::operator*=(const Matrix& other)
    {
        Matrix result {(*this) * other};
        (*this) = result;
        return (*this);
    }

    Matrix& Matrix::operator+=(const Matrix& other)
    {
        Matrix result {(*this) + other};
        (*this) = result;
        return (*this);
    }

    Matrix& Matrix::operator-=(const Matrix& other)
    {
        Matrix result {(*this) - other};
        (*this) = result;
        return (*this);
    }

    Str Matrix::ToString() const
    {
        std::stringstream stream;

        for (size_t i = 0; i < GetRows(); ++i)
        {
            if (i != 0) stream << '\n';
            for (size_t j = 0; j < GetCols(); ++j)
            {
                stream << operator()(i, j) << ' ';
            }
        }

        return stream.str();
    }
}