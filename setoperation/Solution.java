package org.creators;

import org.creators.coll.SetOpt;

public class Solution{
	public static void main(String args[]){
		SetOpt<String> st= new SetOpt<String>();
		SetOpt<String> st1= new SetOpt<String>();
		st.add("a");
		st.add("b");
		st.add("c");
		st.add("d");
		st.add("e");
		st.add("f");
		st1.add("a");
		st1.add("b");
		st1.add("e");
		st1.add("k");
		System.out.println(st.union(st,st1));
		System.out.println(st.intersection(st,st1));
		System.out.println(st.difference(st,st1));
		System.out.println(st.symDifference(st,st1));
		System.out.println(st.isSubset(st,st1));
		System.out.println(st.isSuperset(st,st1));
	}
}
