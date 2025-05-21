// 7.31. ѕроводитс€ учет выполнени€ работ разного вида несколькими
// исполнител€ми. “ребуетс€ хранить информацию об исполнител€х (‘»ќ, адрес,
// табельный номер), о работах (наименование, исполнители, норма на
// исполнител€/-ей, тариф) и о выполненных работах (исполнители, наименование,
// объем, дата завершени€). Ќадо обеспечить возможность получени€:
//     - общего списка работ и их исполнителей,
//     - списка выполненных работ на конкретную дату/период (группировка по
//     исполнител€м и/или видам работ),
//     - работ, выполненных одним исполнителем,
//     - есть ли работы, выполненные одной и той же группой исполнителей.
// ƒл€ выполненных работ должна подсчитыватьс€ стоимость работ.

#include "abstracts.hpp"
#include "file.hpp"
#include "linking.hpp"
#include "menu.hpp"
#include "types.hpp"

#include <windows.h>
#include <fstream>
#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::ifstream in_exec("workfiles/executors.txt");
  std::ifstream in_tasks("workfiles/tasks.txt");

  list<Executor> executors{};
  list<Task> tasks{};
  MultiTask tasks_pool{};
  in_exec >> executors;
  in_tasks >> tasks;

  file::protocol() << std::endl;
  link_executors_to_tasks(executors, tasks);
  fill_multitask(&tasks_pool, tasks);

  loop_main(std::cin, std::cout, tasks, executors, tasks_pool);

  return 0;
}