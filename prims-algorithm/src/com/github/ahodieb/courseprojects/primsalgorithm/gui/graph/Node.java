package com.github.ahodieb.courseprojects.primsalgorithm.gui.graph;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.*;

public class Node extends JButton implements MouseMotionListener, MouseListener {

    private String value;
    public static Node Selected;

    public Node(String Value) {
        this.value = Value;
        this.addMouseMotionListener(this);
        this.addMouseListener(this);
    }

    public String getValue() {
        return value;
    }

    @Override
    protected void paintComponent(Graphics g1) {
        // TODO Auto-generated method stub
        int leftStrOffset = (this.value.length() * 3) + 1;
        int topStrOffset = 5;


        Graphics2D g = (Graphics2D) g1;
        g.setColor(Color.orange);
        g.fillOval(0, 0, this.getWidth(), this.getHeight());


        if (Node.Selected != null && Node.Selected.equals(this)) {
            g.setColor(Color.red);
            g.fillOval(0, 0, this.getWidth(), this.getHeight());

        }

        g.setColor(Color.BLUE);
        g.drawString(this.value, (this.getWidth() / 2) - leftStrOffset, (this.getHeight() / 2) + topStrOffset);

    }

    @Override
    protected void paintBorder(Graphics g1) {
        // TODO Auto-generated method stub
        Graphics2D g = (Graphics2D) g1;
        g.setColor(Color.GRAY);
        g.drawOval(0, 0, this.getWidth(), this.getHeight());

    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(50, 50);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        Rectangle objBounds = this.getBounds();

        if ((e.getX() < 0 || e.getY() < 0) ||
                (objBounds.x <= objBounds.x + e.getX() && objBounds.x + e.getX() <= objBounds.x + objBounds.width &&
                        objBounds.y <= objBounds.y + e.getY() && objBounds.y + e
                        .getY() <= objBounds.y + objBounds.height)
                ) {

            this.setLocation(objBounds.x + e.getX() - this.getWidth() / 2,
                    objBounds.y + e.getY() - this.getHeight() / 2);
        } else {

//				this.setLocation(e.getX(), e.getY());
        }

        this.getParent().repaint();
        repaint();


    }

    @Override
    public void mouseMoved(MouseEvent arg0) {
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (Node.Selected == null || !Node.Selected.equals(this)) {
            Node.Selected = this;
            this.repaint();
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    }
}
