import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Solution to Subsequences in Substrings
 * 
 * @author vanb
 */
public class subsub_vanb
{
    
    /** The input. */
    private static Scanner sc;
    
    /** The output. */
    private static PrintStream ps;
        
    /**
     * Do it!
     */
    private void doit()
    {
        // Read the two strings, but we like char arrays better than strings.
        char s[] = sc.nextLine().trim().toCharArray();
        char t[] = sc.nextLine().trim().toCharArray();
        
        // starters[j] is the place in s where a subsequence of t leading up to t[j] starts
        long starters[] = new long[t.length];
        Arrays.fill( starters, -1L );
        
        long count = 0L;
        long last = -1L;
        for( int i=0; i<s.length; i++ )
        {
            // If this character s[i] matches some character t[j], adjust starters[j]
            for( int j=t.length-1; j>0; j-- ) if( t[j]==s[i] ) starters[j] = starters[j-1];
            
            // The first character is a special case
            if( t[0]==s[i] ) starters[0] = i;
            
            // If the last character in t matches s[i], then we've got a new subsequence
            if( t[t.length-1]==s[i] && starters[t.length-1]>=0 )
            {
                // This is how many new substrings to add that we haven't added before.
                count += (starters[t.length-1]-last)*(s.length-i);
                
                // Remember where we started here so we don't double-count
                last = starters[t.length-1];
            }
        }
        
        ps.println( count );
    }
        
    /**
     * The main method.
     *
     * @param args the arguments
     * @throws Exception the exception
     */
    public static void main( String[] args ) throws Exception
    {
        sc = new Scanner( System.in );
        ps = System.out;
        
        new subsub_vanb().doit();
    }

}
