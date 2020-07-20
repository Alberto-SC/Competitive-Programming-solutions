package com.interview.hcl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

/*
 * Java Collection How to - Create List to store only unique values
 * @url http://www.java2s.com/Tutorials/Java/Collection_How_to/List/Create_List_to_store_only_unique_values.htm
 */
class UniqueList {
	private HashSet masterSet = new HashSet();
	private ArrayList innerList;
	private Object[] returnable;

	public UniqueList() {
		innerList = new ArrayList();
	}

	public UniqueList(int size) {
		innerList = new ArrayList(size);
	}

	public void add(Object thing) {
		if (!masterSet.contains(thing)) {
			masterSet.add(thing);
			innerList.add(thing);
		}
	}

	public List getList() {
		return innerList;
	}

	public Object get(int index) {
		return innerList.get(index);
	}

	public Object[] toObjectArray() {
		int size = innerList.size();
		returnable = new Object[size];
		for (int i = 0; i < size; i++) {
			returnable[i] = innerList.get(i);
		}
		return returnable;
	}
}

public class UniqueListTest {
	public static void main(String[] args) {
		UniqueList ul = new UniqueList();
		ul.add("Test");
		ul.add("Test");
		ul.add("Not a copy");
		ul.add("Test");
		Object[] content = ul.toObjectArray();
		System.out.println(Arrays.toString(content));
	}
}