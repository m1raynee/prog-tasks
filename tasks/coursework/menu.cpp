// 7.31. Проводится учет выполнения работ разного вида несколькими
// исполнителями. Требуется хранить информацию об исполнителях (ФИО, адрес,
// табельный номер), о работах (наименование, исполнители, норма на
// исполнителя/-ей, тариф) и о выполненных работах (исполнители, наименование,
// объем, дата завершения). Надо обеспечить возможность получения:
//     - общего списка работ и их исполнителей,
//     - списка выполненных работ на конкретную дату/период (группировка по
//     исполнителям и/или видам работ),
//     - работ, выполненных одним исполнителем,
//     - есть ли работы, выполненные одной и той же группой исполнителей.
// Для выполненных работ должна подсчитываться стоимость работ.
#include "menu.hpp"

void loop_main(LOOP_ARGS_DEFINITION) {
  os << "7.31. Проводится учет выполнения работ разного вида несколькими "
        "исполнителями.\n"
     << "Требуется хранить информацию об исполнителях (ФИО, адрес, табельный "
        "номер),\n"
     << "о работах (наименование, исполнители, норма на исполнителя/-ей, "
        "тариф)\n"
     << "и о выполненных работах (исполнители, наименование, объем, дата "
        "завершения).\n"
     << "Надо обеспечить возможность получения:\n"
     << "     - общего списка работ и их исполнителей,\n"
     << "     - списка выполненных работ на конкретную дату/период "
        "(группировка по исполнителям и/или видам работ),\n"
     << "     - работ, выполненных одним исполнителем,\n"
     << "     - есть ли работы, выполненные одной и той же группой "
        "исполнителей.\n"
     << " Для выполненных работ должна подсчитываться стоимость работ.\n\n";

  do {
    os << "Выберите пункт меню вывода:\n"
       << "(1) общий список работ и их исполнителей\n"
       << "(2) список выполненных работ на конкретную дату/период\n"
       << "(3) работы, выполненные одним исполнителем,\n"
       << "(4) работы, выполненные одной и той же группой исполнителей,\n"
       << "что угодно для выхода" << '\n';

    char menu_selector;
    is >> menu_selector;
    ExecutorN* exec_node;
    switch (menu_selector) {
      case '1':
        info_tasks_list(os, tasks);
        break;
      case '2':
        loop_date_select(LOOP_ARGS);
        break;
      case '3':
        exec_node = loop_executor_select(LOOP_ARGS);
        if (exec_node)
          info_tasks_of_executor(os, exec_node->value);
        break;
      case '4':
        loop_executors_group_select(LOOP_ARGS);
        break;
      default:
        return;
    }
  } while (true);
}
void info_tasks_list(std::ostream& os, list<Task>& tasks) {
  os << "Список всех работ и их исполнителей:\n";
  file::out() << "Список всех работ и их исполнителей:\n";

  unsigned count = 0;
  TaskN* p = tasks.first;
  while (p) {
    count++;
    p->value->print(os);
    p->value->print(file::out());
    p = p->next;
  }
  os << "Всего: " << count << std::endl;
  file::out() << "Всего: " << count << std::endl;
}

void loop_date_select(LOOP_ARGS_DEFINITION) {
  date begin(0, 0, 0);
  date end(0, 0, 0);
  do {
    os << "Начало периода в формате (YYYY MM DD): ";
    is >> begin;
    if (begin.is_empty())
      os << "Введите валидную дату\n";
  } while (begin.is_empty());
  do {
    os << "Конец периода в формате (YYYY MM DD).\nДля выбора одного для, "
          "повторите его здесь: ";
    is >> end;
    if (end.is_empty())
      os << "Введите валидную дату\n";
  } while (end.is_empty());

  char selector;
  os << "Выберите метод группировки:\n"
     << "(1) по исполнителям\n"
     << "(2) по работам\n"
     << "что-либо ещё для отмены\n";
  is >> selector;
  os << "В даты с ";
  begin.print(os);
  os << " по ";
  end.print(os);
  os << " были выполнены следующие работы:\n";

  file::out() << "В даты с ";
  begin.print(file::out());
  file::out() << " по ";
  end.print(file::out());
  file::out() << " были выполнены следующие работы:\n";

  switch (selector) {
    case '1':
      info_tasks_date_by_executors(os, executors, begin, end);
      break;
    case '2':
      info_tasks_date_by_task(os, tasks_pool.completed_tasks, begin, end);
      break;
    default:
      return;
  }
}

void info_tasks_date_by_executors(std::ostream& os,
                                  list<Executor>& executors,
                                  date beg,
                                  date end) {
  auto condition = [beg, end](TaskN* tp) {
    return tp->value->completion_date <= end and
           tp->value->completion_date >= beg;
  };
  ExecutorN* p = executors.first;
  while (p) {
    TaskN* task_p = p->value->task_pool.completed_tasks.first;
    if (task_p and condition(task_p)) {
    }
    bool first = true;
    while (task_p) {
      if (condition(task_p)) {
        if (first) {
          os << "Исполнитель {";
          p->value->name.print(os);
          os << "}:\n";
          first = false;

          file::out() << "Исполнитель {";
          p->value->name.print(file::out());
          file::out() << "}:\n";
          first = false;
        }
        os << '\t';
        task_p->value->completion_date.print(os);
        os << ' ';
        task_p->value->name.print(os);
        os << '\n';

        file::out() << '\t';
        task_p->value->completion_date.print(file::out());
        file::out() << ' ';
        task_p->value->name.print(file::out());
        file::out() << '\n';
      }
      task_p = task_p->next;
    }
    p = p->next;
    if (!first) {
      os << '\n';
      file::out() << '\n';
    }
  }

  os << std::endl;
  file::out() << std::endl;
}
void info_tasks_date_by_task(std::ostream& os,
                             list<Task>& completed_tasks,
                             date beg,
                             date end) {
  TaskN* p = completed_tasks.first;
  while (p) {
    if (p->value->completion_date <= end and p->value->completion_date >= beg) {
      os << "\tЗадача ";
      p->value->completion_date.print(os);
      os << " {";
      p->value->name.print(os);
      os << "}\n";

      file::out() << "\tЗадача ";
      p->value->completion_date.print(file::out());
      file::out() << " {";
      p->value->name.print(file::out());
      file::out() << "}\n";
    }
    p = p->next;
  }
  os << std::endl;
  file::out() << std::endl;
}

