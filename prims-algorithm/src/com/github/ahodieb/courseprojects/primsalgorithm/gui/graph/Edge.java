package com.github.ahodieb.courseprojects.primsalgorithm.gui.graph;

import java.awt.*;
import javax.swing.*;

public class Edge extends JButton {
    private String value;
    private Node from;
    private Node to;

    public Edge(String Value, Node From, Node To) {
        this.value = Value;
        this.from = From;
        this.to = To;
    }

    public Node getTo() {
        return to;
    }

    public Node getFrom() {
        return from;
    }

    public String getValue() {
        return value;
    }

    @Override
    protected void paintComponent(Graphics g1) {


        Graphics2D g = (Graphics2D) g1;
        g.setColor(Color.CYAN);

        if (this.to.getX() > this.from.getX() && this.to.getY() > this.from.getY()) {
            this.setBounds(this.from.getX() + this.from.getWidth() / 2, this.from.getY() + this.from.getHeight() / 2,
                    this.to.getX() - this.from.getX(), this.to.getY() - this.from.getY());
            g.drawLine(0, 0, this.getWidth(), this.getHeight());
            //g.drawLine(0, this.getHeight(), this.getWidth(), 0);
        } else if (this.to.getX() > this.from.getX() && this.from.getY() > this.to.getY()) {
            this.setBounds(this.from.getX() + this.from.getWidth() / 2, this.to.getY() + this.to.getHeight() / 2,
                    this.to.getX() - this.from.getX(), this.from.getY() - this.to.getY());
            //g.drawLine(0, 0, this.getWidth(), this.getHeight());
            g.drawLine(0, this.getHeight(), this.getWidth(), 0);
        }


        if (this.from.getX() > this.to.getX() && this.from.getY() > this.to.getY()) {
            this.setBounds(this.to.getX() + this.to.getWidth() / 2, this.to.getY() + this.to.getHeight() / 2,
                    this.from.getX() - this.to.getX(), this.from.getY() - this.to.getY());
            g.drawLine(0, 0, this.getWidth(), this.getHeight());
            //g.drawLine(0, this.getHeight(), this.getWidth(), 0);
        } else if (this.from.getX() > this.to.getX() && this.to.getY() > this.from.getY()) {
            this.setBounds(this.to.getX() + this.to.getWidth() / 2, this.from.getY() + this.from.getHeight() / 2,
                    this.from.getX() - this.to.getX(), this.to.getY() - this.from.getY());
            //g.drawLine(0, 0, this.getWidth(), this.getHeight());
            g.drawLine(0, this.getHeight(), this.getWidth(), 0);
        }

        g.setColor(Color.yellow);
        g.drawString(this.value, (this.getWidth() / 2), (this.getHeight() / 2));


    }

    @Override
    protected void paintBorder(Graphics g1) {
    }


    @Override
    public Dimension getPreferredSize() {
        // TODO Auto-generated method stub
        return new Dimension(50, 50);
    }
}
