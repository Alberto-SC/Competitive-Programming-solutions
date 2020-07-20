import java.util.*;
import static jdk.nashorn.internal.objects.NativeString.toLowerCase;

public class StringTask {


    public static void main(String[] args) {
        String s;
        Scanner entradaEscaner = new Scanner (System.in); //Creación de un objeto Scanner
        s = entradaEscaner.nextLine (); 
        s = toLowerCase(s);
        s = s.replaceAll("[aeiouy]", "");
        String F = "";
        for(int i = 0;i<s.length();i++){
            F = F+"."+s.charAt(i);
        }
        System.out.println(F);
    }
    
}