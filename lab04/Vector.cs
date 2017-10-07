// ------------------------------------------------------------------------ //
// -------------------------------Vector----------------------------------- //
// ------------------------------------------------------------------------ //

public class Vector {
    private readonly int SIZE;
    private int[] elements;

    public Vector(int size) {
        this.SIZE = size;
        this.elements = new int[SIZE];
    }

    public Vector(int size, int value) {
        this.SIZE = size;
        this.elements = new int[SIZE];

        for (int i = 0; i < SIZE; i++) {
            this.elements[i] = value;
        }
    }

    public Vector(int size, int[] elements) {
        this.SIZE = size;
        this.elements = elements;
    }

    public int get(int index) {
        return this.elements[index];
    }

    public void set(int index, int value) {
        this.elements[index] = value;
    }
}
