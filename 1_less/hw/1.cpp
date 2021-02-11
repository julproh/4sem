// mldkgdflkmd
#include <iostream>
#include <vector>

using namespace std;

int main() {

    cout << "Hello, world!" << endl;

    //comment
    //qwerty

 //new_branch
    return 0;
}

/*
merge создаёт коммит слияния
коммит A ->
           |-> merge коммит C
коммит B ->
По сути merge создаёт историю.
А rebase меняет свою историю. Допустим вы написали свою работа D используя только видимую ветку коммит A.
         > работа D 
        /
коммит A ->
           |-> merge коммит C
коммит B ->

но передумали и перенесли всю свою работу в появившуюся ветку коммит B. И сделали rebase на коммит B :

коммит A ->
           |-> merge коммит C
коммит B ->
        \
         > работа D

rebase используют если хотят продолжить работу основываясь от чьей-то работы другого человека.
 Все коммиты вашей ветки работа D это новые коммиты, всё переписывается по-новой и забывается всё старое.
 И есть возможность продолжать вашу ветку как без слияния так и с ним. rebase имеет разрушительное действие для истории. 
*/