
#include <iostream>
#include <boost/locale.hpp>
#include <bitset>
#include <string>
#include <locale.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

using namespace std; 

int main() {
	

	unordered_map<char32_t,basic_string<char32_t>> translit_table = {
    {U'а',U"a"}, {U'б',U"b"}, {U'в',U"v"},
    {U'г',U"g"}, {U'д',U"d"}, {U'е',U"e"},
	{U'ё',U"yo"}, {U'ж',U"zh"},{U'з',U"z"},
    {U'и',U"i"}, {U'й',U"j"}, {U'к',U"k"},
    {U'л',U"l"}, {U'м',U"m"}, {U'н',U"n"},
    {U'о',U"o"}, {U'п',U"p"}, {U'р',U"r"},
    {U'с',U"s"}, {U'т',U"t"}, {U'у',U"u"},
    {U'ф',U"f"}, {U'х',U"x"}, {U'ц',U"c"},
    {U'ч',U"ch"}, {U'ш',U"sh"}, {U'щ',U"shh"},
    {U'ъ',U"``"}, {U'ы',U"y`"}, {U'ь',U"`"},
    {U'э',U"e`"}, {U'ю',U"yu"}, {U'я',U"ya"},
    {U'А',U"A"}, {U'Б',U"B"}, {U'В',U"V"},
    {U'Г',U"G"}, {U'Д',U"D"}, {U'Е',U"E"},
    {U'Ё',U"YO"}, {U'Ж',U"ZH"}, {U'З',U"Z"},
    {U'И',U"I"}, {U'Й',U"J"}, {U'К',U"K"},
    {U'Л',U"L"}, {U'М',U"M"}, {U'Н',U"N"},
    {U'О',U"O"}, {U'П',U"P"}, {U'Р',U"R"},
    {U'С',U"S"}, {U'Т',U"T"}, {U'У',U"U"},
    {U'Ф',U"F"}, {U'Х',U"X"}, {U'Ц',U"X"},
    {U'Ч',U"CH"}, {U'Ш',U"SH"}, {U'Щ',U"SHH"},
    {U'Ъ',U"``"}, {U'Ы',U"Y`"}, {U'Ь',U"`"},
    {U'Э',U"E`"}, {U'Ю',U"YU"},{U'Я',U"YA"},
    {U' ',U" "},
    };


	
    string line = "отличная погодка намечается" ;

	std::cout << line << endl;
	u32string u32str =boost::locale::conv::utf_to_utf < char32_t, char > (line);
	u32string newline;
	
	 for (auto c : u32str) {
		for(auto i: translit_table) {
			if (i.first == c) {
				newline.append(i.second);
				break;
			}
			else if (c == ' ') {
				newline.append(U" ");
				break;
			}
			}
	}
	

	string newline8 = boost::locale::conv::utf_to_utf < char, char32_t >(newline);
	std::cout << newline8 << endl;
	
}

