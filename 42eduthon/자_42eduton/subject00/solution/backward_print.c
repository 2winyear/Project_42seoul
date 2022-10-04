#include <unistd.h>

void backward_solution(char *msg) {
  if (*msg == 0) return;
  backward_solution(msg + 1);
  write(1, msg, 1);
}