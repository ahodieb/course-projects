package com.github.ahodieb.courseprojects.primsalgorithm.gui;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;

import com.github.ahodieb.courseprojects.primsalgorithm.Algorithm;
import com.github.ahodieb.courseprojects.primsalgorithm.Matrix;
import com.github.ahodieb.courseprojects.primsalgorithm.gui.graph.Edge;
import com.github.ahodieb.courseprojects.primsalgorithm.gui.graph.Node;

public class MainForm extends JFrame implements ActionListener {
    private final Controls cPanel;
    private final JButton addNewNode_btn;
    private final JButton removeNode_btn;
    private final JTextField nodeName_txt;
    private final JButton addNewEdge_btn;
    private final JTextField edgeValue_txt;
    private final JButton generateMatrix_btn;
    private final JButton getResult_btn;
    private final JCheckBox maxSpanning_chk;
    private final JButton drawResult_btn;

    private final Graph gPanel;
    private final List<Node> Nodes;
    private final List<Edge> Edges;

    int dX = 20, dY = 20, dW = 50, dH = 50;


    public Matrix GenerateMatrix() {

        int size = this.Nodes.size();
        int[][] Matrix = new int[size][size];

        for (int i = 0; i < size; i++) {
            Node g = this.Nodes.get(i);

            for (int j = 0; j < size; j++) {
                Node g2 = this.Nodes.get(j);
                int w = 0;
                for (Edge edge : Edges) {

                    if ((edge.getTo().equals(g2) && edge.getFrom().equals(g)) || (edge.getTo().equals(g) && edge
                            .getFrom().equals(g2))) {
                        w = Integer.parseInt(edge.getValue());
                    }

                    Matrix[i][j] = w;
                }
            }
        }
        com.github.ahodieb.courseprojects.primsalgorithm.Matrix result = new Matrix(Matrix);
        System.out.println(result.toString());
        return result;

    }

    public MainForm() {

        super();

        this.setSize(1024, 800);
        this.setTitle("Graph Algorithms");
        this.setLayout(new BorderLayout(5, 5));
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);

        this.gPanel = new Graph();
        this.add(gPanel, BorderLayout.NORTH);
        this.gPanel.setLayout(null);

        this.Nodes = new ArrayList<Node>();
        this.Edges = new ArrayList<Edge>();


        //


        this.cPanel = new Controls();
        this.add(cPanel, BorderLayout.SOUTH);
        this.cPanel.setLayout(new FlowLayout());

        this.addNewNode_btn = new JButton("+");
        this.cPanel.add(this.addNewNode_btn);
        this.addNewNode_btn.addActionListener(this);
        this.addNewNode_btn.setPreferredSize(new Dimension(50, 30));

        this.removeNode_btn = new JButton("-");
        this.cPanel.add(this.removeNode_btn);
        this.removeNode_btn.addActionListener(this);
        this.removeNode_btn.setPreferredSize(new Dimension(50, 30));

        this.nodeName_txt = new JTextField("1");
        this.cPanel.add(this.nodeName_txt);
        this.nodeName_txt.setPreferredSize(new Dimension(50, 30));

        this.addNewEdge_btn = new JButton("+");
        this.cPanel.add(this.addNewEdge_btn);
        this.addNewEdge_btn.addActionListener(this);
        this.addNewEdge_btn.setPreferredSize(new Dimension(50, 30));

        this.edgeValue_txt = new JTextField("1,2,1");
        this.cPanel.add(this.edgeValue_txt);
        this.edgeValue_txt.setPreferredSize(new Dimension(50, 30));

        this.generateMatrix_btn = new JButton("Generate Matrix");
        this.cPanel.add(this.generateMatrix_btn);
        this.generateMatrix_btn.addActionListener(this);
        this.generateMatrix_btn.setPreferredSize(new Dimension(150, 30));

        this.getResult_btn = new JButton("Get Min/Max Spanning Tree");
        this.cPanel.add(this.getResult_btn);
        this.getResult_btn.addActionListener(this);
        this.getResult_btn.setPreferredSize(new Dimension(250, 30));

        this.maxSpanning_chk = new JCheckBox("Maximum Spanning Tree");
        this.cPanel.add(maxSpanning_chk);
        this.maxSpanning_chk.setBackground(Color.orange);
        this.maxSpanning_chk.setPreferredSize(new Dimension(200, 30));

