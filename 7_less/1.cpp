/*
 Параллельное программирование (mt)

 Можно выполнять сразу несколько задач одновременно

 Псевдопараллелизм - быстро чередуем
 или же каждой задаче даем свое ядро

ps -e - команда шоб посмотреть задачи

Multi-proccessed
Multy-threading  thread



dead_lock - тупик

Приципы puc-||-

1 - по данным
2 - по задачам
T1 - время работы нераспараллеленого алгоритнма
Tn - время работы распараллеренного на n ядер алгоритма
\alpha - доля нерапспараллеленного кода

S = T1/Tn = T1/()

s/n - эффективность

thread_safety - защищенность


_______________________ что то с future
1  - async
2 - packed_task
3 - promise

future <int> result = std::async([](){return 42;});
...
result.get();
// result.wait();

//

std::packeged_task<int()> task([](){return 42;})
result = task.get_future();
std::thread(std::move(task)).detach();
...
x = result.get();

//

std::promise<int > p;
auto result = p.get_future();
std::thread([](std::promise<int> &p){p.set_value(42);}, std::ref(p).detach());
x = result.get();
____________________



*/