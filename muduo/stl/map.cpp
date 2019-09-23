#include <map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort() and rand() and RAND_MAX
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
using namespace std;
namespace jj14
{
    long get_a_target_long()
    {
        long target=0;
        cout << "target (0~" << RAND_MAX << "): ";
        cin >> target;
        return target;
    }
    void test_map(long& value)
    {
        cout << "\ntest_map().......... \n";

        map<long, string> c;   
        char buf[10];

        clock_t timeStart = clock();                                
        for(long i=0; i< value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c[i] = string(buf);                     
            }
            catch(exception& p) {
                cout << "i=" << i << " " << p.what() << endl;   
                abort();
            }
        }
        cout << "milli-seconds : " << (clock()-timeStart) << endl;  
        cout << "map.size()= " << c.size() << endl; 
        cout << "map.max_size()= " << c.max_size() << endl;     //178956970

        long target = get_a_target_long();      
        timeStart = clock();        
        auto pItem = c.find(target);                                
        cout << "c.find(), milli-seconds : " << (clock()-timeStart) << endl;         
        if (pItem != c.end())
            cout << "found, value=" << (*pItem).second << endl;
        else
            cout << "not found! " << endl;          

        c.clear();                  
    }                                                            
}

int main() {
    long value;
    cout << "how many elements: ";
    cin >> value;       
    jj14::test_map(value);
}
