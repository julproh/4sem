#include<fstream>
#include<string>
#include<iostream>
#include<regex>
#include <iterator>


using namespace std;

int main()
{

    ifstream in("test.txt");
    if(!in.is_open()){
        cerr<<"Can't open \"test.txt\"!";
        exit(EXIT_FAILURE);
    }

    string stri, tmp;
    while(getline(in, tmp))
    {
        stri+=tmp;
        stri+="\n";
    }
    cout  << "Было:  "<< endl << stri << endl;
    regex pattern1("(//)");
    regex pattern2(".*");
    regex pattern3("([/]{1})"
                "([\*]{1})"
                "(.*)"
                "([\*]{1})"
                "([/]{1})");
    regex pattern4("([/]{1})"
                "([\*]{1})"
                "([\n]{0,})"
                "(.*)"
                "([\n]{0,})"
                "([\*]{1})"
                "([/]{1})");
    regex pattern5("([/]{1})"
                "([\*]{1})"
                "(.*)"
                "([\n]{0,})"
                "([\*]{1})"
                "([/]{1})");
    regex pattern6("([/]{1})"
                "([\*]{1})"
                "([\n]{0,})"
                "(.*)"
                "([\*]{1})"
                "([/]{1})");

   string str;

   cmatch result;

    while (regex_search(stri.c_str(),result,pattern5)) {
        str +=result.prefix().str();
        str += result[3];
        str += result[4];
        stri = result.suffix().str();
    }

    str += stri;
    stri = str;
    str = "";

    while (regex_search(stri.c_str(),result,pattern6)) {
        str +=result.prefix().str();
        str += result[3];
        str += result[4];
        stri = result.suffix().str();
    }

    str += stri;
    stri = str;
    str = "";

    while (regex_search(stri.c_str(),result,pattern3)) {
        str +=result.prefix().str();
        str += result[3];
        stri = result.suffix().str();
    }

    str += stri;
    stri = str;
    str = "";

    while (regex_search(stri.c_str(),result,pattern4)) {
        str +=result.prefix().str();
        str += result[3];
        str+=result[4];
        str +=result[5];
        stri = result.suffix().str();
    }

    str += stri;
    stri = str;
    str = "";


    while (regex_search(stri.c_str(),result,pattern1)) {
        str += result.prefix().str();
        stri = result.suffix().str();
       
    }
    str += stri;

    cout << "Стало: " << endl << str << endl;


    in.close();
     ofstream out("test.txt");
     out<<str;
     out.close();
    return 0;
}
// //qwerty
// //werrtyyu /* wejfdjdi */
// qwweret/*
// wer*/
// //qwewrr/t76787484y /*
// qgdyufuy */