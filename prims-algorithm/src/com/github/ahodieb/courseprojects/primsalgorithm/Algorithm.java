package com.github.ahodieb.courseprojects.primsalgorithm;

import java.awt.Point;
import java.util.ArrayList;
import java.util.List;

public class Algorithm {
    public static Matrix Start(Matrix Matrix, boolean Max) {
        com.github.ahodieb.courseprojects.primsalgorithm.Matrix output = new Matrix(Matrix.getMatrix());
        int matrixSize = Matrix.getMatrix().length;

        int iIndex = 0, jIndex = 0;
        List<Point> selectedPoints = new ArrayList<Point>();
        List<Integer> SelectedRows = new ArrayList<Integer>();

        for (int k = 0; k < matrixSize; k++) {
            selectedPoints.add(new Point(iIndex, jIndex));
            SelectedRows.add(jIndex);

            for (int i = 0; i < output.getMatrix().length; i++) {
                if (!selectedPoints.contains(new Point(i, jIndex))) {
                    output.getMatrix()[i][jIndex] = 0;
                }
            }

            int match = 0;
            boolean Checked = false;

            for (Integer i : SelectedRows) {
                for (int j = 0; j < output.getMatrix()[i].length; j++) {
                    int value = output.getMatrix()[i][j];
                    if (value != 0) {
                        if (!Max) {
                            if (!Checked || value < match) {
                                if (!selectedPoints.contains(new Point(i, j))) {
                                    match = value;
                                    iIndex = i;
                                    jIndex = j;
                                    Checked = true;
                                }
                            }
                        } else {
                            if (!Checked || value > match) {
                                if (!selectedPoints.contains(new Point(i, j))) {
                                    match = value;
                                    iIndex = i;
                                    jIndex = j;
                                    Checked = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        return output;
    }
}
