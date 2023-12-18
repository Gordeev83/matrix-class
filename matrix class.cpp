#include <iostream>
#include <random>

using namespace std;

template <typename T>

class Matrix {
private:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fillFromKeyboard() {
        cout << "Ведите элементов матрицы:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    void fillRandomly() {
        random_device rd;
        default_random_engine rng(rd());
        uniform_int_distribution<T> dist;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = dist(rng);
            }
        }
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << ' ';
            }
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Размеры матрицы несовместимы для умножения");
        }

        Matrix result(rows, other.cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    Matrix operator/(const Matrix& other) const {
        if (cols != other.cols || rows != other.rows) {
            throw invalid_argument("Размеры матрицы несовместимы для деления");
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }

        return result;
    }

    T findMaxElement() const {
        T maxElement = data[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] > maxElement) {
                    maxElement = data[i][j];
                }
            }
        }
        return maxElement;
    }
};

int main() 
{
    setlocale(LC_ALL, "");
    Matrix<int> matrix(3, 3);

    matrix.fillFromKeyboard();
    matrix.display();

    cout << "Максимальный элемент: " << matrix.findMaxElement() << endl;

    Matrix<int> otherMatrix(3, 3);
    otherMatrix.fillRandomly();
    otherMatrix.display();

    Matrix<int> result = matrix + otherMatrix;
    result.display();

    return 0;
}