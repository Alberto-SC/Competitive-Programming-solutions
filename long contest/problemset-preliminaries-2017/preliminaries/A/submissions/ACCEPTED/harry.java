import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Dictionary;
import java.util.HashMap;
import java.util.Map;

public class harry {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int k = sc.nextInt();
		
		Map<String, ArrayList<Integer>> itemtoplaces = new HashMap<String, ArrayList<Integer>>();
		for(int i = 0; i < k; i++)
		{
			int place = sc.nextInt();
			String s = sc.next();
			
			if(!itemtoplaces.containsKey(s))
			{
				itemtoplaces.put(s, new ArrayList<Integer>());
			}
			itemtoplaces.get(s).add(place);	
		}
		
		
		for (String s : itemtoplaces.keySet()) {
			Collections.sort(itemtoplaces.get(s));
		}
		
		
		int l = sc.nextInt(); 
		String[] items = new String[l];
		int[] lowest = new int[l];
		for(int i = 0; i < l; i++)
		{
			items[i] = sc.next();
			lowest[i] = -1;
		}
		
		int currentplace = 0; // We start at store 0.
		Boolean possible = true, unique = true;
		
		for(int i = 0; i < l && possible; i++) // This loop is quite ugly, which is a consequence of Collections.binarysearch.
		{
			String item = items[i];
			int index = Collections.binarySearch(itemtoplaces.get(item), currentplace); // Find the earliest place still available that has the item.
			
			if(index >= 0) // We can stay at the same place.
				lowest[i] = currentplace;
			else // We move as little as possible.
			{
				index = -index - 1; //Collections.binarysearch is weird.
				if(index == itemtoplaces.get(item).size()) // There is no store left that has the item; all is lost.
					possible = false;
				else // Go to the next place.
				{
					int newplace = itemtoplaces.get(item).get(index);
					currentplace = newplace; 
					lowest[i] = newplace;
				}
			}
		}
		if(possible) // To check whether the path is unique, we repeat the same process from back to front, this time taking the latest possible store. If this gives the same path, it is necessarily unique.
		{
			currentplace = n-1;
			for(int i = l-1; i >= 0 && unique; i--)
			{
				String item = items[i];
				int index = Collections.binarySearch(itemtoplaces.get(item), currentplace);
				int newplace = -1;
				if(index >= 0) // Stay in the same place.
					newplace = currentplace;
				else
				{
					index = - index - 2;
					if(index == -1) // Again, all is lost. This shouldn't happen, as a path is possible.
						System.err.println("ARGH");
					else  newplace = itemtoplaces.get(item).get(index);
						
				}
				if(newplace != lowest[i]) // We found a different path.
					unique = false;
				
				currentplace = newplace;
			}
		}
		
		if(unique && possible)
			System.out.println("unique");
		else if(possible)
			System.out.println("ambiguous");
		else System.out.println("impossible");		
	}
}
