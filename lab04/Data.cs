// ------------------------------------------------------------------------ //
// --------------------------------Data------------------------------------ //
// ------------------------------------------------------------------------ //

using System;

class Data {
    private readonly int N;
    private static Random random;

    public Data(int N) {
        this.N = N;
        random = null;
    }

    public Vector InputVector() {
        Console.WriteLine("Input Vector(space-separated, single line):");
        try {
            int[] elements = Array.ConvertAll(
                    Console.ReadLine().Split(' '), int.Parse);

            return new Vector(N, elements);
        } catch (FormatException e) {
            Console.WriteLine(e.Message);
        }

        return null;
    }

    public void OutputVector(Vector vector) {
        for (int i = 0; i < N; i++) {
            Console.Write(vector.get(i) + " ");
        }
    }

    public Matrix InputMatrix() {
        Console.WriteLine("Input Matrix(space-separated, multiple line):");
        try {
            int[,] matrix = new int[N, N];
            for (int row = 0; row < N; row++) {
                int[] elements = Array.ConvertAll(
                        Console.ReadLine().Split(' '), int.Parse);

                for (int column = 0; column < N; column++) {
                    matrix[row, column] = elements[column];
                }
            }

            return new Matrix(N, matrix);
        } catch (FormatException e) {
            Console.WriteLine(e.Message);
        }

        return null;
    }

    public void OutputMatrix(Matrix matrix) {
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                Console.Write(matrix.get(row, column) + " ");
            }
            Console.WriteLine();
        }
    }

    // ------------------------------------------------------------------ //

    public Vector FillVectorRandom() {
        if (random == null) {
            random = new Random();
        }

        int[] values = new int[N];
        for (int i = 0; i < N; i++) {
            values[i] = random.Next(200) - 100;
        }

        return new Vector(N, values);
    }

    public Matrix FillMatrixRandom() {
        if (random == null) {
            random = new Random();
        }

        int[,] values = new int[N, N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                values[row, column] = random.Next(200) - 100;
            }
        }

        return new Matrix(N, values);
    }
    public Vector FillVectorOnes() {

        return new Vector(N, 1);
    }

    public Matrix FillMatrixOnes() {
        return new Matrix(N, 1);
    }

    // ------------------------------------------------------------------ //

    private Vector AddVectors(Vector v1, Vector v2) {
        int[] result = new int[N];
        for (int i = 0; i < N; i++) {
            result[i] = v1.get(i) + v2.get(i);
        }

        return new Vector(N, result);
    }

    private Matrix AddMatrices(Matrix m1, Matrix m2) {
        int[,] result = new int[N, N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[row, column] =
                    m1.get(row, column) + m2.get(row, column);
            }
        }

        return new Matrix(N, result);
    }

    private Vector MulVectorMatrix(Vector v, Matrix m) {
        int[] result = new int[N];
        for (int column = 0; column < N; column++) {
            result[column] = 0;
            for (int row = 0; row < N; row++) {
                result[column] += v.get(row) * m.get(row, column);
            }
        }

        return new Vector(N, result);
    }

    private Vector MulMatrixVector(Matrix m, Vector v) {
        int[] result = new int[N];
        for (int row = 0; row < N; row++) {
            result[row] = 0;
            for (int column = 0; column < N; column++) {
                result[row] += m.get(row, column) * v.get(column);
            }
        }

        return new Vector(N, result);
    }

    private Matrix MulMatrices(Matrix m1, Matrix m2) {
        int[,] result = new int[N, N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[row, column] = 0;
                for (int i = 0; i < N; i++) {
                    result[row, column] +=
                        m1.get(row, i) * m2.get(i, column);
                }
            }
        }

        return new Matrix(N, result);
    }

    private Matrix TransposeMatrix(Matrix m) {
        int[,] result = new int[N, N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[column, row] = m.get(row, column);
            }
        }

        return new Matrix(N, result);
    }

    private int FindMin(Vector v) {
        return FindMinOrMax(v, true);
    }

    private int FindMax(Vector v) {
        return FindMinOrMax(v, false);
    }

    private int FindMinOrMax(Vector v, bool findMinElement) {
        int current = v.get(0);
        for (int i = 1; i < N; i++) {
            int element = v.get(i);
            if (findMinElement ?
                    (element < current) : (element > current)) {
                current = element;
            }
        }

        return current;
    }

    // ------------------------------------------------------------------ //

    public int Func1(Vector A, Vector B, Vector C, Matrix MA, Matrix ME) {
        return (
            FindMax(
                AddVectors(B, C)
            )
            +
            FindMin(
                AddVectors(
                    A,
                    MulVectorMatrix(
                        B,
                        MulMatrices(MA, ME)
                    )
                )
            )
        );
    }

    public Matrix Func2(Matrix MA, Matrix MB, Matrix MZ) {
        return (
            AddMatrices(
                MulMatrices(
                    MA,
                    MulMatrices(MA, MZ)
                ),
                TransposeMatrix(MB)
            )
        );
    }

    public Vector Func3(Vector P, Vector S, Matrix MO, Matrix MR, Matrix MS) {
        return (
            AddVectors(
                MulMatrixVector(MO, P),
                MulMatrixVector(
                    MulMatrices(MR, MS),
                    S
                )
            )
        );
    }
}
