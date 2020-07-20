package com.interview.altimetrik;
/**
 * Java program to find middle element of linked list in one pass.
 * In order to find middle element of linked list we need to find length first
 * but since we can only traverse linked list one time, we will use two pointers
 * one which we will increment on each iteration while other which will be
 * incremented every second iteration. so when first pointer will point to the
 * end of linked list, second will be pointing to the middle element of linked list
 * @url http://javarevisited.blogspot.in/2012/12/how-to-find-middle-element-of-linked-list-one-pass.html
 */
public class LinkedListTest {
  
    public static void main(String args[]) {
        //creating LinkedLst with 5 elements including head
      LinkedLst linkedList = new LinkedLst();
      LinkedLst.Node head = linkedList.head();
      linkedList.add( new LinkedLst.Node("1"));
      linkedList.add( new LinkedLst.Node("2"));
      linkedList.add( new LinkedLst.Node("3"));
      linkedList.add( new LinkedLst.Node("4"));
    
      //finding middle element of LinkedLst in single pass
      LinkedLst.Node current = head;
      int length = 0;
      LinkedLst.Node middle = head;
    
      while(current.next() != null){
          length++;
          if(length%2 ==0){
              middle = middle.next();
          }
          current = current.next();
      }
    
      if(length%2 == 1){
          middle = middle.next();
      }

      System.out.println("length of LinkedLst: " + length);
      System.out.println("middle element of LinkedLst : " + middle);
      
    } 
  
}

class LinkedLst{
    private Node head;
    private Node tail;
  
    public LinkedLst(){
        this.head = new Node("head");
        tail = head;
    }
  
    public Node head(){
        return head;
    }
  
    public void add(Node node){
        tail.next = node;
        tail = node;
    }
  
    public static class Node{
        private Node next;
        private String data;

        public Node(String data){
            this.data = data;
        }
      
        public String data() {
            return data;
        }

        public void setData(String data) {
            this.data = data;
        }

        public Node next() {
            return next;
        }

        public void setNext(Node next) {
            this.next = next;
        }
      
        public String toString(){
            return this.data;
        }
    }
}