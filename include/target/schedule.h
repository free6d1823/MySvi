#ifndef __SCHEDULE_H_INCLUDE__
#define __SCHEDULE_H_INCLUDE__

struct schedule_mailbox {
  int  case_id;
  void *arg;
  uint16_t status0;  // set by dispatcher (primary cpu)
  uint16_t status1;  // set by dispatched cpu after test case finished
  char log[64];
};

void schedule_start_transcation();
void schedule_end_transcation();
void schedule_notify_taskended();
void schedule_mailbox_log(const char *format, ...);
void schedule_mailbox_check();

struct schedule_mailbox* schedule_get_mb(int cpu);
int exec_case(int id, void *arg);
#endif
