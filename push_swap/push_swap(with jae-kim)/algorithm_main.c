#include "push_swap.h"

void b_to_a(Stack *a, Stack *b, int cnt);

void sort_under_6_A(Stack *a, Stack *b, int cnt){
  if (cnt < 2)
    return ;
  
  a_top = atoi(a->head->data);
  a_second = atoi(a->head->prev->data);
  
  int min = a_top;
  int tmp_cnt = 0;
  while (cnt != 0){
    a->head = a->head->prev;
    a_top = atoi(a->head->data);
    if (a_top < min){
      min = a->top;
      tmp_cnt++;
    }
    cnt--;
  }
}

void a_to_b(Stack *a, Stack *b, int cnt){
  int pivot_index_big;
  int pivot_index_small;
  int a_top;
  int a_second;
  int cnt_pb;
  int cnt_ra;
  int cnt_rb;

  cnt_pb = 0;
  cnt_ra = 0;
  cnt_rb = 0;

  //printf("count : %d\n", cnt);
  
  if (a->head->data == NULL)
    return ;

  if (a == NULL || b == NULL|| cnt < 2)
      return ;
  
  a_top = atoi(a->head->data);
  a_second = atoi(a->head->prev->data);
  
  //printf("check 25\n");

  if (cnt < 6){
    a_top = atoi(a->head->data);
    a_second = atoi(a->head->prev->data);
  if (cnt == 2){
    if (a_top < a_second)
        sa(a);
    return ;
  }
  }
  if (a_top > a_second){
    pivot_index_big = a_top;
    pivot_index_small = a_second;
  }
  else {
    pivot_index_big = a_second;
    pivot_index_small = a_top;
  }

  while(!IsEmpty(*a) && cnt != 0)
  {

    a_top = atoi(a->head->data);
    if (a_top >= pivot_index_big){
      ra(a);
      cnt_ra++;
    }
    else {
      pb(a, b);
      cnt_pb++;
      if (a_top >= pivot_index_small);
      {
        rb(b);
        cnt_rb++;
      }
    }
    cnt--;
  }
  if (size(*a) != cnt_ra){
  if (cnt_ra < cnt_rb){
    for (int i = 0; i < cnt_ra; i++)
      rrr(a, b);
    for (int i = 0; i < cnt_rb - cnt_ra; i++)
      rrb(b);
  }
  else 
  {
    for (int i = 0; i < cnt_rb; i++)
      rrr(a, b);
    for (int i = 0; i < cnt_ra - cnt_rb; i++)
      rra(a);
  }  
  }
  else {
    for (int i = 0; i < cnt_rb; i++)
      rrb(b);
  }
  printf("\n");
  print_stack(a, b);
  printf("\n");
  a_to_b(a, b, cnt_ra);
  b_to_a(a, b, cnt_rb);
  b_to_a(a, b, cnt_pb - cnt_rb);
  printf("\n");
  print_stack(a, b);
  printf("\n");
}

void b_to_a(Stack *a, Stack *b, int cnt){
  int pivot_index_big;
  int pivot_index_small;
  int cnt_pa;
  int cnt_ra;
  int cnt_rb;
  int b_top;
  int b_second;

  cnt_pa = 0;
  cnt_ra = 0;
  cnt_rb = 0;

  if (a == NULL || b == NULL)
      return ;

  if (cnt < 2){
    while (cnt != 0){
      pa(a, b);
      cnt--;
    }
    return ;
  }
  b_top = atoi(b->head->data);
  b_second = atoi(b->head->prev->data);
  if (cnt == 2){
      if (b_top < b_second)
        sb(b);
      pa(a,b);
      pa(a,b);
    return ;
  }
  if (b_top > b_second){
    pivot_index_big = b_top;
    pivot_index_small = b_second;
    //push_head(a, pop_head(b));
  }else {
    pivot_index_big = b_second;
    pivot_index_small = b_top;
  }


  while(!IsEmpty(*b) && cnt != 0)
  {
    b_top = atoi(b->head->data);
    //피봇값을 고정하지 않으려면
    // 피봇값을 따로 변수로 저장 
    // 비교해서 크면 rra 작으면 ra 
  if (b_top < pivot_index_small){
      rb(b);
      cnt_rb++;
    }
    else {
      pa(a, b);
      cnt_pa++;
      if (b_top < pivot_index_big);
      {
        ra(a);
        cnt_ra++;
      }
    }
  cnt--;
  }
  printf("\n");
  print_stack(a, b);
  printf("\n");
  a_to_b(a, b, cnt_pa - cnt_ra);

  if (cnt_rb != size(*b)){
  if (cnt_ra < cnt_rb){
    for (int i = 0; i < cnt_ra; i++)
      rrr(a, b);
    for (int i = 0; i < cnt_rb-cnt_ra; i++)
      rrb(b);
  }
  else 
  {
    for (int i = 0; i < cnt_rb; i++)
      rrr(a, b);
    for (int i = 0; i < cnt_ra-cnt_rb; i++)
      rra(a);
  }  
  }
  else{
    for (int i = 0; i < cnt_ra; i++)
      rra(a);
  }
  a_to_b(a, b, cnt_ra);
  b_to_a(a, b, cnt_rb);

}
#include <stdlib.h>

int main(int argc, char* argv[]){
    Stack *a;
    Stack *b;

    int tmp;

    if (argc <= 1)
    {
      write(1, "Error", sizeof("Error"));
      return 0;
    }
    a = init();
    b = init();

    printf("argc : %d\n", argc);

    for (int i = 1; i < argc; i++){
       push_head(a, argv[i]);
      printf("%s ", argv[i]);
    }
    //printf("%d\n", a->head->next->data);  
    a_to_b(a, b, size(*a));
    print_stack(a, b);

    //exit(0);
    // delete_stack(a);
    // delete_stack(b);
    //system("leaks a.out");

    //메모리 leaks  
   // exit(0);
}