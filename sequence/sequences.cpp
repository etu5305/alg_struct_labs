void sort(RB& tree, Node* node);
RB* concat (RB& tree1, RB& tree2);
RB* merge(RB& tree1, RB& tree2);
RB* change (RB &tree1, RB& tree2, int p);

RB* concat (RB& tree1, RB& tree2)
{
  std::vector<int> seq1,seq2,seq,vec1,vec2,result;
  
  tree1.get_vec(tree1.root, vec1, seq1);
  tree2.get_vec(tree2.root, vec2, seq2);

  std::vector<int>::iterator x1 = vec1.begin();
  std::vector<int>::iterator x2 = vec2.begin();

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

  RB *new_tree = new RB(tree1.name, result, seq);
  return new_tree;
}

void sort(RB& tree, Node* node)
{
  if (tree.root == node) {
	tree.sequence.clear();
	tree.count = 0;
  }
  
  if (node == 0)
  	return;

  sort(tree, node->left);
  
  tree.sequence.push_back(node);
  node->number = tree.count++;

  sort(tree, node->right);
}

RB* merge(RB& tree1, RB& tree2)
{
  RB *tree3 =  concat(tree1, tree2);
  // tree1.sequence = 0;
  // tree1.sequence_end = 0;
  sort(*tree3, tree3->root);
  return tree3;
}

RB* change (RB &tree1, RB& tree2, int p)
{
  // Node *head1 = tree1.sequence, *head2 = tree2.sequence;
  // RB *tree3 = new RB(tree1.name);
  // int key;

  // if (p >= tree1.count && head1 == 0)
  //   return tree3;
  
  // for (int i = 0; ; i++) {
  //   if (i < p && head1 != 0){
  //     key = head1->key;
  //     head1 = head1->s_next;
  //   }else if (i >=p && head2 != 0) {
  //     key = head2->key;
  //     head2 = head2->s_next;
  //     if (head1 !=0)
  // 	head1 = head1->s_next;
  //   }else if (head1 != 0) {
  //     key = head1->key;
  //     head1 = head1->s_next;
  //   }else
  //     return tree3;

  //   tree3->insert(key);
  // }
  // return tree3;
}
