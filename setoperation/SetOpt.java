package org.creators.coll;

import java.util.Collection;
import java.util.Set;
import java.util.TreeSet;

public class SetOpt<E> {
	
    private Set<E> set;
    
    public SetOpt() {
        this.set = new TreeSet<E>();
    }
    public SetOpt(Collection<E> set) {
        this.set = (Set<E>) set;
    }
    public int size() {
        return this.set.size();
    }
    public boolean isEmpty() {
        return this.set.isEmpty();
    }
    public void clear() {
        this.set.clear();
    }
    public boolean contains(Object o) {
        return this.set.contains(o);
    }
    public void remove(Object o) {
        this.set.remove(o);
    }
    public void add(E e) {
        this.set.add(e);
    }
    public SetOpt<E> union(SetOpt<E> a,SetOpt<E> b) {
        SetOpt<E> tmp = new SetOpt<E>();
        tmp.set.addAll(a.set);
        tmp.set.addAll(b.set);
        return tmp;
    }
    public SetOpt<E> intersection(SetOpt<E> a,SetOpt<E> b) {
    	SetOpt<E> tmp = new SetOpt<E>();
        tmp.set.addAll(a.set);
        tmp.set.retainAll(b.set);
        return tmp;
    }
    public SetOpt<E> difference(SetOpt<E> a,SetOpt<E> b) {
    	SetOpt<E> tmp = new SetOpt<E>();
        tmp.set.addAll(a.set);
        tmp.set.removeAll(b.set);
        return tmp;
    }
    public SetOpt<E> symDifference(SetOpt<E> a,SetOpt<E> b) {
    	SetOpt<E> tmp = new SetOpt<E>();
        tmp.set.addAll(a.set);
        SetOpt<E> tmp2 = new SetOpt<E>();
        tmp.set.addAll(b.set);
        tmp=union(a,b);
        tmp2=intersection(a,b);
        return difference(tmp,tmp2);
    }
    public  boolean isSubset(SetOpt<E> a,SetOpt<E> b) {
        return b.set.containsAll(a.set);
      }

    public  boolean isSuperset (SetOpt<E> a,SetOpt<E> b) {
        return a.set.containsAll(b.set);
    }
	@Override
	public String toString() {
		return ""+set;
	}
    
}
