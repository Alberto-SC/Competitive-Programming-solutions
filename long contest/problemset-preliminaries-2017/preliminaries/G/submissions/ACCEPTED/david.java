import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class david{
	public int N, M;
	public ArrayList<Key> key_list;
	public ArrayList<Key> solution;
	
    public void kruskal(){ //O(E log(V))
    	Collections.sort(key_list, david.COMPARE_BY_PROB);
        UFDS UF = new UFDS(N+M);
        //for (int i=0; i<key_list.size(); i++){
        solution = new ArrayList<Key>();
        for(Key front: key_list){
          if (UF.find(front.row)!=UF.find(N+front.column)){
                UF.unionn(front.row,N+front.column);
                solution.add(front);
    }}}

    public class Key{

        public Key(int row, int column, double probability){
        	this.row = row;
        	this.column = column;
        	this.probability = probability;
        }

        public double probability;
        public int row;
        public int column;
        
        
       
    }
    public static final Comparator<Key> COMPARE_BY_PROB = new Comparator<Key>() {
        public int compare(Key one, Key other) {
            if (one.probability > other.probability)
            	return -1;
            else if (one.probability < other.probability)
            	return 1;
            else 
            	return 0;
        }
    };
    
    public static final Comparator<Key> COMPARE_BY_LEX = new Comparator<Key>() {
        public int compare(Key one, Key other) {
            if (one.row < other.row || (one.row == other.row && one.column < other.column))
            	return -1;
            else if (one.row == other.row && one.column == other.column)
            	return 0;
            else 
            	return 1;
        }
    };

    public class UFDS{
        Integer [] p, r;
        UFDS (int N){
            p = new Integer[N];
            r = new Integer[N];
            for(int j=0; j<N; j++){
            	p[j] = j;
            	r[j] = 0;
            }
        }
        int find(int i){
            if (p[i]==i) 
            	return i;
            else 
            	return find(p[i]); 
        }
        void unionn(int i, int j){
            int x=find(i), y=find(j);
            if (x!=y){
                if (r[x]>r[y]) p[y]=x;
                else{
                    p[x]=y;
                    if (r[x]==r[y]) r[y]++;
                }   
            }    
        }
    }
  public void keyboard() throws IOException{
	  BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    String[] words;
	    
	    words = br.readLine().split("\\s");
	    N = Integer.parseInt(words[0]);
	    M = Integer.parseInt(words[1]);
	    Double matrix [][] = new Double[N][];
	    for(int i = 0; i < N; i++){
	        matrix[i] = new Double[M];
	        words = br.readLine().split("\\s");
	        for(int j = 0; j < M; j++){
	            matrix[i][j] = Double.parseDouble(words[j]);
	        }
	    }

	    key_list = new ArrayList<Key>();
	    for(int row = 0; row < N ; row++){
		    words = br.readLine().split("\\s");
		    int aux = Integer.parseInt(words[0]);
		    for(int j = 1; j <= aux; j++){
		    	int col = Integer.parseInt(words[j]);
		    	key_list.add(new Key(row, col , matrix[row][col]));
		    }
	    }
	    kruskal();
	    Collections.sort(solution, david.COMPARE_BY_LEX);
	    for(Key k: solution){
	    	System.out.println(k.row + " " + k.column);
	    }
	  }

   public static void main(String args[]) throws IOException {
	   david d = new david();
	   d.keyboard();
   }

}
