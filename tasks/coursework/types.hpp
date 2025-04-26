#pragma once
#include "const.hpp"
#include "abstracts.hpp"

#define NODE_CONSTRAINT_FOR(NAME, SEP, END) \
void print(ostream& out);                   \
void destroy();                             \
inline static char sep[] = SEP;             \
inline static char end[] = END;

struct StrChunk;
using str = list<StrChunk, unsigned>;

struct date {
    // ```
    //     2           1           0
    // 0000 0000 | 0000 0000 | 0000 0000
    //  | day||month||        year     |
    // ```
    unsigned char bytes[3];
    date(
        unsigned year,
        short unsigned month,
        short unsigned day
    );
    unsigned year();
    short unsigned month();
    short unsigned day();
};

struct StrChunk {
    char s[STR_CHUNK_LENGTH]{};
    
    NODE_CONSTRAINT_FOR(StrChunk, " -> ", "nullptr\n")
    void print(ostream& out, int count);
    bool operator==(const StrChunk& other);
};

struct Task;
struct Executor {
    str initials{};
    str address{};
    unsigned service_number;

    list<Task> tasks{true};
    list<Task> completed_tasks{true};

    NODE_CONSTRAINT_FOR(Executor, "\n", "\n")
};

struct Task {
    str name{};
    unsigned rate;
    unsigned fee;

    // only completed_tasks
    unsigned scope;
    date completion_date;

    list<Executor> executors{true};

    NODE_CONSTRAINT_FOR(Task, "\n", "\n")
};

struct MultiTask {
    list<Task> tasks{true};
    list<Task> completed_tasks{true};
};

#include "types.ipp"