package com.company;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Введите длину массива: ");
        int length = in.nextInt();
        int[] arr = new int[length];
        for (int i = 0; i < arr.length; i++) {
            System.out.print("Введите "+ (i+1) +" элемент: ");
            arr[i] = in.nextInt();
        }
        Search Tree = new Search(arr);
        Tree.printTree();
    }
}
