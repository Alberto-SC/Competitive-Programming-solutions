package com.interview.mdocs;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.junit.Test;

import java.util.Set;

//http://javarevisited.blogspot.in/2014/03/3-ways-to-find-first-non-repeated-character-String-MDocss1-problem.html
//Given a string, find its first non-repeating character in only One scan
public class MDocssTest {
	 @Test
	    public void testFirstNonRepeatedCharacter() {
	        assertEquals('b', MDocss1.firstNonRepeatedCharacter("abcdefghija"));
	        assertEquals('h', MDocss1.firstNonRepeatedCharacter("hello"));
	        assertEquals('J', MDocss1.firstNonRepeatedCharacter("Java"));
	        assertEquals('i', MDocss1.firstNonRepeatedCharacter("simplest"));
	    }

	    @Test
	    public void testFirstNonRepeatingChar() {
	        assertEquals('b', MDocss1.firstNonRepeatingChar("abcdefghija"));
	        assertEquals('h', MDocss1.firstNonRepeatingChar("hello"));
	        assertEquals('J', MDocss1.firstNonRepeatingChar("Java"));
	        assertEquals('i', MDocss1.firstNonRepeatingChar("simplest"));
	    }

	    @Test
	    public void testGetFirstNonRepeatedChar() {
	        assertEquals('b', MDocss1.getFirstNonRepeatedChar("abcdefghija"));
	        assertEquals('h', MDocss1.getFirstNonRepeatedChar("hello"));
	        assertEquals('J', MDocss1.getFirstNonRepeatedChar("Java"));
	        assertEquals('i', MDocss1.getFirstNonRepeatedChar("simplest"));
	    }
}

