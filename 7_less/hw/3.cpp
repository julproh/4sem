#include<iterator>
#include<vector>
#include<algorithm>
#include <numeric>
#include<thread>
#include <future>
#include<iostream>

using namespace std;

template < typename Iterator, typename Function >
void parallel_for_each(Iterator first, Iterator last, Function function)
{
    size_t length = 25;

    if ( length >= distance(first, last))
	{
		for_each(first, last, function);
	}
    else
	{
        vector <future<void>> f;
        for (auto i = 0; i < std::distance(first, last)/length; i++) {

            Iterator current = first;
            for (auto j=0; j < i*25; j++){
                current++;
            }

            Iterator itog = current; 
            if (distance(current, last) > 25){
                for (auto j=0; j < 25; j++){
                itog++;
            }
            } else {
                itog = last;
            }

		    f.push_back(async(parallel_for_each < Iterator, Function>, current, itog, function));
	    }
    }

}


int main() {

    vector<int> v(10);
    iota(v.begin(), v.end(), 1);
    
    parallel_for_each(v.begin(), v.end(), [](int& i) {i++;});

    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}