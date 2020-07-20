import java.util.Scanner;

public class fran {
	
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		System.out.println(Math.max(1, reader.nextInt() - 2));
		reader.close();
	}

}
