/*=============================================================================
| Assignment: HW 02 - Implementing a Skip List
|
| Author: Franklyn Gonzalez
| Language: Java
|
| To Compile: javac Hw02.java
|
| To Execute: java Hw02 filename seed
| where filename is in the current directory and contains
| commands to insert, delete, print.
| and seed is the RNG seeding.
|
| Class: COP3503 - CS II Spring 2021
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Random;
import java.util.ArrayList;

public class Hw02 {

    public static void main(String[] args) throws IOException {
        ArrayList<String> input = new ArrayList<>(Files.readAllLines(Paths.get(args[0])));
        PrintStream output = new PrintStream(new FileOutputStream("stu-" + args[0].split("-")[1]));
        System.setOut(output);

        SkipList lst;
        boolean seeded = false;
        try {
            lst = new SkipList(Integer.parseInt(args[1]));
            seeded = true;
        }
        catch (IndexOutOfBoundsException e) {
            lst = new SkipList(42);
        }

        complexityIndicator();
        System.out.println("For the input file named " + args[0]);
        System.out.println("With the RNG " + (seeded ? "seeded," : "unseeded,"));
        for (String line : input) {
            String[] split = line.split(" ");
            switch (split[0]) {
                case "i":
                    int value = Integer.parseInt(split[1]);
                    lst.insert(value);
                    break;
                case "d":
                    value = Integer.parseInt(split[1]);
                    try {
                        System.out.println(value + (lst.delete(value).value == value ? " deleted" : ""));
                    }
                    catch (NullPointerException e) {
                        System.out.println(value + " integer not found - delete not successful");
                    }
                    break;
                case "s":
                    value = Integer.parseInt(split[1]);
                    System.out.println(value + (lst.search(value).value == value ? " found" : " Not found"));
                    break;
                case "p":
                    lst.print();
                    break;
                case "q":
                    break;
                default:

            }
        }
    }

    static void complexityIndicator() {
        System.err.println("fr124772@eustis;2.5;6.5hrs");
    }
}

class SkipList {
    class Node {
        // node properties
        Node next, previous, above, below;
        int value;

        public Node(int value) {
            this.value = value;
            this.next = null;
            this.previous = null;
            this.above = null;
            this.below = null;
        }
    }

    // Integer representation of +- Infinity
    final int POSITIVE_INFINITY = Integer.MAX_VALUE;
    final int NEGATIVE_INFINITY = Integer.MIN_VALUE;

    // random to be seeded
    Random random;

    // height of Skip List
    int height;

    // Head and Tail nodes of the Skip List
    Node head;
    Node tail;

    public SkipList(int seed) {
        random = new Random(seed);
        height = 0;

        head = new Node(NEGATIVE_INFINITY);
        tail = new Node(POSITIVE_INFINITY);

        head.next = tail;
        tail.previous = head;
    }

    public Node search(int value) {
        Node node = head;

        while (node.below != null) {
            node = node.below;

            while (value >= node.next.value) {
                node = node.next;
            }
        }
        return node;
    }

    public Node insert(int value) {
        Node node = search(value);
        Node n;

        int level = -1;

        // don't insert duplicate values.
        if (node.value == value) {
            return node;
        }

        do {
            // increase the height of the Skip List if necessary.
            increaseLevel(++level);

            n = node;
            while (node.above == null) {
                node = node.previous;
            }

            node = node.above;
            n = insertAbove(node, n, value);

        } while (Math.abs(random.nextInt()) % 2 != 0);

        return n;
    }

    public Node delete(int value) {
        Node node = search(value);

        // value not found
        if (node.value != value) {
            return null;
        }

        removeReferences(node);

        // remove the reference at each height.
        while (node != null) {
            removeReferences(node);

            if (node.above != null) {
                node = node.above;
            }
            else {
                break;
            }
        }

        return node;
    }

    public void print() {
        StringBuilder sb = new StringBuilder();
        sb.append("the current Skip List is shown below:\n");
        sb.append("---infinity\n");

        Node node = head;
        while (node.below != null) {
            node = node.below;
        }

        node = node.next;
        while (node.next != null) {
            try {
                Node temp = node;
                do {
                    sb.append(String.format("%1$7s", node.value + ";"));
                    temp = temp.above;
                } while (temp.above != null);

                sb.append(String.format("%1$7s", node.value + ";"));
                sb.append('\n');
            }
            catch (NullPointerException e) {
                sb.append('\n');
            }

            node = node.next;
        }

        sb.append("+++infinity\n");
        sb.append("---End of Skip List---");
        System.out.println(sb.toString());
    }

    private void increaseLevel(int level) {
        if (level >= this.height) {
            this.height += 1;
            addLevel();
        }
    }

    private void addLevel() {
        Node head = new Node(NEGATIVE_INFINITY);
        Node tail = new Node(POSITIVE_INFINITY);

        head.next = tail;
        head.below = this.head;

        tail.previous = head;
        tail.below = this.tail;

        this.head.above = head;
        this.tail.above = tail;

        this.head = head;
        this.tail = tail;
    }

    private Node insertAbove(Node node, Node n, int value) {
        Node newNode = new Node(value);
        Node preNode = node.below.below;

        setHorizontal(n, newNode);
        setVertical(node, newNode, preNode, value);

        return newNode;
    }

    private void setHorizontal(Node node, Node newNode) {
        newNode.next = node.next;
        newNode.previous = node;
        node.next.previous = newNode;
        node.next = newNode;
    }

    private void setVertical(Node node, Node newNode, Node preNode, int value) {
        if (preNode != null) {
            while (true) {
                if (preNode.next.value != value) {
                    preNode = preNode.next;
                }
                else {
                    break;
                }
            }

            newNode.below = preNode.next;
            preNode.next.above = newNode;
        }

        if (node != null) {
            if (node.next.value == value) {
                newNode.above = node.next;
            }
        }
    }

    private void removeReferences(Node node) {
        Node next = node.next;
        Node previous = node.previous;

        previous.next = next;
        next.previous = previous;
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