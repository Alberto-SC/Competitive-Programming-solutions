package com.interview.mdocs;

public class MDocs extends Parent{
	int intVar=11;
	
	static int staticVar=111;
	
	public static void main(String[] args) {
		Parent docs = new MDocs();
		
		System.out.println("intVar--->"+docs.intVar);
		
		System.out.println("intVar--->"+docs.staticVar);
		
		
	}
}


class Parent{
	int intVar=1;
	
	static int staticVar=10;
}