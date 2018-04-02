package com.github.ahodieb.courseprojects.primsalgorithm.gui;

import java.awt.*;
import javax.swing.*;

public class Controls extends JPanel {
    public Controls() {
        this.setBackground(Color.orange);
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(this.getParent().getWidth(), (int) (this.getParent().getHeight() * (1 / 10.0)));
    }
}
