cout  << "|" << groot->treeName << "|" << endl;
  output << "|" << groot->treeName << "|" << endl; //output
  inorderTraversalPrintItem(groot->theTree,output); // visit sub tree
  cout << endl;
  output << endl;