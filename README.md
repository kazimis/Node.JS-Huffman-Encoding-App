## Purpose

The purpose of this project is to understand the importance of interaction of different programming language in developing large application. This application is a compresser app based on huffman encoding. The overall hope of this app is to be able to compress any file format. The memory effeciency of this encoding depends on the distribution of characters in file. 

## Languages used
C++, Javascript and python is used for this application. C++ is used for Huffman encoding to acknowledge the fact that we need to use effecient programming language when huge CPU power is needed. Javascript is used to do the front end work and Nodejs is used to do the back-end work. I also incorporated python too. In this python is used to hash password. Though I did not used this password in my app, using python is to acknowledge the significance of [numpy] and [pandas] library which very effective in data analysis. The password hash can be used in future of work for this app if we need to add sigin functionality. 

## Communication method
I use two communication methods function call and running language as executable file. In function call I used [Napi] to add [C++] addon in [Nodejs]. The second method that I used is calling [python] script from [Nodejs] child process. 

## How to run this App
```python
vagrant up
vagrant provision
vagrant ssh
cd project
node app.js
```


