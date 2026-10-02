#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using Matrix = vector<vector<long long>>;

// Set to false to print values separated by a single space with no padding.
const bool ALIGN_COLUMNS = true;

// Print a matrix, optionally with right-aligned columns.
void printMatrix(const Matrix &m)
{
    size_t width = 0;
    if (ALIGN_COLUMNS)
    {
        for (const auto &row : m)
            for (long long v : row)
                width = max(width, to_string(v).size());
    }

    for (const auto &row : m)
    {
        for (size_t j = 0; j < row.size(); j++)
        {
            if (j > 0)
                cout << " ";
            if (ALIGN_COLUMNS)
                cout << setw(static_cast<int>(width));
            cout << row[j];
        }
        cout << "\n";
    }
}

// 1. Load N and two N x N matrices from a file, then print them.
bool loadMatrices(const string &filename, Matrix &A, Matrix &B)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "Error: could not open file '" << filename << "'.\n";
        return false;
    }

    int n;
    if (!(in >> n) || n <= 0)
    {
        cout << "Error: the first line must contain a positive integer N.\n";
        return false;
    }

    A.assign(n, vector<long long>(n));
    B.assign(n, vector<long long>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> A[i][j]))
            {
                cout << "Error: not enough values for Matrix A.\n";
                return false;
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> B[i][j]))
            {
                cout << "Error: not enough values for Matrix B.\n";
                return false;
            }

    cout << "Matrix A:\n";
    printMatrix(A);
    cout << "Matrix B:\n";
    printMatrix(B);
    return true;
}

// 2. Add two matrices and display the result.
void addMatrices(const Matrix &A, const Matrix &B)
{
    size_t n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    cout << "A + B:\n";
    printMatrix(C);
}

// 3. Multiply two matrices and display the result.
void multiplyMatrices(const Matrix &A, const Matrix &B)
{
    size_t n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            for (size_t k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    cout << "A * B:\n";
    printMatrix(C);
}

// 4. Sum the main and secondary diagonals.
void diagonalSums(const Matrix &M, const string &name)
{
    size_t n = M.size();
    long long mainSum = 0, secondarySum = 0;
    for (size_t i = 0; i < n; i++)
    {
        mainSum += M[i][i];
        secondarySum += M[i][n - 1 - i];
    }

    cout << "Diagonal sums for Matrix " << name << ":\n";
    cout << "Main diagonal sum: " << mainSum << "\n";
    cout << "Secondary diagonal sum: " << secondarySum << "\n";
}

// 5. Swap two rows (0-based) and display the result.
void swapRows(Matrix M, int r1, int r2)
{
    int n = static_cast<int>(M.size());
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n)
    {
        cout << "Problem 5 - Invalid row indices.\n";
        return;
    }
    swap(M[r1], M[r2]);
    cout << "Problem 5 - Rows " << r1 << " and " << r2 << " swapped:\n";
    printMatrix(M);
}

// 6. Swap two columns (0-based) and display the result.
void swapColumns(Matrix M, int c1, int c2)
{
    int n = static_cast<int>(M.size());
    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n)
    {
        cout << "Problem 6 - Invalid column indices.\n";
        return;
    }
    for (int i = 0; i < n; i++)
        swap(M[i][c1], M[i][c2]);
    cout << "Problem 6 - Columns " << c1 << " and " << c2 << " swapped:\n";
    printMatrix(M);
}

// 7. Update one element (0-based) and display the result.
void updateElement(Matrix M, int row, int col, long long value)
{
    int n = static_cast<int>(M.size());
    if (row < 0 || row >= n || col < 0 || col >= n)
    {
        cout << "Problem 7 - Invalid row or column index.\n";
        return;
    }
    M[row][col] = value;
    cout << "Problem 7 - Updated matrix:\n";
    printMatrix(M);
}

int main()
{
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    Matrix A, B;
    if (!loadMatrices(filename, A, B))
        return 1;

    addMatrices(A, B);
    multiplyMatrices(A, B);
    diagonalSums(A, "A");

    // Each of the following operates on a copy of the original Matrix A.
    swapRows(A, 0, 2);
    swapColumns(A, 0, 2);
    updateElement(A, 1, 2, 99);

    return 0;
}
