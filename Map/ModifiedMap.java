package org.creators;
import java.io.IOException;
import java.util.*;
public class ModifiedMap {
private static Scanner sc;

public static void main(String args[]) throws IOException {

	Map<String,Pair> mp=new TreeMap<String,Pair>();
	sc = new Scanner(System.in);
	int n;
	n=sc.nextInt();
	while(n>0){
		String s;
		Double f;
		s=sc.next();
		f=sc.nextDouble();
		if(mp.containsKey(s)){
			Pair p=mp.get(s);
			p.setKey1((Double)p.getKey1()+f);
			p.setKey2((Integer)p.getKey2()+1);
			mp.put(s,p);
		}else{
			
			Pair p=new Pair();
			p.setKey1(f);
			p.setKey2(1);
			mp.put(s,p);
		}
		n-=1;
	}
	for(Map.Entry<String,Pair> each: mp.entrySet()){
		System.out.println(each.getKey()+" "+each.getValue());
	}
}
}
