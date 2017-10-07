// -------------------------------------------------------------------- //
// -------------------------------Lab2--------------------------------- //
// -------------------------------------------------------------------- //
/*
 *  Main Program(Lab2)
 *
 *  Parallel and distributed Computing
 *  Lab work #2 "Threads in Java"
 *
 * Functions:
 * F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
 * F2: MK = MA * (MA * MZ) + TRANS(MB)
 * F3: T = MO * P + (MR * MS) * S
 *
 * Author: Igor Boyarshin, IO-52
 * Date: 14.09.17
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Lab2 {

    private final int outputThreshold = 7;
    private final Data data;
    // private final int N = 3;

    private final Thread thread1;
    private final Thread thread2;
    private final Thread thread3;


    public Lab2(int N) {
        this.data = new Data(N);

        this.thread1 = new Thread(() -> {
            final Vector A;
            final Vector B;
            final Vector C;
            final Matrix MA;
            final Matrix ME;
            synchronized (this) {
                System.out.println(":> Starting Thread 1...");

                // System.out.println("Input for thread1:");
                A = data.fillVectorOnes();
                B = data.fillVectorOnes();
                C = data.fillVectorOnes();
                MA = data.fillMatrixOnes();
                ME = data.fillMatrixOnes();
            }

            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            final int d = data.func1(A, B, C, MA, ME);

            if (N < outputThreshold) {
                synchronized (this) {
                    System.out.println();
                    System.out.println("Result of Func1: d = Max(B+C)+Min(A+B*(MA*ME)) = ");
                    System.out.println(d);
                    System.out.println();
                }
            }

            System.out.println(":> Finished Thread 1");
        }, "Thread 1");

        this.thread2 = new Thread(() -> {
            final Matrix MA;
            final Matrix MB;
            final Matrix MZ;

            synchronized (this) {
                System.out.println(":> Starting Thread 2...");

                // System.out.println("Input for thread2:");
                MA = data.fillMatrixOnes();
                MB = data.fillMatrixOnes();
                MZ = data.fillMatrixOnes();
            }

            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            final Matrix MK = data.func2(MA, MB, MZ);

            if (N < outputThreshold) {
                synchronized (this) {
                    System.out.println();
                    System.out.println("Result of Func2: MK = MA*(MA*MZ) + Trans(MB) = ");
                    data.outputMatrix(MK);
                    System.out.println();
                }
            }

            System.out.println(":> Finished Thread 2");
        }, "Thread 2");

        this.thread3 = new Thread(() -> {
            final Vector P;
            final Vector S;
            final Matrix MO;
            final Matrix MR;
            final Matrix MS;

            synchronized (this) {
                System.out.println(":> Starting Thread 3...");

                // System.out.println("Input for thread3:");
                P = data.fillVectorOnes();
                S = data.fillVectorOnes();
                MO = data.fillMatrixOnes();
                MR = data.fillMatrixOnes();
                MS = data.fillMatrixOnes();
            }

            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            final Vector T = data.func3(P, S, MO, MR, MS);

            if (N < outputThreshold) {
                synchronized (this) {
                    System.out.println();
                    System.out.println("Result of Func3: T = MO*P + (MR*MS) * S = ");
                    data.outputVector(T);
                    System.out.println();
                }
            }

            System.out.println(":> Finished Thread 3");
        }, "Thread 3");

        thread1.setPriority(2);
        thread2.setPriority(4);
        thread3.setPriority(8);

        thread1.start();
        thread2.start();
        thread3.start();

        try {
            thread1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            thread3.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // -------------------------------------------------------------------- //

    public static void main(String[] args) {
        System.out.println(":> Main program started!");

        System.out.println("Input N(dimensions): ");
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            final int N = Integer.parseInt(br.readLine());
            new Lab2(N);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
