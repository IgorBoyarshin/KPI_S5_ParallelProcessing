-- Data package(implementation)
--
with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Numerics.Discrete_Random;
use Ada.Text_IO, Ada.Integer_Text_IO;

package body Data is


    procedure Input_Vector(V: out Vector) is
    begin
        Put_Line("Input vector start:");

        for i in 1..N loop
            Get(V(i));
        end loop;

        Put_Line("Input vector end");
    end Input_Vector;


    procedure Input_Matrix(M: out Matrix) is
    begin
        Put_Line("Input matrix start:");

        for i in 1..N loop
            for j in 1..N loop
                Get(M(i)(j));
            end loop;
        end loop;

        Put_Line("Input matrix end");
    end Input_Matrix;


    procedure Output_Vector(V: in Vector) is
    begin
        Put_Line("Output vector start:");

        for i in 1..N loop
            Put(V(i));
            Put(" ");
        end loop;

        Put_Line("Output vector end");
    end Output_Vector;


    procedure Output_Matrix(M: in Matrix) is
    begin
        Put_Line("Output matrix start:");

        for i in 1..N loop
            for j in 1..N loop
                Put(M(i)(j));
                Put(" ");
            end loop;
            Put_Line("");
        end loop;

        Put_Line("Output matrix end");
    end Output_Matrix;


    procedure Fill_Vector_Random(V: out Vector)
    is
        package Random_Integer is new Ada.Numerics.Discrete_Random(Integer);
        use Random_Integer;
        G: Generator;
    begin
        Reset(G);
        for i in 1..N loop
            V(i) := (Random(G) mod 200) - 100;
        end loop;
    end Fill_Vector_Random;


    procedure Fill_Matrix_Random(M: out Matrix)
    is
        package Random_Integer is new Ada.Numerics.Discrete_Random(Integer);
        use Random_Integer;
        G: Generator;
    begin
        Reset(G);
        for i in 1..N loop
            for j in 1..N loop
                M(i)(j) := (Random(G) mod 200) - 100;
            end loop;
        end loop;
    end Fill_Matrix_Random;


    procedure Fill_Vector_Ones(V: out Vector)
    is
    begin
        for i in 1..N loop
            V(i) := 1;
        end loop;
    end Fill_Vector_Ones;


    procedure Fill_Matrix_Ones(M: out Matrix)
    is
    begin
        for i in 1..N loop
            for j in 1..N loop
                M(i)(j) := 1;
            end loop;
        end loop;
    end Fill_Matrix_Ones;


    function Add_Vectors(V1, V2: in Vector) return Vector
    is
        V_Result: Vector;
    begin
        for i in 1..N loop
            V_Result(i) := V1(i) + V2(i);
        end loop;

        return V_Result;
    end Add_Vectors;


    function Add_Matrices(M1, M2: in Matrix) return Matrix
    is
        M_Result: Matrix;
    begin
        for row in 1..N loop
            for column in 1..N loop
                M_Result(row)(column) :=
                    M1(row)(column) + M2(row)(column);
            end loop;
        end loop;
        return M_Result;
    end Add_Matrices;


    function Mul_Vector_Matrix(V: in Vector; M: in Matrix) return Vector
    is
        V_Result: Vector;
    begin
        for i in 1..N loop
            V_Result(i) := 0;
            for j in 1..N loop
                V_Result(i) := V_Result(i) + V(j) * M(j)(i);
            end loop;
        end loop;

        return V_Result;
    end Mul_Vector_Matrix;


    function Mul_Matrix_Vector(M: in Matrix; V: in Vector) return Vector
    is
        V_Result: Vector;
    begin
        for i in 1..N loop
            V_Result(i) := 0;
            for j in 1..N loop
                V_Result(i) := V_Result(i) + M(i)(j) * V(j);
            end loop;
        end loop;

        return V_Result;
    end Mul_Matrix_Vector;


    function Mul_Matrices(M1, M2: in Matrix) return Matrix
    is
        M_Result: Matrix;
    begin
        for row in 1..N loop
            for column in 1..N loop
                M_Result(row)(column) := 0;
                for i in 1..N loop
                    M_Result(row)(column) :=
                        M_Result(row)(column) + M1(row)(i) * M2(i)(column);
                end loop;
            end loop;
        end loop;

        return M_Result;
    end Mul_Matrices;


    function Transpose_Matrix(M: in Matrix) return Matrix
    is
        M_Result: Matrix;
    begin
        for row in 1..N loop
            for column in 1..N loop
                M_Result(row)(column) := M(column)(row);
            end loop;
        end loop;

        return M_Result;
    end Transpose_Matrix;


    function Find_Min(V: in Vector) return Integer
    is
        Min: Integer;
    begin
        Min := V(1);
        for i in 2..N loop
            if (V(i) < Min) then
                Min := V(i);
            end if;
        end loop;

        return Min;
    end Find_Min;


    function Find_Max(V: in Vector) return Integer
    is
        Max: Integer;
    begin
        Max := V(1);
        for i in 2..N loop
            if (V(i) > Max) then
                Max := V(i);
            end if;
        end loop;

        return Max;
    end Find_Max;


    function Func1(A, B, C: in Vector; MA, ME: in Matrix) return Integer
    is
    begin
        return (
            Find_Max(
                Add_Vectors(B, C)
            )
            +
            Find_Min(
                Add_Vectors(
                    A,
                    Mul_Vector_Matrix(
                        B,
                        Mul_Matrices(MA, ME)
                    )
                )
            )
        );
    end Func1;


    function Func2(MA, MB, MZ: in Matrix) return Matrix
    is
    begin
        return (
            Add_Matrices(
                Mul_Matrices(
                    MA,
                    Mul_Matrices(MA, MZ)
                ),
                Transpose_Matrix(MB)
            )
        );
    end Func2;


    function Func3(P, S: in Vector; MO, MR, MS: in Matrix) return Vector
    is
    begin
        return (
            Add_Vectors(
                Mul_Matrix_Vector(MO, P),
                Mul_Matrix_Vector(
                    Mul_Matrices(MR, MS),
                    S
                )
            )
        );
    end Func3;

end Data;
