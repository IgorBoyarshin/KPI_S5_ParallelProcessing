-- GNAT 7.1.1 20170630
-- Copyright 1992-2017, Free Software Foundation, Inc.
--
-- Compiling: lab1.adb
-- Source file time stamp: 2017-09-07 20:12:38
-- Compiled at: 2017-09-07 23:27:26

-- Main Program(Lab1)
--
-- Parallel and distributed computing
-- Lab work #1 "Threads in Ada language. Tasks"
--
-- Functions:
-- F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
-- F2: MK = MA * (MA * MZ) + TRANS(MB)
-- F3: T = MO * P + (MR * MS) * S
--
-- Author: Igor Boyarshin, IO-52
-- Date: 02.09.17
--
with Ada.Text_IO, Ada.Integer_Text_IO, System.Multiprocessors, Data;
use Ada.Text_IO, Ada.Integer_Text_IO, System.Multiprocessors;
procedure Lab1
is
    N: constant := 1000;
    Memory: constant := 50000000;
    Output_Threshold: constant := 5;

    package My_Data is new Data(N);
    use My_Data;

    CPU_1: CPU_Range:= 1;
    CPU_2: CPU_Range:= 2;

    -- Tasks specification
    task T1 is
        pragma Task_Name("Task 1");
        pragma Priority(2);
        pragma Storage_Size(Memory);
        -- pragma CPU(CPU_1);
    end T1;

    task T2 is
        pragma Task_Name("Task 2");
        pragma Priority(4);
        pragma Storage_Size(Memory);
        -- pragma CPU(CPU_1);
    end T2;

    task T3 is
        pragma Task_Name("Task 3");
        pragma Priority(8);
        pragma Storage_Size(Memory);
        -- pragma CPU(CPU_1);
    end T3;


    -- Tasks implementation
    -- F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
    task body T1 is
        d: Integer;
        A, B, C: Vector;
        MA, ME: Matrix;
    begin
        Put_Line(":> Starting Task 1...");

        Fill_Vector_Ones(A);
        -- Input_Vector(A);
        Fill_Vector_Ones(B);
        Fill_Vector_Ones(C);
        Fill_Matrix_Ones(MA);
        Fill_Matrix_Ones(ME);

        -- delay 9.0;
        d := Func1(A, B, C, MA, ME);

        if (N < Output_Threshold) then
            Put_Line("");
            Put_Line("Result of Func1: d = Max(B+C)+Min(A+B*(MA*ME)) = ");
            Put_Line(Integer'Image(d));
            Put_Line("");
        end if;

        Put_Line(":> Finished Task 1");
    end T1;


    -- F2: MK = MA * (MA * MZ) + TRANS(MB)
    task body T2 is
        MA, MB, MZ, MK: Matrix;
    begin
        Put_Line(":> Starting Task 2...");

        Fill_Matrix_Ones(MA);
        Fill_Matrix_Ones(MB);
        Fill_Matrix_Ones(MZ);

        --delay 10.3;
        MK := Func2(MA, MB, MZ);

        if (N < Output_Threshold) then
            Put_Line("");
            Put_Line("Result of Func2: MK = MA*(MA*MZ) + Trans(MB) = ");
            Output_Matrix(MK);
            Put_Line("");
        end if;

        Put_Line(":> Finished Task 2");
    end T2;


    -- F3: T = MO * P + (MR * MS) * S
    task body T3 is
        P, S, T: Vector;
        MO, MR, MS: Matrix;
    begin
        Put_Line(":> Starting Task 3...");

        Fill_Vector_Ones(P);
        -- Input_Vector(P);
        Fill_Vector_Ones(S);
        Fill_Matrix_Ones(MO);
        Fill_Matrix_Ones(MR);
        Fill_Matrix_Ones(MS);

        -- delay 3.0;
        T := Func3(P, S, MO, MR, MS);

        if (N < Output_Threshold) then
            Put_Line("");
            Put_Line("Result of Func3: T = MO*P + (MR*MS) * S = ");
            Output_Vector(T);
            Put_Line("");
        end if;

        Put_Line(":> Finished Task 3");
    end T3;


begin
    Put_Line (":> Main program started...");
end Lab1;
