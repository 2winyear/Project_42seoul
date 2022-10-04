#include <unistd.h>

void forward_solution(char *msg) {
  if (*msg == 0) return;
  write(1, msg, 1);
  forward_solution(msg + 1);
}