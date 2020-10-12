package com.company;

public class Search {
    private class Elem {
        protected Elem left;
        protected Elem right;
        protected int value;
        protected int height;
        Elem(int value) {
            this(null, null, value);
        }
        public Elem(Elem left, Elem right, int value) {
            this.left = left;
            this.right = right;
            this.value = value;
            this.height = 1;
        }
    }

    private Elem root;
    public Search (int[] arr) {
        this.root = new Elem(arr[0]);

        for (int i = 1; i < arr.length; i++) {
            this.add(arr[i]);
        }
    }

    public void add(int value) {
        this.root = add(this.root, value);
    }

    private Elem add(Elem p, int value) {
        if (p == null) return new Elem(value);
        if (value < p.value) p.left = add(p.left, value);
        else p.right = add(p.right, value);
        return balance(p);
    }

    private Elem delete(Elem p, int value) {
        if (p == null) return null;
        if (value < p.value) p.left = delete(p.left, value);
        else if (value > p.value) p.right = delete(p.right, value);
        else {
            Elem left = p.left;
            Elem right = p.right;
            if (right == null) return left;
            Elem min = findMin(right);
            min.right = removeMin(right);
            min.left = left;
            return balance(min);
        }
        return balance(p);
    }

    private Elem removeMin(Elem p){
        if (p.left == null) {
            return p.right;
        }
        p.left = removeMin(p.left);
        return balance(p);
    }

    private Elem findMin(Elem p) {
        return p.left != null ?findMin(p.left) :p;
    }

    private Elem balance(Elem p) {
        fixHeight(p);
        if (calcBalanceFactor(p) == 2) {
            if (calcBalanceFactor(p.right) < 0) p.right = rotateRight(p.right);
            return rotateLeft(p);
        }
        if (calcBalanceFactor(p) == -2) {
            if (calcBalanceFactor(p.left) > 0) p.left = rotateLeft(p.left);
            return rotateRight(p);
        }
        return p;
    }

    private Elem rotateRight(Elem p) {
        Elem q = p.left;
        p.left = q.right;
        q.right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    private Elem rotateLeft(Elem q) {
        Elem p = q.right;
        q.right = p.left;
        p.left = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    private int getHeight(Elem element){
        return element != null ?element.height :0;
    }

    private int calcBalanceFactor(Elem element) {
        return getHeight(element.right) - getHeight(element.left);
    }

    private void fixHeight(Elem element) {
        int hl = getHeight(element.left);
        int hr = getHeight(element.right);
        element.height = Math.max(hl, hr) + 1;
    }

    public void printTree() {
        print(this.root);
    }

    private void print(Elem p){
        if (p.left != null) {
            System.out.println(p.value + "--->" + p.left.value);
            print(p.left);
        }
        if (p.right != null) {
            System.out.println(p.value + "--->" + p.right.value);
            print(p.right);
        }
    }
}