ExecutorN* loop_executor_select(LOOP_ARGS_DEFINITION) {
  ExecutorN* p = nullptr;
  do {
    os << "Введите табельный номер исполнителя (0 для выхода из выбора "
          "исполнителя): ";
    unsigned number;
    is >> number;
    p = executors.first;
    if (number == 0)
      return nullptr;
    while (p and p->value->service_number != number)
      p = p->next;
    if (!p)
      os << "Исполнитель не найден, попробуйте ещё раз\n";
  } while (!p);
  return p;
}
void info_tasks_of_executor(std::ostream& os, Executor* executor) {
  unsigned count = 0;
  os << "Задачи исполнителя {";
  executor->name.print(os);
  os << "}:\n------------------------------------\n";

  file::out() << "Задачи исполнителя {";
  executor->name.print(file::out());
  file::out() << "}:\n------------------------------------\n";

  TaskN* p = executor->task_pool.tasks.first;
  while (p) {
    p->value->print(os);
    p->value->print(file::out());
    p = p->next;
    ++count;
  }
  os << "------------------------------------\n";
  file::out() << "------------------------------------\n";
  p = executor->task_pool.completed_tasks.first;
  while (p) {
    p->value->print(os);
    p->value->print(file::out());
    p = p->next;
    ++count;
  }
  os << "------------------------------------\n";
  os << "Всего: " << count << std::endl;
  file::out() << "------------------------------------\n";
  file::out() << "Всего: " << count << std::endl;
}

void loop_executors_group_select(LOOP_ARGS_DEFINITION) {
  list<Executor> virtual_executors{true};
  list<Task> virtual_tasks_selected{true};
  ExecutorN* p;
  TaskN *q, *prev;
  unsigned e_count = 0;
  unsigned t_count = 0;
  do {
    os << "Для исполнителя №" << e_count + 1 << ':';
    p = loop_executor_select(LOOP_ARGS);
    if (p) {
      ++e_count;
      virtual_executors.push_back(p->replicate());
      if (virtual_tasks_selected.is_empty()) {
        q = tasks.first;
        while (q) {
          if (q->value->executors.in_value(*p->value)) {
            virtual_tasks_selected.push_back(q->replicate());
            ++t_count;
          }
          q = q->next;
        }
      } else {
        prev = nullptr;
        q = virtual_tasks_selected.first;
        while (q) {
          if (!q->value->executors.in_value(*p->value)) {
            if (prev == nullptr) {
              virtual_tasks_selected.first = virtual_tasks_selected.first->next;
              delete q;
              q = virtual_tasks_selected.first;
            } else {
              prev->next = q->next;
              delete q;
              q = prev->next;
            }
            --t_count;
          } else {
            prev = q;
            q = q->next;
          }
        }
      }
      os << "Выбрано задач: " << t_count << '\n';
    }
  } while (p);

  os << '\n';
  info_group_tasks(os, virtual_executors, e_count, virtual_tasks_selected,
                   t_count);
  virtual_executors.destroy();
  virtual_tasks_selected.destroy();
}
void info_group_tasks(std::ostream& os,
                      list<Executor> executors,
                      unsigned e,
                      list<Task> tasks,
                      unsigned t) {
  if (executors.is_empty()) {
    os << "Не выбрано ни одного исполнителя\n\n";
    return;
  }
  os << "Для исполнителей (кол-во: " << e << ") выбрано задач в количестве "
     << t << " шт.:\n"
     << "Исполнители:\n";
  file::out() << "Для исполнителей (кол-во: " << e
              << ") выбрано задач в количестве " << t << " шт.:\n"
              << "Исполнители:\n";

  ExecutorN* ep = executors.first;
  while (ep) {
    os << '\t';
    ep->value->name.print(os);
    os << '\n';
    file::out() << '\t';
    ep->value->name.print(file::out());
    file::out() << '\n';
    ep = ep->next;
  }
  os << '\n';
  file::out() << '\n';

  TaskN* tp = tasks.first;
  while (tp) {
    tp->value->name.print(os);
    os << '\n';
    tp->value->name.print(file::out());
    file::out() << '\n';
    if (!executors.is_empty()) {
      os << "\tИсполнители:\n";
      file::out() << "\tИсполнители:\n";
      ExecutorN* ep_print = tp->value->executors.first;
      while (ep_print) {
        os << "\t\t";
        file::out() << "\t\t";
        if (executors.in_value(*ep_print->value)) {
          os << "> ";
          file::out() << "> ";
        }
        ep_print->value->name.print(os);
        os << '\n';
        ep_print->value->name.print(file::out());
        file::out() << '\n';
        ep_print = ep_print->next;
      }
    }
    tp = tp->next;
  }
  os << std::endl;
  file::out() << std::endl;
}
