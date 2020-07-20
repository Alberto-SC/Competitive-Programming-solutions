import java.io.*;
import java.util.*;

public class generate {
    final static int maxn = 20;
    final static int maxappear = 8;
    final static int maxm = 100000;
    
    public static void main(String[] args) throws Exception {

	// Big case where each word has many possible valid translations
	List<String> dutch = new ArrayList<String>();
	List<Translation> dict = new ArrayList<Translation>();
	List<String> answer = new ArrayList<String>();
	long num_correct = 1;
	int idx = 0;
	for(int i = 0; i < maxn; i++) {
	    dutch.add(numToWord(i));
	    num_correct *= maxappear;
	    for(int j = 0; j < maxappear; j++)
		dict.add(new Translation(numToWord(i), numToWord(j), true));
	    for(int j = maxappear; j < maxm / maxn; j++)
		dict.add(new Translation(numToWord(maxn + (++idx / 8)), numToWord(j), true));
	}
	Collections.shuffle(dutch);
	Collections.shuffle(dict);
	answer.add(num_correct + " correct");
	answer.add("0 incorrect");
	WriteCase("secret/11-maxwords", dutch, dict, answer);
	
	// Big case where each word has a single translation
	dutch = new ArrayList<String>();
	dict = new ArrayList<Translation>();
	answer = new ArrayList<String>();
	for(int i = 0; i < maxn; i++)
	    dutch.add(numToWord(i));
	String ans = "";
	for(int i = 0; i < maxm; i++) {
	    dict.add(new Translation(numToWord(i), numToWord(12345 + i), true));
	    if(i < maxn) {
		if(i != 0) ans += " ";
		ans += numToWord(12345 + i);
	    }
	}
	Collections.shuffle(dict);
	answer.add(ans);
	answer.add("correct");
	WriteCase("secret/12-allsingle", dutch, dict, answer);
    }

    public static void WriteCase(String filename, List<String> dutch, List<Translation> dict, List<String> ans) throws IOException {
	try (PrintWriter writer = new PrintWriter(new FileWriter(filename + ".in"))) {
	    writer.println(dutch.size());
	    boolean first = true;
	    for(String d : dutch) {
		if(!first) writer.print(' ');
		else first = false;
		writer.print(d);
	    }
	    writer.println();
	    writer.println(dict.size());
	    for(Translation t : dict)
		writer.println(t);
	}
	try (PrintWriter writer = new PrintWriter(new FileWriter(filename + ".ans"))) {
	    for(String line : ans)
		writer.println(line);
	}
    }

    public static String numToWord(int i) {
	String ret = i >= 26 ? numToWord(i / 26) : "";
	ret += (char)('a' + (i%26));
	return ret;
    }

    static class Translation {
	public String dutch, english;
	public boolean correct;

	public Translation(String d, String e, boolean c) {
	    this.dutch = d;
	    this.english = e;
	    this.correct = c;
	}

	public String toString() {
	    return dutch + " " + english + " " + (correct ? "correct" : "incorrect");
	}
    }
}
