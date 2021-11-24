#include "push_swap.h"

void sort_under_20_B(Stack *a, Stack *b, int cnt, Pushswap *p)
{
    int pivot;
	int num;
	int cnt_pa;
	int cnt_rb;
	int part;
	int i;
	ListNode *ptr;

    num = cnt;
    
    if (check_reverse_sorted(b, cnt) == TRUE)
    {   
        while (num != 0)
        {
            pa(a, b);
            p->count++;
            num--;
        }
        return ;
    }
    
	if (cnt < 4){
		sort_under_4_B(a, b, cnt, p);
		return ;
	}
	cnt_pa = 0;
	cnt_rb = 0;
	i = 0;
	pivot = get_middle_pivot(b, cnt);
	part = TRUE;
	if (size(*b) == cnt)
		part = FALSE;
    while (num != 0)
	{
		ptr = b->head;
		{
			if (ft_atoi(ptr->data) > pivot) // 2n + 1 일때 n + 1개, 2n일때 n개 
			{
				pa(a, b);
				cnt_pa++;
				p->count++;
			}
			else
			{
                if ((cnt_pa == (cnt - (int)(cnt/2) - 1)) && (ft_atoi(ptr->prev->data) > pivot))
                {
                    sb(a, 0);
                    pa(a, b);
                    cnt_pa++;
                    p->count += 2;
                } 
                else
                {
				    rb(b, 0);
				    cnt_rb++;
				    p->count++;
                }
			}
			if (cnt_pa == (int)(cnt/2))
				break;
			num--;
		}
	}
    if (part == TRUE)
	{
		while (i < cnt_rb)
		{
			rrb(b, 0);
			p->count++;
			i++;
		}
	}
	sort_under_20_A(a, b, cnt_pa, p);
	sort_under_20_B(a, b, cnt - cnt_pa, p);   
}


// 완료인거 쪼개기전 (참고용)
void sort_under_20_A(Stack *a, Stack *b, int cnt, Pushswap *p){
    
    int pivot;
    int num;
    int cnt_pb;
    int cnt_ra;
    ListNode *ptr;
    cnt_pb = 0;
    cnt_ra = 0;
    pivot = get_middle_pivot(a, cnt);
    num = cnt;
	int part;
	
	//정렬이 된 숫자가 들어왔을 때.
    if (check_sorted(a, cnt))
        return ;
	//4개보다 작은 경우. 3개 2개인 경우에 비효율적이라서 최적화하기 위함.
	if (cnt < 4)
	{
		sort_under_4_A(a, b, cnt, p);
		return ;
	}

	//process_a_to_b_one부분
    while (num != 0){
        ptr = a->head;
		//process_main_a_to_b_one_pivot
        //피봇보다 작은경우. pb(a->b)로 옮김.
		if (ft_atoi(ptr->data) < pivot) // 지금 n, n+1 개씩 먹음 
        {
            pb(a, b);
            cnt_pb++;
            p->count++;
        }
		//ptr->data > pivot 피봇보다 값이 큰 경우 a에 값이 있다.
        else
        {
            //???????????cnt_pb == (cnt - (int)(cnt/2) - 1)이 조건이 뭐지????????????
			//절반정도가 b에 있으면서 이게 피봇보다 바로 작은 값인건가?
			//a랑 맨 위를 바꿔주고 a->b로 옮김.
			//b에 절반정도가 있고 pivot값보다 작다면, 피봇이 a탑에 있는데, 그 다음값이 pivot보다 작으면?
			//피봇을 a뒤로 보내고 그 다음 값을 b로 보낸다.
			if ((cnt_pb == (cnt - (int)(cnt/2) - 1)) && (ft_atoi(ptr->prev->data) < pivot))
            {
                sa(a, 0);
                pb(a, b);
                cnt_pb++;
                p->count += 2;
            } 
			//단순히 pivot보다 값이 큰 경우 a의 뒤로 넘겨준다.
            else
            {
                ra(a, 0);
                cnt_ra++;
                p->count++;
            }
        }
		if (cnt_pb == (int)(cnt/2)) // ra를 더돌리지 않을 것 
			break;
        num--;
    }


	//check_partition
    int i;
    i = 0;
	part = TRUE;
	if (size(*a) == cnt)
		part = FALSE;
	if (part == TRUE) // rra가 의미있고 (전체가 아니라 부분), 
    {
    	while (i < cnt_ra)
		{
        	rra(a, 0);
        	p->count++;
        	i++;
    	}
	}


    sort_under_20_A(a, b, cnt - cnt_pb, p);// 여기에는 a스택에 있는 전체 element가 들어가야함 
    b_to_a(a, b, cnt_pb, p);
    //sort_under_20_B(a, b, cnt_pb, p);
}