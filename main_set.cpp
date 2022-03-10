#include "set.hpp"
#include <set>
#ifdef STD
    using namespace std;
#else
    using namespace ft;
#endif
int     main()
{
    std::cout << "..............Equal_range..............." << std::endl << std::endl;
    {
        set<int> myset;
        myset.insert(10);
        myset.insert(20);
        myset.insert(30);
        pair<set<int>::iterator,set<int>::iterator> ret;
        ret = myset.equal_range(20);
        std::cout << "lower bound points to: ";
        std::cout << *ret.first << '\n';
        std::cout << "upper bound points to: ";
        std::cout << *ret.second << '\n';
    }
    std::cout << ".......Lower_bound / Upper_bound........" << std::endl << std::endl;
    {
        set<int> myset;
        set<int>::iterator itlow,itup;
        myset.insert(20);
        myset.insert(40);
        myset.insert(60);
        myset.insert(80);
        myset.insert(100);
        itlow=myset.lower_bound(40);  // itlow points to b
        itup=myset.upper_bound(80);   // itup points to e (not d!)
        myset.erase(itlow,itup);        // erases [itlow,itup)
        // print content:
        for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "...............Count................." << std::endl << std::endl;
    {
        set<char> myset;
        char c;
        myset.insert('a');
        myset.insert('f');
        myset.insert('c');
        for (c='a'; c<'h'; c++)
        {
            std::cout << c;
            if (myset.count(c)>0)
                std::cout << " is an element of myset.\n";
            else
                std::cout << " is not an element of myset.\n";
        }
    }
    std::cout << "...............Find.................." << std::endl << std::endl;
    {
        set<char> myset;
        set<char>::iterator it;
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        myset.insert('d');
        it = myset.find('b');
        if (it != myset.end())
            myset.erase (it);
        // print content:
        std::cout << "elements in myset:" << '\n';
        std::cout << "a => " << *myset.find('a') << '\n';
        std::cout << "c => " << *myset.find('c') << '\n';
        std::cout << "d => " << *myset.find('d') << '\n';
    }
    std::cout << ".............Value_comp.............." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('x');
        myset.insert('y');
        myset.insert('z');
        std::cout << "myset contains:\n";
        char highest = *myset.rbegin();          // last element
        set<char>::iterator it = myset.begin();
        do {
            std::cout << *it << '\n';
        } while ( myset.value_comp()(*it++, highest) );
        std::cout << '\n';
    }
    std::cout << "..............Key_comp..............." << std::endl << std::endl;
    {
        set<char> myset;
        set<char>::key_compare mycomp = myset.key_comp();
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        std::cout << "myset contains:\n";
        char highest = *myset.rbegin();     // key value of last element
        set<char>::iterator it = myset.begin();
        do {
            std::cout << *it << '\n';
        } while ( mycomp((*it++), highest) );
        std::cout << '\n';
    }
    std::cout << "...............Clear................." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('x');
        myset.insert('y');
        myset.insert('z');
        std::cout << "myset contains:\n";
        for (set<char>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
        myset.clear();
        myset.insert('a');
        myset.insert('b');
        std::cout << "myset contains:\n";
        for (set<char>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
}
	/*
    std::cout << "...............Swap.................." << std::endl << std::endl;
    {
        set<char,int> foo,bar;
        foo['x']=100;
        foo['y']=200;
        bar['a']=11;
        bar['b']=22;
        bar['c']=33;
        foo.swap(bar);
        std::cout << "foo contains:\n";
        for (set<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "bar contains:\n";
        for (set<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "...............Erase................." << std::endl << std::endl;
    {
        set<char,int> myset;
        set<char,int>::iterator it;
        // insert some values:
        myset['a']=10;
        myset['b']=20;
        myset['c']=30;
        myset['d']=40;
        myset['e']=50;
        myset['f']=60;
        it=myset.find('b');
        myset.erase (it);                   // erasing by iterator
        myset.erase ('c');                  // erasing by key
        it=myset.find ('e');
        myset.erase ( it, myset.end() );    // erasing by range
        // show content:
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "..............Insert................." << std::endl << std::endl;
    {
        set<char,int> myset;
        // first insert function version (single parameter):
        myset.insert ( pair<char,int>('a',100) );
        myset.insert ( pair<char,int>('z',200) );
        pair<set<char,int>::iterator,bool> ret;
        ret = myset.insert ( pair<char,int>('z',500) );
        if (ret.second==false) {
            std::cout << "element 'z' already existed";
            std::cout << " with a value of " << ret.first->second << '\n';
        }
        // second insert function version (with hint position):
        set<char,int>::iterator it = myset.begin();
        myset.insert (it, pair<char,int>('b',300));  // max efficiency inserting
        myset.insert (it, pair<char,int>('c',400));  // no max efficiency inserting
        // third insert function version (range insertion):
        set<char,int> anotherset;
        anotherset.insert(myset.begin(),myset.find('c'));
        // showing contents:
        std::cout << "myset contains:\n";
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "anotherset contains:\n";
        for (it=anotherset.begin(); it!=anotherset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << ".............Operator[].............." << std::endl << std::endl;
    {
        set<char,std::string> myset;
        myset['a']="an element";
        myset['b']="another element";
        myset['c']=myset['b'];
        std::cout << "myset['a'] is " << myset['a'] << '\n';
        std::cout << "myset['b'] is " << myset['b'] << '\n';
        std::cout << "myset['c'] is " << myset['c'] << '\n';
        std::cout << "myset['d'] is " << myset['d'] << '\n';
        std::cout << "myset now contains " << myset.size() << " elements.\n";
    }
    std::cout << "..............Max_Size..............." << std::endl << std::endl;
    {
        int i;
        set<int,int> myset;
        if (myset.max_size()>1000)
        {
            for (i=0; i<1000; i++) myset[i]=0;
            std::cout << "The set contains 1000 elements.\n";
        }
        else std::cout << "The set could not hold 1000 elements.\n";
    }
    std::cout << "...............Size.................." << std::endl << std::endl;
    {
        set<char,int> myset;
        myset['a']=101;
        myset['b']=202;
        myset['c']=302;
        std::cout << "myset.size() is " << myset.size() << '\n';
    }
    std::cout << "............Empty....................." << std::endl << std::endl;
    {
        set<char,int> myset;
        myset['a']=10;
        myset['b']=20;
        myset['c']=30;
        while (!myset.empty())
        {
            std::cout << myset.begin()->first << " => " << myset.begin()->second << '\n';
            myset.erase(myset.begin());
        }
    }
    std::cout << "..........Reverse Iterators..........." << std::endl << std::endl;
    {
        set<char,int> myset;
        myset['x'] = 100;
        myset['y'] = 200;
        myset['z'] = 300;
        // show content:
        set<char,int>::reverse_iterator rit;
        for (rit=myset.rbegin(); rit!=myset.rend(); ++rit)
            std::cout << rit->first << " => " << rit->second << '\n';
    }
    std::cout << "..............Iterators..............." << std::endl << std::endl;
    {
        set<char,int> myset;
        myset['b'] = 100;
        myset['a'] = 200;
        myset['c'] = 300;
        // show content:
        for (set<char,int>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "............Operator=............" << std::endl << std::endl;
    {
        set<char,int> first;
        set<char,int> second;
        first['x']=8;
        first['y']=16;
        first['z']=32;
        second=first;                // second now contains 3 ints
        first=set<char,int>();  // and first is now empty
        std::cout << "Size of first: " << first.size() << '\n';
        std::cout << "Size of second: " << second.size() << '\n';
    }
    std::cout << "...........Erase..........." << std::endl << std::endl;
    {
        set<char,int> myset;
        set<char,int>::iterator it;
        // insert some values:
        myset['a']=10;
        myset['b']=20;
        myset['c']=30;
        myset['d']=40;
        myset['e']=50;
        myset['f']=60;
        it=myset.find('b');
        myset.erase (it);                   // erasing by iterator
        myset.erase ('c');                  // erasing by key
        it=myset.find ('e');
        myset.erase ( it, myset.end() );    // erasing by range
        // show content:
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "..........Upper_bound and Lower_bound.........." << std::endl << std::endl;
    {
        set<char,int> myset;
        set<char,int>::iterator itlow,itup;
        myset['a']=20;
        myset['b']=40;
        myset['c']=60;
        myset['d']=80;
        myset['e']=100;
        itlow = myset.lower_bound ('b');  // itlow points to b
        itup = myset.upper_bound ('d');   // itup points to e (not d!)
        myset.erase(itlow,itup);        // erases [itlow,itup)
        // print content:
        for (set<char,int>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "..............Equal_range............" << std::endl << std::endl;
    {
        set<char,int> myset;
        myset['a']=10;
        myset['b']=20;
        myset['c']=30;
        pair<set<char,int>::iterator,set<char,int>::iterator> ret;
        ret = myset.equal_range('b');
        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';
        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';
    }
}
*/
