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
    std::cout << "...............Swap.................." << std::endl << std::endl;
    {
        set<char> foo,bar;
        foo.insert('x');
        foo.insert('y');
        bar.insert('a');
        bar.insert('b');
        bar.insert('c');
        foo.swap(bar);
        std::cout << "foo contains:\n";
        for (set<char>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "bar contains:\n";
        for (set<char>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "...............Erase................." << std::endl << std::endl;
    {
        set<char> myset;
        set<char>::iterator it;
        // insert some values:
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        myset.insert('d');
        myset.insert('e');
        myset.insert('f');
        it=myset.find('b');
        myset.erase (it);                   // erasing by iterator
        myset.erase ('c');                  // erasing by key
        it=myset.find ('e');
        myset.erase ( it, myset.end() );    // erasing by range
        // show content:
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "..............Insert................." << std::endl << std::endl;
    {
        set<char> myset;
        // first insert function version (single parameter):
        myset.insert('a');
        myset.insert('z');
        pair<set<char>::iterator,bool> ret;
        ret = myset.insert('z');
        if (ret.second==false) {
            std::cout << "element 'z' already existed";
            std::cout << " with a value of " << *ret.first<< '\n';
        }
        // second insert function version (with hint position):
        set<char>::iterator it = myset.begin();
        myset.insert (it, 'b');
        myset.insert (it, 'c');
        // third insert function version (range insertion):
        set<char> anotherset;
        anotherset.insert(myset.begin(),myset.find('c'));
        // showing contents:
        std::cout << "myset contains:\n";
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it<< '\n' ;
        std::cout << "anotherset contains:\n";
        for (it=anotherset.begin(); it!=anotherset.end(); ++it)
            std::cout << *it<< '\n' ;
    }
    std::cout << "..............Max_Size..............." << std::endl << std::endl;
    {
        int i;
        set<int> myset;
        if (myset.max_size()>1000)
        {
            for (i=0; i<1000; i++) myset.insert(i);
            std::cout << "The set contains 1000 elements.\n";
        }
        else std::cout << "The set could not hold 1000 elements.\n";
    }
    std::cout << "...............Size.................." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        std::cout << "myset.size() is " << myset.size() << '\n';
    }
    std::cout << "............Empty....................." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        while (!myset.empty())
        {
            std::cout << *myset.begin() << '\n'; 
            myset.erase(myset.begin());
        }
    }
    std::cout << "..........Reverse Iterators..........." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('x');
        myset.insert('y');
        myset.insert('z');
        // show content:
        set<char>::reverse_iterator rit;
        for (rit=myset.rbegin(); rit!=myset.rend(); ++rit)
            std::cout << *rit << '\n';
    }
    std::cout << "..............Iterators..............." << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('b');
        myset.insert('a');
        myset.insert('c');
        // show content:
        for (set<char,int>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "............Operator=............" << std::endl << std::endl;
    {
        set<char> first;
        set<char> second;
        first.insert('x');
        first.insert('y');
        first.insert('z');
        second=first;                // second now contains 3 ints
        first=set<char>();  // and first is now empty
        std::cout << "Size of first: " << first.size() << '\n';
        std::cout << "Size of second: " << second.size() << '\n';
    }
    std::cout << "...........Erase..........." << std::endl << std::endl;
    {
        set<char> myset;
        set<char>::iterator it;
        // insert some values:
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        myset.insert('d');
        myset.insert('e');
        myset.insert('f');
        it=myset.find('b');
        myset.erase (it);                   // erasing by iterator
        myset.erase ('c');                  // erasing by key
        it=myset.find ('e');
        myset.erase ( it, myset.end() );    // erasing by range
        // show content:
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "..........Upper_bound and Lower_bound.........." << std::endl << std::endl;
    {
        set<char> myset;
        set<char>::iterator itlow,itup;
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        myset.insert('d');
        myset.insert('e');
        itlow = myset.lower_bound ('b');  // itlow points to b
        itup = myset.upper_bound ('d');   // itup points to e (not d!)
        myset.erase(itlow,itup);        // erases [itlow,itup)
        // print content:
        for (set<char,int>::iterator it=myset.begin(); it!=myset.end(); ++it)
            std::cout << *it << '\n';
    }
    std::cout << "..............Equal_range............" << std::endl << std::endl;
    {
        set<char> myset;
        myset.insert('a');
        myset.insert('b');
        myset.insert('c');
        pair<set<char>::iterator,set<char>::iterator> ret;
        ret = myset.equal_range('b');
        std::cout << "lower bound points to: ";
        std::cout << *ret.first << '\n';
        std::cout << "upper bound points to: ";
        std::cout << *ret.second << '\n';
    }
}
