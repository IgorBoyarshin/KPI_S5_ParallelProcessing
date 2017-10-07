// ------------------------------------------------------------------------ //
// --------------------------------Data------------------------------------ //
// ------------------------------------------------------------------------ //

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.stream.Stream;

class Data {
    private final int N;
    private BufferedReader br =
        new BufferedReader(new InputStreamReader(System.in));

    public Data(int N) {
        this.N = N;
    }

    public Vector inputVector() {
        System.out.println("Input Vector(space-separated, single line):");
        try {
            String line;
            while ((line = br.readLine()) == null);
            final int[] elements = Stream.of(line.split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();

            return new Vector(N, elements);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public void outputVector(Vector vector) {
        for (int i = 0; i < N; i++) {
            System.out.print(vector.get(i) + " ");
        }
    }

    public Matrix inputMatrix() {
        System.out.println("Input Matrix(space-separated, multiple line):");
        try {
            int[][] matrix = new int[N][N];
            for (int row = 0; row < N; row++) {
                String line;
                while ((line = br.readLine()) == null);
                final int[] elements = Stream.of(line.split(" "))
                    .mapToInt(Integer::parseInt)
                    .toArray();

                matrix[row] = elements;
            }

            return new Matrix(N, matrix);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public void outputMatrix(Matrix matrix) {
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                System.out.print(matrix.get(row, column) + " ");
            }
            System.out.println();
        }
    }

    // ------------------------------------------------------------------ //

    public Vector fillVectorRandom() {
        final Random random = new Random();
        random.setSeed(System.currentTimeMillis());

        int[] values = new int[N];
        for (int i = 0; i < N; i++) {
            values[i] = random.nextInt(200);
        }

        return new Vector(N, values);
    }

    public Matrix fillMatrixRandom() {
        final Random random = new Random();
        random.setSeed(System.currentTimeMillis());

        int[][] values = new int[N][N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                values[row][column] = random.nextInt(200);
            }
        }

        return new Matrix(N, values);
    }
    public Vector fillVectorOnes() {

        return new Vector(N, 1);
    }

    public Matrix fillMatrixOnes() {
        return new Matrix(N, 1);
    }

    // ------------------------------------------------------------------ //

    private Vector addVectors(Vector v1, Vector v2) {
        int[] result = new int[N];
        for (int i = 0; i < N; i++) {
            result[i] = v1.get(i) + v2.get(i);
        }

        return new Vector(N, result);
    }

    private Matrix addMatrices(Matrix m1, Matrix m2) {
        int[][] result = new int[N][N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[row][column] =
                    m1.get(row, column) + m2.get(row, column);
            }
        }

        return new Matrix(N, result);
    }

    private Vector mulVectorMatrix(Vector v, Matrix m) {
        int[] result = new int[N];
        for (int column = 0; column < N; column++) {
            result[column] = 0;
            for (int row = 0; row < N; row++) {
                result[column] += v.get(row) * m.get(row, column);
            }
        }

        return new Vector(N, result);
    }

    private Vector mulMatrixVector(Matrix m, Vector v) {
        int[] result = new int[N];
        for (int row = 0; row < N; row++) {
            result[row] = 0;
            for (int column = 0; column < N; column++) {
                result[row] += m.get(row, column) * v.get(column);
            }
        }

        return new Vector(N, result);
    }

    private Matrix mulMatrices(Matrix m1, Matrix m2) {
        int[][] result = new int[N][N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[row][column] = 0;
                for (int i = 0; i < N; i++) {
                    result[row][column] +=
                        m1.get(row, i) * m2.get(i, column);
                }
            }
        }

        return new Matrix(N, result);
    }

    private Matrix transposeMatrix(Matrix m) {
        int[][] result = new int[N][N];
        for (int row = 0; row < N; row++) {
            for (int column = 0; column < N; column++) {
                result[column][row] = m.get(row, column);
            }
        }

        return new Matrix(N, result);
    }

    private int findMin(Vector v) {
        return findMinOrMax(v, true);
    }

    private int findMax(Vector v) {
        return findMinOrMax(v, false);
    }

    private int findMinOrMax(Vector v, boolean findMinElement) {
        int current = v.get(0);
        for (int i = 1; i < N; i++) {
            final int element = v.get(i);
            if (findMinElement ?
                    (element < current) : (element > current)) {
                current = element;
            }
        }

        return current;
    }

    // ------------------------------------------------------------------ //

    public int func1(Vector A, Vector B, Vector C, Matrix MA, Matrix ME) {
        return (
            findMax(
                addVectors(B, C)
            )
            +
            findMin(
                addVectors(
                    A,
                    mulVectorMatrix(
                        B,
                        mulMatrices(MA, ME)
                    )
                )
            )
        );
    }

    public Matrix func2(Matrix MA, Matrix MB, Matrix MZ) {
        return (
            addMatrices(
                mulMatrices(
                    MA,
                    mulMatrices(MA, MZ)
                ),
                transposeMatrix(MB)
            )
        );
    }

    public Vector func3(Vector P, Vector S, Matrix MO, Matrix MR, Matrix MS) {
        return (
            addVectors(
                mulMatrixVector(MO, P),
                mulMatrixVector(
                    mulMatrices(MR, MS),
                    S
                )
            )
        );
    }
}
