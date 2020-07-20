import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.LinkedList;

public class fran_dunglish {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		reader.readLine();
		String[] words = reader.readLine().split(" ");
		Dict D = new Dict(words);
		int m = Integer.parseInt(reader.readLine());
		for(int i = 0; i < m; i++) {
			String[] data = reader.readLine().split(" ");
			String dutch = data[0];
			String english = data[1];
			if(D.contains(dutch)) {
				if(data[2].charAt(0) == 'c') {
					D.addCorrect(dutch, english);
				} else {
					D.addIncorrect(dutch, english);
				}
			}
		}
		reader.close();
		// count correct
		long correct = countCorrect(words, D);
		long incorrect = countIncorrect(words, D);
		if(correct + incorrect == 1) {
			for(int i = 0; i < words.length; i++) {
				LinkedList<String> correctL = D.getCorrect(words[i]);
				LinkedList<String> incorrectL = D.getIncorrect(words[i]);
				if(incorrectL.size() == 1) {
					System.out.print(incorrectL.getFirst());
				} else {
					System.out.print(correctL.getFirst());	
				}
				if(i < words.length - 1) {
					System.out.print(" ");
				}
			}
			System.out.println();
			System.out.println(correct == 1 ? "correct" : "incorrect");
		} else {
			System.out.println(correct + " correct");
			System.out.println(incorrect + " incorrect");			
		}
	}

	static long countIncorrect(String[] words, Dict D) {
		long total = 0;
		for(int i = 0; i < words.length; i++) {
			long incorrect = D.nbIncorrect(words[i]);
			for(int j = 0; j < words.length; j++) {
				if(i == j) continue;
				if(j < i) {
					incorrect *= D.nbCorrect(words[j]);
				} else {
					incorrect *= D.total(words[j]);
				}
			}
			total += incorrect;
		}
		return total;
	}

	static long countCorrect(String[] words, Dict D) {
		long correct = 1;
		for(String w : words) {
			correct *= D.nbCorrect(w);
		}
		return correct;
	}

	static class Dict {

		private HashMap<String, LinkedList<String>> correct;
		private HashMap<String, LinkedList<String>> incorrect;

		public Dict(String[] words) {
			correct = new HashMap<>();
			incorrect = new HashMap<>();
			for(String word : words) {
				correct.put(word, new LinkedList<>());
				incorrect.put(word, new LinkedList<>());
			}
		}

		public boolean contains(String dutch) {
			return correct.containsKey(dutch);
		}

		public void addCorrect(String dutch, String english) {
			correct.get(dutch).add(english);
		}

		public int nbCorrect(String dutch) {
			return correct.get(dutch).size();
		}

		public LinkedList<String> getCorrect(String dutch) {
			return correct.get(dutch);
		}

		public void addIncorrect(String dutch, String english) {
			incorrect.get(dutch).add(english);
		}

		public int nbIncorrect(String dutch) {
			return incorrect.get(dutch).size();
		}

		public LinkedList<String> getIncorrect(String dutch) {
			return incorrect.get(dutch);
		}

		public int total(String dutch) {
			return nbCorrect(dutch) + nbIncorrect(dutch);
		}

		public String toString() {
			return correct.toString() + "\n" + incorrect.toString();
		}

	}

}
