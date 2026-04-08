package com.example;

import java.util.Arrays;

public class Quadrilateral {
    private Point[] vertices;

    public Quadrilateral(Point p1, Point p2, Point p3, Point p4) {
        if (p1 == null || p2 == null || p3 == null || p4 == null) {
            throw new IllegalArgumentException("Points cannot be null");
        }

        this.vertices = new Point[]{p1, p2, p3, p4};

        // Проверка, что четырехугольник не вырожденный
        if (!isValidQuadrilateral()) {
            throw new IllegalArgumentException("Points do not form a valid quadrilateral");
        }
    }

    private boolean isValidQuadrilateral() {
        // Проверка, что все точки различны
        for (int i = 0; i < vertices.length; i++) {
            for (int j = i + 1; j < vertices.length; j++) {
                if (vertices[i].equals(vertices[j])) {
                    return false;
                }
            }
        }

        // Проверка, что точки не лежат на одной прямой (упрощенная проверка)
        // и что стороны не пересекаются (для выпуклого четырехугольника)
        return isConvex();
    }

    private boolean isConvex() {
        // Проверка выпуклости четырехугольника через векторные произведения
        int n = vertices.length;
        int sign = 0;

        for (int i = 0; i < n; i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % n];
            Point p3 = vertices[(i + 2) % n];

            double cross = (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);

            if (Math.abs(cross) < 1e-10) {
                continue; // Три точки на одной прямой
            }

            int currentSign = cross > 0 ? 1 : -1;
            if (sign == 0) {
                sign = currentSign;
            } else if (sign != currentSign) {
                return false; // Изменение знака - невыпуклый
            }
        }
        return true;
    }

    public double perimeter() {
        double perim = 0.0;
        for (int i = 0; i < vertices.length; i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % vertices.length];
            perim += distance(p1, p2);
        }
        return perim;
    }

    public double area() {
        // Используем формулу площади Гаусса (формула шнурков)
        double sum = 0.0;
        for (int i = 0; i < vertices.length; i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1) % vertices.length];
            sum += p1.x * p2.y - p2.x * p1.y;
        }
        return Math.abs(sum) / 2.0;
    }

    public String type() {
        double[] sides = new double[4];
        double[] diagonals = new double[2];

        // Вычисляем стороны
        for (int i = 0; i < 4; i++) {
            sides[i] = distance(vertices[i], vertices[(i + 1) % 4]);
        }

        // Вычисляем диагонали
        diagonals[0] = distance(vertices[0], vertices[2]);
        diagonals[1] = distance(vertices[1], vertices[3]);

        boolean allSidesEqual = Math.abs(sides[0] - sides[1]) < 1e-10 &&
                                 Math.abs(sides[1] - sides[2]) < 1e-10 &&
                                 Math.abs(sides[2] - sides[3]) < 1e-10;

        boolean allAnglesRight = Math.abs(diagonals[0] - diagonals[1]) < 1e-10 &&
                                  Math.abs(sides[0] * sides[0] + sides[1] * sides[1] - diagonals[0] * diagonals[0]) < 1e-10;

        if (allSidesEqual && allAnglesRight) {
            return "Square";
        } else if (allAnglesRight) {
            return "Rectangle";
        } else if (allSidesEqual) {
            return "Rhombus";
        } else {
            return "General";
        }
    }

    public Point[] getVertices() {
        return vertices.clone();
    }

    private double distance(Point p1, Point p2) {
        return Math.sqrt(Math.pow(p2.x - p1.x, 2) + Math.pow(p2.y - p1.y, 2));
    }

    @Override
    public String toString() {
        return String.format("Quadrilateral[type=%s, perimeter=%.2f, area=%.2f]",
                            type(), perimeter(), area());
    }
}