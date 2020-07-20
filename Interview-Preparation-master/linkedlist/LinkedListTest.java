package com.interview.linkedlist;

/**
 *
 * Java program to find if LinkedList contains loop or cycle or not. This
 * example uses two pointer approach to detect cycle in linked list. Fast
 * pointer moves two node at a time while slow pointer moves one node. If linked
 * list contains any cycle or loop then both pointer will meet some time.
 * 
 * @url http://javarevisited.blogspot.in/2013/05/find-if-linked-list-contains-loops-cycle-cyclic-circular-check.html
 */
public class LinkedListTest {

	public static void main(String args[]) {

		// creating LinkedList with 5 elements including head
		LinkedList linkedList = new LinkedList();
		linkedList.appendIntoTail(new LinkedList.Node("101"));
		linkedList.appendIntoTail(new LinkedList.Node("201"));
		linkedList.appendIntoTail(new LinkedList.Node("301"));
		linkedList.appendIntoTail(new LinkedList.Node("401"));

		System.out.println("Linked List : " + linkedList);

		if (linkedList.isCyclic()) {
			System.out.println("Linked List is cyclic as it contains cycles or loop");
		} else {
			System.out.println("LinkedList is not cyclic, no loop or cycle found");
		}

		// 2
		// creating LinkedList with 5 elements including head
		linkedList = new LinkedList();
		linkedList.appendIntoTail(new LinkedList.Node("101"));
		LinkedList.Node cycle = new LinkedList.Node("201");
		linkedList.appendIntoTail(cycle);
		linkedList.appendIntoTail(new LinkedList.Node("301"));
		linkedList.appendIntoTail(new LinkedList.Node("401"));
		linkedList.appendIntoTail(cycle);

		// don't call toString method in case of cyclic linked list, it will
		// throw OutOfMemoryError
		// System.out.println("Linked List : " + linkedList);

		if (linkedList.isCyclic()) {
			System.out.println("Linked List is cyclic as it contains cycles or loop");
		} else {
			System.out.println("LinkedList is not cyclic, no loop or cycle found");
		}

	}

}