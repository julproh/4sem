/*Механизмы синхронизации

- поток (thread)
- разделяемые ресурсы (shared resources)
- состояние гонки (race condition) - результат зависит от очередности
- критическая секция (critical section)
- синхронность
- механизмы синхронизации (блокирующие и неблокирующие)
    - блокирующие - семафоры 
    - неблокирующие - атомарные операцииы

A -> B -> C
B синхронно с А "согласованно"

A -> C
^  ^ ^
|  | | - асинхронно
   В

Семафоры Дейкстры - разделяемая N переменная S = N, где N - местность семафора (6-ти местный семафор)

P(S) - S>0, S--
     - S<=0, S не меняется, а вызывающий поток блокируется

V(S) - S++
N=1 - mutex


*/