        this.drawResult_btn = new JButton("Draw Spanning Tree");
        this.cPanel.add(this.drawResult_btn);
        this.drawResult_btn.addActionListener(this);
        this.drawResult_btn.setPreferredSize(new Dimension(200, 30));
    }


    @Override
    public void actionPerformed(ActionEvent e) {

        if (e.getSource().equals(addNewNode_btn)) {
            Node g = new Node(this.nodeName_txt.getText());
            this.Nodes.add(g);
            this.gPanel.add(g);
            g.setBounds(dX, dY, dW, dH);
            this.nodeName_txt.setText((Integer.parseInt(nodeName_txt.getText()) + 1) + "");

            this.dX += 50;
            this.dY += 50;

            if (this.dX > this.getWidth() - 100) dX = 0;
            if (this.dY > this.getHeight() - (this.getHeight() * (1 / 10.0) + 100)) dY = 0;

        } else if (e.getSource().equals(removeNode_btn)) {
            if (Node.Selected != null) {

                ArrayList<Edge> edgesToRemove = new ArrayList<Edge>();
                for (Edge edge : Edges) {

                    if (edge.getTo().equals(Node.Selected) || edge.getFrom().equals(Node.Selected)) {
                        edgesToRemove.add(edge);
                    }
                }

                for (Edge edge : edgesToRemove) {

                    Edges.remove(edge);
                    this.gPanel.remove(edge);
                }

                this.Nodes.remove(Node.Selected);
                this.gPanel.remove(Node.Selected);
                Node.Selected = null;

                gPanel.repaint();
            }
        } else if (e.getSource().equals(addNewEdge_btn)) {
            String[] s = this.edgeValue_txt.getText().split(",");

            Node from = null;
            Node to = null;

            for (Node g : this.Nodes) {

                if (g.getValue().equals(s[0])) {
                    from = g;
                } else if (g.getValue().equals(s[1])) {
                    to = g;
                }
            }

            Edge edge = new Edge(s[2], from, to);
            this.Edges.add(edge);
            edge.setSize(1, 1);
            this.gPanel.add(edge);
            this.gPanel.repaint();
            System.out.println(Algorithm.Start(GenerateMatrix(), this.maxSpanning_chk.isSelected()).toString());

        } else if (e.getSource().equals(generateMatrix_btn)) {

            JOptionPane.showMessageDialog(null, GenerateMatrix().toString(), "Generated Matrix",
                    JOptionPane.PLAIN_MESSAGE);
        } else if (e.getSource().equals(getResult_btn)) {
            JOptionPane.showMessageDialog(null,
                    Algorithm.Start(GenerateMatrix(), this.maxSpanning_chk.isSelected()).toString(), "Solved Matrix",
                    JOptionPane.PLAIN_MESSAGE);
        } else if (e.getSource().equals(drawResult_btn)) {
            JFrame f = new JFrame("Spanning Tree");
            f.setSize(this.getWidth(), (int) (this.getHeight() - (this.getHeight() * (1 / 10.0))));
            f.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
            f.getContentPane().setBackground(Color.DARK_GRAY);
            f.setVisible(true);
            f.getContentPane().setLayout(null);

            ArrayList<Node> CloneNodes = new ArrayList<Node>();
            ArrayList<Edge> CloneEdges = new ArrayList<Edge>();

            for (Node g : Nodes) {

                Node gclone = new Node(g.getValue());
                gclone.setBounds(g.getX(), g.getY(), g.getWidth(), g.getHeight());
                f.getContentPane().add(gclone);
                CloneNodes.add(gclone);
            }

            int[][] m = Algorithm.Start(GenerateMatrix(), this.maxSpanning_chk.isSelected()).getMatrix();

            for (int i = 0; i < m.length; i++) {
                for (int j = 0; j < m[i].length; j++) {
                    if (m[i][j] != 0) {
                        CloneEdges.add(new Edge(m[i][j] + "", CloneNodes.get(i), CloneNodes.get(j)));
                    }
                }
            }

            for (Edge edge : CloneEdges) {
                edge.setSize(1, 1);
                f.getContentPane().add(edge);
            }
        }
    }
}
