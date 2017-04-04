// функции для сортировки слиянием
void merge_sort(Node **h);
void split_half(Node *head, Node **a, Node **b);
Node* merge_two_sorted_lists(Node *a, Node *b);

void merge_sort(Node **h) // сортировка слиянием
{
  Node *head = *h,*a,*b;

  if ( head == NULL || head->s_next == 0 )
    return;

  split_half(head, &a, &b);

  merge_sort(&a);
  merge_sort(&b);
  
  *h = merge_two_sorted_lists(a, b);
}

void split_half(Node *head, Node **a, Node **b) // разбивка списка на две половины
{
  Node* fast;
  Node* slow;
  if ( head == 0 || head->s_next == 0) {
    *a = head;
    *b = 0;
  } else {
    slow = head;
    fast = head->s_next;
 
    while(fast != 0) {
      fast = fast->s_next;
      if(fast != 0) {
        slow = slow->s_next;
        fast = fast->s_next;
      }
    } 
    *a = head;
    *b = slow->s_next;
    (*b)->s_prev = 0;
    slow->s_next = 0;
  }
}

Node* merge_two_sorted_lists(Node *a, Node *b) // совмещает два отсортированных списка
{
  Node *result = 0;

  if (a == 0)
    return b;
  else if (b == 0)
    return a;

  if (a->key <= b->key) {
    result = a;
    result->s_next = merge_two_sorted_lists(a->s_next, b);
    if ( result->s_next != 0 ) (result->s_next)->s_prev = result;
  } else {
    result = b;
    result->s_next = merge_two_sorted_lists(a, b->s_next);
    if ( result->s_next != 0 ) (result->s_next)->s_prev = result;
  }
  return result;
}


