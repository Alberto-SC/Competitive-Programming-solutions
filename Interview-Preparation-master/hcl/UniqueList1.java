package com.interview.hcl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

//Get unique values from arraylist in java
//Create an Arraylist of unique values

public class UniqueList1 {
	public static void main(String[] args) {
		List<String> gasList = new ArrayList<>();// create list with
													// duplicates...
		Set<String> uniqueGas = new HashSet<String>(gasList);
		System.out.println("Unique gas count: " + uniqueGas.size());

		// Using Java 8 Stream.
		// Create the list with duplicates.
		List<String> listAll = Arrays.asList("CO2", "CH4", "SO2", "CO2", "CH4", "SO2", "CO2", "CH4", "SO2");

		// Create a list with the distinct elements using stream.
		List<String> listDistinct = listAll.stream().distinct().collect(Collectors.toList());

		// Display them to terminal using stream::collect with a build in
		// Collector.
		String collectAll = listAll.stream().collect(Collectors.joining(", "));
		System.out.println(collectAll);

		String collectDistinct = listDistinct.stream().collect(Collectors.joining(", "));
		System.out.println(collectDistinct);

	}
}
