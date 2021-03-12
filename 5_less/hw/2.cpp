
#include <iostream>
#include <boost/locale.hpp>
#include <bitset>
#include <string>
#include <locale.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std; 

// std::string convert_locale_to_utf(const string& str)
// {
// 	boost::locale::generator generator;
// 	generator.locale_cache_enabled(true);

// 	std::locale locale =
// 		generator(boost::locale::util::get_system_locale());

// 	return boost::locale::conv::to_utf < char >(str, locale);
// }

// string convert_utf_to_locale(const string& str)
// {
// 	boost::locale::generator generator;
// 	generator.locale_cache_enabled(true);

// 	std::locale locale =
// 		generator(boost::locale::util::get_system_locale());

// 	return boost::locale::conv::from_utf < char >(str, locale);
// }


int main() {
	
	vector<pair<char, char32_t>> conv = 
	{
		make_pair('а','a'),make_pair('б','b'),make_pair('в','v'),make_pair('г','g'),make_pair('д','d'),
		make_pair('е','e'),make_pair('ж','j'),make_pair('з','z'),make_pair('и','i'),make_pair('ы','i'),
		make_pair('й','y'),make_pair('к','k'),make_pair('л','l'),make_pair('м','m'),make_pair('н','n'),
		make_pair('о','o'),make_pair('п','p'),make_pair('р','R'),make_pair('с','s'),make_pair('т','t'),
		make_pair('у','u'),make_pair('ф','f'),make_pair('x','h'),make_pair('ц','c'),make_pair('ч','сh'),
		make_pair('ш','sh'),make_pair('щ','sh'),make_pair('ъ','\''),make_pair('ь','\''),make_pair('э','ie'),
		make_pair('ю','iu'),make_pair('я','ia') 
	};
    string line = "отличная погодка намечается" ;

    //cin >> line;
    // string u8str = convert_locale_to_utf(line);
	// cout << u8str << endl;
	//u32string u32str =boost::locale::conv::utf_to_utf < char32_t, char > (line);
	//u32string newline;
	
	string newline;
	for (auto c : line) {
		for(auto i: conv) {
			if (i.first == c) {
				newline.push_back(i.second);
				break;
			}
			else if (c == ' ') {
				newline.push_back(' ');
				break;
			}
			}
	}
	

	
	//string newline8 = boost::locale::conv::utf_to_utf < char, char32_t >(newline);
	cout << newline << endl;
	
}

