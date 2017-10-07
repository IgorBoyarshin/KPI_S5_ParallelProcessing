// -------------------------------------------------------------------- //
// -------------------------------Lab4--------------------------------- //
// -------------------------------------------------------------------- //
/*
 *  Main Program(Lab4)
 *
 *  Parallel and distributed Computing
 *  Lab work #4 "Threads in C#"
 *
 * Functions:
 * F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
 * F2: MK = MA * (MA * MZ) + TRANS(MB)
 * F3: T = MO * P + (MR * MS) * S
 *
 * Author: Igor Boyarshin, IO-52
 * Date: 05.10.17
 */

using System;
using System.Threading;

public class Lab2 {

    private const int outputThreshold = 7;
    private readonly Data data;

    private Thread thread1;
    private Thread thread2;
    private Thread thread3;

    static readonly object locker = new object();

    public Lab2(int N) {
        this.data = new Data(N);

        this.thread1 = new Thread(() => {
            Vector A;
            Vector B;
            Vector C;
            Matrix MA;
            Matrix ME;
            lock (locker) {
                Console.WriteLine(":> Starting Thread 1...");

                // Console.WriteLine("Input for thread1:");
                A = data.FillVectorOnes();
                B = data.FillVectorOnes();
                C = data.FillVectorOnes();
                MA = data.FillMatrixOnes();
                ME = data.FillMatrixOnes();
            }

            Thread.Sleep(3000);

            int d = data.Func1(A, B, C, MA, ME);

            if (N < outputThreshold) {
                lock (locker) {
                    Console.WriteLine();
                    Console.WriteLine("Result of Func1: d = Max(B+C)+Min(A+B*(MA*ME)) = ");
                    Console.WriteLine(d);
                    Console.WriteLine();
                }
            }

            Console.WriteLine(":> Finished Thread 1");
        });

        this.thread2 = new Thread(() => {
            Matrix MA;
            Matrix MB;
            Matrix MZ;

            lock (locker) {
                Console.WriteLine(":> Starting Thread 2...");

                // Console.WriteLine("Input for thread2:");
                MA = data.FillMatrixOnes();
                MB = data.FillMatrixOnes();
                MZ = data.FillMatrixOnes();
            }

            Thread.Sleep(2000);

            Matrix MK = data.Func2(MA, MB, MZ);

            if (N < outputThreshold) {
                lock (locker) {
                    Console.WriteLine();
                    Console.WriteLine("Result of Func2: MK = MA*(MA*MZ) + Trans(MB) = ");
                    data.OutputMatrix(MK);
                    Console.WriteLine();
                }
            }

            Console.WriteLine(":> Finished Thread 2");
        });

        this.thread3 = new Thread(() => {
            Vector P;
            Vector S;
            Matrix MO;
            Matrix MR;
            Matrix MS;

            lock (locker) {
                Console.WriteLine(":> Starting Thread 3...");

                // Console.WriteLine("Input for thread3:");
                P = data.FillVectorOnes();
                S = data.FillVectorOnes();
                MO = data.FillMatrixOnes();
                MR = data.FillMatrixOnes();
                MS = data.FillMatrixOnes();
            }

            Thread.Sleep(5000);

            Vector T = data.Func3(P, S, MO, MR, MS);

            if (N < outputThreshold) {
                lock (locker) {
                    Console.WriteLine();
                    Console.WriteLine("Result of Func3: T = MO*P + (MR*MS) * S = ");
                    data.OutputVector(T);
                    Console.WriteLine();
                }
            }

            Console.WriteLine(":> Finished Thread 3");
        });

        thread1.Name = "Thread 1";
        thread2.Name = "Thread 2";
        thread3.Name = "Thread 3";

        thread1.Priority = ThreadPriority.Lowest;
        thread2.Priority = ThreadPriority.AboveNormal;
        thread3.Priority = ThreadPriority.Normal;

        thread1.Start();
        thread2.Start();
        thread3.Start();

        thread1.Join();
        thread2.Join();
        thread3.Join();
    }

    // -------------------------------------------------------------------- //

    public static void Main(String[] args) {
        Console.WriteLine(":> Main program started!");

        Console.WriteLine("Input N(dimensions): ");
        int N = int.Parse(Console.ReadLine());
        new Lab2(N);
    }
}
