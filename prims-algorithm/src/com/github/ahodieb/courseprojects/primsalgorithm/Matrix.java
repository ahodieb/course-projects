package com.github.ahodieb.courseprojects.primsalgorithm;

public class Matrix {

    private final int[][] matrix;

    public Matrix(int[][] matrix) {
        this.matrix = matrix;
    }

    public int[][] getMatrix() {
        return matrix;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int[] m : matrix) {
            for (int n : m) {
                if (n == 0) {
                    sb.append("- ");
                } else {
                    sb.append(n).append(" ");
                }
            }
            sb.append("\n");
        }
        return sb.toString();
    }
}
