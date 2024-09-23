import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);

        System.out.println("Print matrix size and number of rotations: ");

        int n = in.nextInt();
        int k = in.nextInt();

        int matr[][] = new int[n][n];
        int res[][] = new int[n][n];

        System.out.println("Print your matrix: ");

        int i = 0;
        while(i < n * n){
            int num = in.nextInt();
            if(num < (-1) * n || num > n){
                System.out.println("Incorrect number! Print again!");
            }
            else{
                int column = i % n;
                int row = i / n;
                matr[row][column] = num;
                res[row][column] = num;
                ++i;
            }
        }

        System.out.println("Which rotation do you want?\n1)To the left;\n2)To the right;\n3)Upwards;\n4)Downwards;\n");
        boolean flag = true;
        while(flag){
            int choice = in.nextInt();
            if(choice > 0 && choice < 5){
                switch(choice){
                    case 1:
                        rotateRight(res, matr, k, n);
                        break;
                    case 2:
                        rotateLeft(res, matr, k, n);
                        break;
                    case 3:
                        rotateUp(res, matr, k, n);
                        break;
                    case 4:
                        rotateDown(res, matr, k, n);
                        break;
                }
                flag = false;
            }
            else{
                System.out.println("Incorrect number! Print again!");
            }
        }

        System.out.println("Initial Matrix:\n");
        printMatrix(matr, n);
        System.out.println("Final Matrix:\n");
        printMatrix(res, n);
    }

    public static void rotateRight(int[][] result, final int[][] mat, int rot, int size){
        rot = rot % size;
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                int pos = j + rot;
                if(pos + 1 > size) pos -= size;
                result[i][pos] = mat[i][j];
            }
        }
    }

    public static void rotateLeft(int[][] result, final int[][] mat, int rot, int size){
        rot = rot % size;
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                int pos = j - rot;
                if(pos < 0) pos += size;
                result[i][pos] = mat[i][j];
            }
        }
    }

    public static void rotateUp(int[][] result, final int[][] mat, int rot, int size){
        rot = rot % size;
        for(int j = 0; j < size; ++j){
            for(int i = 0; i < size; ++i){
                int pos = i - rot;
                if(pos < 0) pos += size;
                result[pos][j] = mat[i][j];
            }
        }
    }

    public static void rotateDown(int[][] result, final int[][] mat, int rot, int size){
        rot = rot % size;
        for(int j = 0; j < size; ++j){
            for(int i = 0; i < size; ++i){
                int pos = i + rot;
                if(pos + 1 > size) pos -= size;
                result[pos][j] = mat[pos][j];
            }
        }
    }

    public static void printMatrix(int[][] matrix, int n){
        for(int f = 0; f < n; ++f){
            for(int b = 0; b < n; ++b){
                System.out.print(matrix[f][b]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
    }
}