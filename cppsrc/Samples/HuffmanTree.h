#pragma once
 #include "Node.h"
 #include "FrequencyTable.h"
 #include "BitStream.h"
 #include <string>
 #include"PriorityQueue.h"


 class HuffmanTree{

  private:

    Node<int>* root;//root of tree
    int treeSize;//num of bits written writing tree.
    int codeSize;//num of bits written when writing huffCode;
    int freq;
    int numChar = 0;
    int ctr = 0;
    string ext;

    //helper functions
    //Description: This function read the frequency table
    bool nodeBuilder (const std::string& aFile,PriorityQueue<Node<int>*>& p_queue ){

      //build Frequency table
      FrequencyTable charFreq;
      bool result = charFreq.setFrequency(aFile);
      if(result){
        freq = charFreq.getCharSize();

        // get frequency and build the nodes.
        for(int i =0; i<256; i++){
          int aFreq = charFreq.getFrequency(i);
          if(aFreq> 0 ){
            numChar += 1;
            Node<int>* node = new Node<int>(aFreq,static_cast<unsigned char>(i));
            p_queue.enqueue(node);

          }
        }
      }
      return result;
    }

    // getfile extension
    string getFileExt(const string& s) {

       size_t i = s.rfind('.', s.length());
       if (i != string::npos) {
          return(s.substr(i+1, s.length() - i));
       }

       return("");
    }
    //Description: This function build Huffman Tree.
    bool buildTree(const std::string& aFile){
      ext = getFileExt(aFile);
      PriorityQueue<Node<int>*> p_queue = PriorityQueue<Node<int>*>();
      bool result = this->nodeBuilder(aFile,p_queue);

      if(result){
        //keep building tree using two nodes with smallest frequency.
        Node<int>* node1;
        Node<int>*node2;

        while(!p_queue.isEmpty()){

          node1 = p_queue.peek();
          p_queue.dequeue();

          if(p_queue.isEmpty()){
            root = node1;
          }else{

            node2 = p_queue.peek();
            p_queue.dequeue();
            Node<int>* newNode = new Node<int>();
            newNode->right = node1;
            newNode->left = node2;
            newNode->Frequency = node1->Frequency+node2->Frequency;
            p_queue.enqueue(newNode);

          }
        }
      }
      return result;
  }

    //Description: This function recursively traverse a tree and creates the codes for each character and
    //             and store it in string array
    void huffCode(Node<int>* root,string str, string arr[]){
      if(root) //if the node is not null
      {
          //compare char of the leaf node and the given char
          if(!root->left && !root->right)
          {
              unsigned int index = root->aChar;
              arr[index]=str;
          }
          else
          {
              //continue to search if the same char still not found
              huffCode(root->left,str+"0",arr);
              huffCode(root->right, str+"1",arr);
          }
      }
    }

    //Description: This function the write huffman Code for each char from srcFile to destFile.
    void writeCode(const std::string& srcFile, BitStream& outFile, string codeTable[]){

      // BitStream outFile = BitStream(destFile);
      fstream inFile;
      inFile.open(srcFile, istream::in|ios::binary);
      if (inFile.is_open()){
        outFile.OpenToWrite();
        unsigned char ch2;
        unsigned char ch;
        char c;

        while(inFile.get(c)){
          ch=c;
          //send the Huffman string to output file bit by bit
          for(unsigned int i=0;i<codeTable[ch].size();i++)
          {
              if(codeTable[ch].at(i)=='0')
                  ch2=0;
              if(codeTable[ch].at(i)=='1')
                  ch2=1;
              outFile.writeBits(ch2);
          }
        }
        outFile.flushWrite();
        codeSize = outFile.getCharSize();

        inFile.close();
        outFile.closeFile();
        cout<<"size of code is :"<<this->codeSize<<endl;
      }

    }

    //Description: This function traverse tree and write 0 for non leaf branch and 1 for leaf brach following by 8-bits char.
    //pre:         outfile is already open.
    void treeToFile(Node<int>* tree,BitStream& outfile){
      if(tree){
        if(!tree->left &&!tree->right){

          outfile.writeBits(1);
          outfile.writeBytes(tree->aChar);
        }else{

          outfile.writeBits(0);
          treeToFile(tree->left,outfile);
          treeToFile(tree->right,outfile);

        }
      }
    }


    //Description: This function write tree structure to file. It writes 0 bit for none leaf and when it reaches a leaf
    void writeTree(BitStream& outfile){
      // outfile.OpenToWrite();

      if (outfile.OpenToWriteFirst(numChar,freq,ext)){
        // treeSize += outfile.getCharSize();
        if(root){

          this->treeToFile(root,outfile);
        }
        outfile.flushWrite();
        treeSize += outfile.getCharSize();
        outfile.closeFile();
        // cout<<"size of tree is : "<< this->treeSize<<endl;
      }

    }

    //Description: This function read tree from file and construct the huffman tree.
    Node<int>* treeFromFile(BitStream& infile ){
        if (ctr ==numChar){
          return NULL;
        }else{
          if (infile.readBits() == 1)
          {
              // cout<<"char = "<<infile.readBytes()<<endl;
              this->ctr+=1;
              return (new Node<int>(0,infile.readBytes()));

          }else{
            Node<int>* leftChild = treeFromFile(infile);
            Node<int>* rightChild = treeFromFile(infile);
            Node<int>* node = new Node<int>(0,0);
            node->left = leftChild;
            node->right = rightChild;
            return node;
          }
        }
    }


    //Description: This function traverse the tree using huff code and write the chars to destination file as uncompreesed form.
    //Pre:         infile and outfile are already opened.
    void findChar(BitStream& inFile,fstream& outFile){
      Node<int>* nodeTracker = root;
      bool charFound =false;
      int i = freq-1;
      while (i >= 0){
    // for(int i = 0 ; i < 30; i++){

        //if char found go to root
        if(charFound){
          nodeTracker = root;
          charFound = false;

        }
        unsigned char bits = inFile.readBits();

        //if 0 go left if 1 go right
        if(bits ==0){
          nodeTracker = nodeTracker->left;
        }else if(bits ==1){
          nodeTracker = nodeTracker->right;
        }

        //if leaf node is reached write the char to desitination file.
        if(!nodeTracker->left && !nodeTracker->right){
          outFile.put(static_cast<char>(nodeTracker->aChar));
          charFound = true;
          i--;
          //cout<< static_cast<char>(nodeTracker->aChar);
        }
      }
    }


  public:

//--------------------------------------------------------------------------------------

    //Main functions
    //Description: Constructor. Root of tree = NULL, treeSize and CodeSize = 0
    HuffmanTree();

    //Description: Parametarized constructor
    HuffmanTree(Node<int>* root);

    //Descpription: Return the pointer to root node of the tree
    Node<int>* getRoot();

    string getExt();

    //Des: return the size of compressed file.
    int getSizeCompressed();

    //Des: return the size of sourcefile;
    int getSizeSource();

    //Description: This function decompress the file by building huffman tree from compressed file

    bool decompress(const std::string& srcFile,const std::string& destFile);

    //Description: This function compress the file by reading chars from srcFile and write to destFile.
    bool compress(const std::string& srcFile, const std::string& destFile);
 };
