void sort(RB& tree, Node* node);
RB* concat (RB& tree1, RB& tree2);
void merge(RB& tree1, RB& tree2);
RB* change (RB &tree1, RB& tree2, int p);

RB* concat (RB& tree1, RB& tree2)
{
  tree1.dd();
  tree2.dd();

  vector<int> result;
  vector<int>::iterator x1 = vec1.begin();
  vector<int>::iterator x2 = vec2.begin();

  while (x1 != vec1.end() || x2 != vec2.end()){
    if (x1 != vec1.end() && x2 != vec2.end()){
      if (*x1 <= *x2){
	result.push_back(*x1);
	seq.push_back(seq1[x1 - vec1.begin()]);
	++x1;
      }else{
	result.push_back(*x2);
	seq.push_back(seq2[x2 - vec2.begin()] + seq1.size());
	++x2;
      }
    }else if(x1 != vec1.end()){ // случай когда второй вектор закончился
      result.push_back(*x1);
      seq.push_back(seq1[x1 - vec1.begin()]);
      ++x1;
    }else{ // случай когда первый вектор закончился
      result.push_back(*x2);
      seq.push_back(seq2[x2 - vec2.begin()] + seq1.size());
      ++x2;
    }
  }

  RB *new_tree = new RB();
  
}

void merge(RB& tree1, RB& tree2)
{
  concat(tree1, tree2);
  tree1.sequence = 0;
  tree1.sequence_end = 0;
  sort(tree1, tree1.root);
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
