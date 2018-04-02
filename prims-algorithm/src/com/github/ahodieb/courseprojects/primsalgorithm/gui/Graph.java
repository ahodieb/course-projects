package com.github.ahodieb.courseprojects.primsalgorithm.gui;

import java.awt.*;
import javax.swing.*;

public class Graph extends JPanel {
    public Graph() {
        this.setBackground(Color.DARK_GRAY);
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(this.getParent().getWidth(), (int) (this.getParent().getHeight() * (9 / 10.0)));
    }
}
