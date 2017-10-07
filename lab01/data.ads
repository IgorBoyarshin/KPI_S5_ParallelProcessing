-- Data package(specification)
--
generic
    N: Integer;
package Data is

    type Vector is private;
    type Matrix is private;


    procedure Input_Vector (V: out Vector);
    procedure Input_Matrix (M: out Matrix);
    procedure Output_Vector(V: in Vector);
    procedure Output_Matrix(M: in Matrix);


    procedure Fill_Vector_Random(V: out Vector);
    procedure Fill_Matrix_Random(M: out Matrix);


    procedure Fill_Vector_Ones(V: out Vector);
    procedure Fill_Matrix_Ones(M: out Matrix);


    --function Add_Vectors      (V1, V2: in Vector)          return Vector;
    --function Add_Matrices     (M1, M2: in Matrix)          return Matrix;
    --function Mul_Vector_Matrix(V: in Vector; M: in Matrix) return Vector;
    --function Mul_Matrix_Vector(M: in Matrix; V: in Vector) return Vector;
    --function Mul_Matrices     (M1, M2: in Matrix)          return Matrix;
    --function Transpose_Matrix (M: in Matrix)               return Matrix;
    --function Find_Min         (V: in Vector)               return Integer;
    --function Find_Max         (V: in Vector)               return Integer;


    function Func1(A, B, C: in Vector; MA, ME: in Matrix)  return Integer;
    function Func2(MA, MB, MZ: in Matrix)                  return Matrix;
    function Func3(P, S: in Vector; MO, MR, MS: in Matrix) return Vector;


    private
    type Vector is array (1..N) of Integer;
    type Matrix is array (1..N) of Vector;

end Data;
