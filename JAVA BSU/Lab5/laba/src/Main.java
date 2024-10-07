public class Main {
    public static void main(String[] args) {
        Vector[] vectors = {
                new Vector(1, 2, 3),
                new Vector(4, 4, 6),
                new Vector(1, 1, 1)
        };

        System.out.println("Vectors:");
        for (Vector vector : vectors) {
            System.out.println(vector);
        }

        // Проверяем компланарность
        boolean coplanar = Vector.areCoplanar(vectors[0], vectors[1], vectors[2]);
        System.out.println("Vectors complanar: " + coplanar);
    }
}