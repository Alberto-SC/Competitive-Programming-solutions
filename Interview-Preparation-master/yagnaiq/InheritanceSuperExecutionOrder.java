package com.interview.yagnaiq;

public class InheritanceSuperExecutionOrder {
	 public static void main(String[] args) {
	        new B();
	    }
}

class A {
    public A() {
        System.out.print("A");
    }
}

class B extends A {
    public B() {
        //System.out.print("B");
        super();
    }
}

