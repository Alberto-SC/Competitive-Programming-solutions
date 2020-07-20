import java.util.Scanner;

//calculates sqrt too imprecise

public class EgorImprecise {

	public static void main(String[] args) throws Exception{
		Scanner in=new Scanner(System.in);
		System.out.println(4*sqrt(in.nextDouble()));
		in.close();
	}

	static double sqrt(double z){
		double low=0.0;
		double high=Math.max(z,1.0);
		while(high-low>high*6e-6){
			double middle=0.5*(high+low);
			if(middle*middle>z)
				high=middle;
			else
				low=middle;
		}
		return (low+high)*.5;
	}
}

