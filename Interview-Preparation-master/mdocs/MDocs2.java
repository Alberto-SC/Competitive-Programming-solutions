package com.interview.mdocs;

public class MDocs2 {
	public static void main(String[] args) {
		Final o1 = new Final();
		
		FinalFields o2 = new FinalFields();
		
		
		FinalFields o3 = new FinalFields();
	}
}



final class Final {
	String name="name";
	public void test(){
		System.out.println("Final");
	}
}


class FinalFields {
	final String  name="name";
	final static String  name1="name1";
	
	public final void test(){
		System.out.println("FinalFields");
	}
}

class Child extends FinalFields {
	final String  name="name";
	final static String  name1="name1";
	
	final void test(String str){
		System.out.println("FinalFields");
	}
	
	//Cannot reduce the visibility of the inherited method from FinalFields
	/*void test() {
		System.out.println("FinalFields");
	}*/
	
	//Cannot override the final method from FinalFields
	/*public void test() {
		System.out.println("FinalFields");
	}*/
	
}

//The type Child1 cannot subclass the final class Final
/*class Child1 extends Final {
	
}*/


