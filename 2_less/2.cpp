#include <iostream>
#include <tuple>

using namespace std;

template <int Index, int Max,  typename...Types>
struct Tuple_Printer{
    static void print(ostream& stream, const tuple<Types...> &tuple){
        stream << get<Index>(tuple) << (Index + 1 == Max? "" : ", ");
        Tuple_Printer <Index+1, Max, Types...> :: print(stream, tuple);
    }
};

template <int Max, typename ...Types>
struct Tuple_Printer <Max, Max, Types...>
{
    static void print(ostream& stream, const std::tuple <Types...> &tuple) {};
};

template <typename... Types>
ostream& operator << (ostream &stream, const std::tuple<Types...> &tuple) {
    Tuple_Printer <0, sizeof...(Types), Types...> :: print(stream, tuple);
    return stream;
}

int main() {

    auto tuple = make_tuple(22, 43.55, "Hello");
    cout << tuple << endl;
    return 0;
}