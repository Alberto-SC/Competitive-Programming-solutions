/**
 * BFS with minimum capacity
 */

import java.util.*;
import java.io.*;

/**
 * @author mathijs
 * p009 Paris
 * O( m * maxc )
 */
public class SolutionLin {
	TreeMap<Integer,Node> nodes;
	static int maxid = 0;
	
	public static void main(String[] args) {
		try{
	          InputStream input = System.in;
	          Scanner sc = new Scanner(input);
        	  int m = sc.nextInt();
        	  int n = sc.nextInt();
        	  SolutionLin sol = new SolutionLin();
        	  for( int i = 0; i < n; ++i )
        	  {
        		  int from = sc.nextInt();
        		  int to = sc.nextInt();
        		  int cap = sc.nextInt();
        		  sol.addEdge( i, from, to, cap );
        	  }
        	  sol.solveBFS();
	          input.close();
	          sc.close();
	      }
	      catch (IOException iox){System.out.println(iox);}
	}

	public SolutionLin(){
		nodes = new TreeMap<Integer,Node>();
	}
	
	public boolean BFS( int c )
	{
		LinkedList<Node> Q = new LinkedList<Node>();
		Q.add(nodes.get(0));
		
		while( !Q.isEmpty() )
		{
			Node u = Q.removeFirst();
			u.visited = true;
			for( Edge e : u.neighbors )
			{
				if( e.cap >= c )
				{
					Node v = e.to;
					if( v == u )
						v = e.from;
					if( ! v.visited )
					{
						v.previous = u;
						if( v.id == maxid )
							return true;
						Q.add(v);
					}
				}
			}
		}
		return false;
	}
	
	public void solveBFS()
	{
		boolean found = false;
		int c = 500000;
		for( ; c >= 1 && ! found; c-- )
		{
			for( Node n : nodes.values() )
			{
				n.visited = false;
				n.previous = null;
			}
			found = BFS( c );
		}
//	System.out.println( "Width: " + c );
  	  int nodeTo = -1;
  	  int nodeFrom = -1;
  	  TreeSet<Integer> blocked = new TreeSet<Integer>();
  	  Node s = nodes.get(maxid);
  	  int nodeC = -1;
  	  while( s != null )
  	  {
  		  // print edges except incoming and outgoing
  		  if( s.previous != null )
  			  nodeFrom = s.previous.id;
  		  else
  			  nodeFrom = -1;
  		  nodeC = s.id;
//  	  	  System.out.println( "Via " + nodeC + " nodeFrom: " + nodeFrom + " nodeTo: " + nodeTo);
  		  for( Edge e : nodes.get(s.id).neighbors )
  		  {
  			  if( ! (e.from.id == nodeFrom && e.to.id == nodeC) &&
  					! (e.to.id == nodeFrom && e.from.id == nodeC) &&
  					! (e.from.id == nodeTo && e.to.id == nodeC) &&
  	  					! (e.to.id == nodeTo && e.from.id == nodeC)  )
  				  blocked.add(e.id);
  		  }
  		  s = s.previous;
  		  nodeTo = nodeC;
  	  }
  	  if( blocked.size()> 0)
  	  {
	  	  StringBuilder list = new StringBuilder();
	  	  for( Integer i : blocked )
	  	  {
	  		  list.append(i + " ");
	  	  }
	  	  System.out.println( list );
  	  }
  	  else
  	  	  System.out.println( "none" );

	}
	
	public void addEdge(int id, int from, int to, int cap )
	{
		Node f = nodes.get( from );
		if( f == null )
		{
			f = new Node( from );
			nodes.put( from, f );
		}
		Node t = nodes.get( to );
		if( t == null )
		{
			t = new Node( to );
			nodes.put( to, t );
		}
		Edge e = new Edge( id, f, t, cap );
		t.addNeighbor(e);
		f.addNeighbor(e);

	}
		
	protected class Node {
		ArrayList<Edge> neighbors;
		int id;
		boolean visited;
		Node previous;
		
		public Node( int id )
		{
			this.id = id;
			if( id > SolutionLin.maxid )
				SolutionLin.maxid = id;
			neighbors = new ArrayList<Edge>();
			visited = false;
			previous = null;
		}
		
		public void addNeighbor( Edge e )
		{
			neighbors.add(e);
		}
	}
	
	protected class Edge  {
		Node from;
		Node to;
		int cap;
		int id;
		
		public Edge( int id, Node from, Node to, int cap )
		{
			this.id = id;
			this.from = from;
			this.to = to;
			this.cap = cap;
		}
		
	}
	
}
