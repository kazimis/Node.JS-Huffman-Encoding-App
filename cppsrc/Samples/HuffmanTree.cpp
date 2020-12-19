/*HuffmanTree.cpp
*/
#include"HuffmanTree.h"

//Description: Constructor. Root of tree = NULL, treeSize and CodeSize = 0
HuffmanTree::HuffmanTree():root(NULL),
                          treeSize(0),
                          codeSize(0),
                          freq(0),
                          numChar(0),
                          ctr(0){
}

//Description: Parametarized constructor
HuffmanTree::HuffmanTree(Node<int>* aRoot):root(aRoot){
}

//Des: return the size of compressed file.
int HuffmanTree::getSizeCompressed(){

  return (treeSize+codeSize)/8;
}

int HuffmanTree::getSizeSource(){
  return freq;
}

string HuffmanTree :: getExt(){
  return ext;
}
//Descpription: Return the pointer to root node of the tree
Node<int>* HuffmanTree::getRoot(){
  return root;
}

//Description: This function decompress the file by building huffman tree from compressed file
bool HuffmanTree::decompress(const std::string& srcFile, const std::string& destFile){

  //open the srcFile to read and destFile to write
  BitStream inFile = BitStream(srcFile);
  int a = 0;
  int b = 0;
  string str;
  if(!inFile.OpenToReadFirst(&a, &b, &str)){
    return false;
  }
  fstream outFile;
  cout<<"file name : = "<<destFile+str<<endl;
  outFile.open(destFile+str, ios::out|ios::binary);
  numChar = a;
  freq = b;
  ext = str;
  //reconstruct tree
  inFile.readBits();
  root = new Node<int>(0,0);
  root ->left =  treeFromFile(inFile);
  root->right = treeFromFile(inFile);
  inFile.flushRead();
  this->findChar(inFile,outFile);
  return true;
}

//Description: This function compress the file by reading chars from srcFile and write to destFile.
bool HuffmanTree::compress(const std::string& srcFile, const std::string& destFile){
  //build the tree
  bool result = this->buildTree(srcFile);
  if (result){
    BitStream outfile = BitStream(destFile);
    //Write the tree to destination file.
    this->writeTree(outfile);
    string codeTable[256];

    //build the huff code
    this->huffCode(root,"",codeTable);

    //write the huffCode.
    this->writeCode(srcFile, outfile,codeTable);
  }
  return result;
}
