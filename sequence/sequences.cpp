void sort(RB& tree, Node* node);
void concat (RB& tree1, RB& tree2);
void merge(RB& tree1, RB& tree2);
RB* change (RB &tree1, RB& tree2, int p);

void concat (RB& tree1, RB& tree2)
{
  Node* item = tree2.sequence;

  while (item != 0) {
        tree1.insert(item->key);
	item = item->s_next;
  }
}

void sort(RB& tree, Node* node)
{
  if (node == 0)
	return;

  sort(tree, node->left);

  if (tree.sequence_end == 0)
	tree.sequence = node;
  else
	tree.sequence_end->s_next = node;

  node->s_next = 0;
  node->s_prev = tree.sequence_end;
  tree.sequence_end = node;

  sort(tree, node->right);
}

void merge(RB& tree1, RB& tree2)
{
  concat(tree1, tree2);
  tree1.sequence = 0;
  tree1.sequence_end = 0;
  sort(tree1, tree1.root);
}


RB* change (RB &tree1, RB& tree2, int p)
{
  Node *head1 = tree1.sequence, *head2 = tree2.sequence;
  RB *tree3 = new RB(tree1.name);
  int key;

  if (p >= tree1.count && head1 == 0)
    return tree3;
  
  for (int i = 0; ; i++) {
    if (i < p && head1 != 0){
      key = head1->key;
      head1 = head1->s_next;
    }else if (i >=p && head2 != 0) {
      key = head2->key;
      head2 = head2->s_next;
      if (head1 !=0)
	head1 = head1->s_next;
    }else if (head1 != 0) {
      key = head1->key;
      head1 = head1->s_next;
    }else
      return tree3;

    tree3->insert(key);
  }
  return tree3;
}
