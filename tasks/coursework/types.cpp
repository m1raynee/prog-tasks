#include "types.hpp"

date::date(unsigned _year, short unsigned _month, short unsigned _day) {
  bytes[0] = _year & 0b11111111;
  bytes[1] = ((_year >> 8) & 0b00111111) | ((_month & 0b00000011) << 6);
  bytes[2] = ((_month >> 2) & 0b00000011) | ((_day & 0b00001111) << 2);
}
unsigned date::year() const {
  return bytes[0] | (unsigned)(bytes[1] & 0b00111111) << 8;
}
short unsigned date::month() const {
  return ((bytes[1] & 0b11000000) >> 6) | ((bytes[2] & 0b00000011) << 2);
}
short unsigned date::day() const {
  return (bytes[2] & 0b01111100) >> 2;
}
bool date::is_empty() const {
  return not(bytes[0] or bytes[1] or bytes[2]);
}
void date::print(ostream& os) const {
  os << std::setfill('0') << std::setw(4) << year() << '-' << std::setw(2)
     << month() << '-' << std::setw(2) << day() << std::setfill(' ');
}

bool operator==(const date& a, const date& b) {
  return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
}

bool operator<(const date& a, const date& b) {
  if (a.year() != b.year()) {
    return a.year() < b.year();
  }
  if (a.month() != b.month()) {
    return a.month() < b.month();
  }
  return a.day() < b.day();
}

bool operator!=(const date& a, const date& b) {
  return !(a == b);
}
bool operator>(const date& a, const date& b) {
  return b < a;
}
bool operator<=(const date& a, const date& b) {
  return !(b < a);
}
bool operator>=(const date& a, const date& b) {
  return !(a < b);
}

bool StrChunk::operator==(const StrChunk& other) {
  for (unsigned i = 0; i < STR_CHUNK_LENGTH; ++i)
    if (s[i] != other.s[i])
      return false;
  return true;
}

void StrChunk::print(ostream& out) {
  print(out, STR_CHUNK_LENGTH);
}

void StrChunk::print(ostream& out, unsigned count) {
  for (unsigned i = 0; i < count; ++i)
    out << s[i];
}

void StrChunk::destroy() {}

void Executor::destroy() {
  name.destroy();
  address.destroy();
  task_pool.destroy();
}

void Executor::print(ostream& out) {
  name.print(out);
  out << "\n\tАдрес: ";
  address.print(out);
}

void _Id::print(ostream& out) {
  out << id;
}

void Task::destroy() {
  name.destroy();
  executors.destroy();
}

void Task::print(ostream& out) {
  name.print(out);
  out << "\n\t(" << rate << " час(а/ов) за " << fee << " тыс. руб.)\n\t";
  if (completion_date.is_empty()) {
    out << "Не завершено\n";
  } else {
    out << "Дата завершения: " << completion_date.year() << '-'
        << completion_date.month() << '-' << completion_date.day()
        << ", объём работ: " << scope << " час(а/ов)\n";
  }
  if (!executors.is_empty()) {
    out << "\tИсполнители:\n";
    ExecutorN* p = executors.first;
    while (p) {
      out << "\t\t";
      p->value->name.print(out);
      out << '\n';
      p = p->next;
    }
  }
}

void MultiTask::destroy() {
  tasks.destroy();
  tasks.destroy();
}

std::ofstream& file::protocol() {
  static std::ofstream file("protocol.txt");
  return file;
}
std::ofstream& file::out() {
  static std::ofstream file("out.txt");
  return file;
}

bool Executor::operator==(Executor& b) {
  return service_number == b.service_number;
}