/**
 * Dijkstra variant
 */

import java.util.*;
import java.io.*;

/**
 * @author mathijs
 * p009 Paris
 * with variant of Dijkstra, replacing min distance with max bottleneck
 * O( m log n )
 */
public class Solution {
	TreeMap<Integer,Node> nodes;
	static int maxid = 0;

	public static void main(String[] args) {
		try{
			InputStream input = System.in;
			Scanner sc = new Scanner(input);
			Solution sol = new Solution();
			int n = sc.nextInt();
			int m = sc.nextInt();
			sol.maxid = n-1;
			for( int i = 0; i < m; ++i )
			{
				int from = sc.nextInt();
				int to = sc.nextInt();
				int cap = sc.nextInt();
				sol.addEdge( i, from, to, cap );
			}
			sol.solveDijkstra();
			input.close();
			sc.close();
		}
		catch (IOException iox){System.out.println(iox);}
	}

	public Solution(){
		nodes = new TreeMap<Integer,Node>();
	}

	public void solveDijkstra()
	{
		//		for( Node n : nodes.values() )
		//		{
		//			System.out.print( "node: " + n.id + n + " with: ");
		//			for( Edge e : n.neighbors )
		//				System.out.print( "(" + e.from.id + "," + e.to.id + ") ");
		//			System.out.println();
		//		}
		PriorityQueue<State> Q = new PriorityQueue<State>();
		// contains width of bottleneck, and position
		State s = new State( 0, Integer.MAX_VALUE, null);
		Q.add(s);
		while(! Q.isEmpty())
		{
			s = Q.remove();
			if( s.id == maxid )
				break;
			Node n = nodes.get(s.id); 
			n.visited = true;
			int cap = 0;
			int pto = 0;
			for( Edge e : n.neighbors ){
				Node to = e.to;
				if( to.id == s.id )
					to = e.from;
				if( ! to.visited )
				{
					int w = Math.min(s.width, e.cap); 
					State nb = new State( to.id , w, s );
					Q.add(nb);
				}
			}
		}
		int nodeC = s.id;
		int nodeTo = -1;
		int nodeFrom = -1;
		TreeSet<Integer> blocked = new TreeSet<Integer>(); 
		//System.out.println( "width: " + s.width );
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
			boolean first = true;
			for( Integer i : blocked )
			{
				if (first){
					list.append(i);
					first = false;
				} else
					list.append(" "+i);
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

		public Node( int id )
		{
			this.id = id;
			neighbors = new ArrayList<Edge>();
			visited = false;
		}

		public void addNeighbor( Edge e )
		{
			neighbors.add(e);
		}
	}

	//	protected class Edge implements Comparable<Edge> {
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

		//@Override
		//public int compareTo( Edge other )
		//{
		//	return other.to.id - this.to.id;
		//}


	}

	protected class State implements Comparable<State> {
		int width;
		int id;
		State previous;

		public State( int id, int width, State p )
		{
			this.id = id;
			this.width = width;
			this.previous = p;
			//if( p != null )
			//	System.out.println( "State " + id + " width " + width + " previous " + p.id);
			//else
			//	System.out.println( "State " + id + " width " + width + " previous -1");
		}

		@Override
		public int compareTo( State other )
		{
			return other.width - this.width;
		}

	}	
	}
