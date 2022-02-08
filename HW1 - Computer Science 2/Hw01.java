/*=============================================================================
| Assignment: HW 01 - Building and managing a BST
|
| Author: Franklyn Gonzalez
| Language: Java
|
| To Compile: javac Hw01.java
|
| To Execute: java Hw01 filename
| where filename is in the current directory and contains
| commands to insert, delete, print.
|
| Class: COP3503 - CS II Spring 2021
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.io.PrintStream;

public class Hw01 {

    public static void main(String[] args) throws IOException {
        ArrayList<String> input = new ArrayList<>(Files.readAllLines(Paths.get(args[0])));
        BinarySearchTree tree = new BinarySearchTree();

        PrintStream output = new PrintStream(new FileOutputStream(args[0].split("\\.")[0] + "ST.txt"));
        System.setOut(output);

        System.out.println(args[0] + " contains:");

        boolean print = false;

        for (String line: input) {
            if (line.equals("p")) {
                print = true;
            }
            System.out.println(line);
        }

        for (String line: input) {
            System.setOut(output);
            String t[] = line.split(" ");

            if (t.length != 2 && (!t[0].equals("p") && !t[0].equals("q"))) {
                System.out.println(t[0] + " command:missing integer");
                continue;
            }

            switch (t[0]) {
                case "i":
                    tree.insertValue(Integer.parseInt(t[1]));
                    break;
                case "s":
                    boolean search = tree.searchValue(Integer.parseInt(t[1]));
                    System.out.println(t[1] + ": " + (search? "" : "NOT ") + "found");
                    break;
                case "d":
                    if (!tree.searchValue(Integer.parseInt(t[1])) && print) {
                        System.out.println(t[1] + ": NOT found - NOT deleted");
                    }
                    else {
                        tree.deleteValue(Integer.parseInt(t[1]));
                    }

                    break;
                case "p":
                    tree.print();
                    break;
                case "q":
                    System.out.println("left children:\t" + tree.countChildren(tree.root.left));
                    System.out.println("left depth:\t" + tree.getDepth(tree.root.left));
                    System.out.println("right children:\t" + tree.countChildren(tree.root.right));
                    System.out.println("right depth:\t" + tree.getDepth(tree.root.right));
                    tree.complexityIndicator();
                    return;
                default:
            }
        }
    }
}

class BinarySearchTree {
    class Node {
        Node left;
        Node right;
        int value;

        public Node(int value) {
            this.value = value;
            left = null;
            right = null;
        }
    }

    Node root;

    public BinarySearchTree() {
        root = null;
    }

    public void insertValue(int value) {
        root = insert(root, value);
    }

    Node insert(Node node, int value) {
        if (node == null) {
            node = new Node(value);
            return node;
        }

        if (value >= node.value) {
            node.right = insert(node.right, value);
        }
        else {
            node.left = insert(node.left, value);
        }
        return node;
    }

    public boolean searchValue(int value) {
        return search(root, value) != null;
    }

    Node search(Node node, int value) {
        if (node == null || node.value == value) {
            return node;
        }

        return search(value < node.value ? node.left : node.right, value);
    }

    public void deleteValue(int value) {
        root = delete(root, value);
    }

    Node delete(Node node, int value) {
        if (node == null) {
            return null;
        }

        if (value < node.value) {
            node.left = delete(node.left, value);
        }
        else if (value > node.value) {
            node.right = delete(node.right, value);
        }
        else {
            if (node.left == null) {
                return node.right;
            }
            else if (node.right == null) {
                return node.left;
            }

            node.value = min(node.right);
            node.right = delete(node.right, node.value);
        }
        return node;
    }

    int min(Node node) {
        int min = node.value;
        while (node.left != null) {
            min = node.left.value;
            node = node.left;
        }
        return min;
    }

    static int countChildren(Node node) {
        return node == null ? 0 : 1 + countChildren(node.left) + countChildren(node.right);
    }

    static int getDepth(Node node) {
        return node == null ? 0 : Math.max(getDepth(node.left), getDepth(node.right)) + 1;
    }

    public void print() {
        printNode(root);
        System.out.println();
    }

    void printNode(Node node) {
        if (node == null) {
            return;
        }

        printNode(node.left);
        System.out.print(node.value + " ");
        printNode(node.right);
    }

    static void complexityIndicator() {
        System.err.println("fr124772@eustis;1.5;4hrs");
    }
}

/*=============================================================================
| I Franklyn Gonzalez (fr124772) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/