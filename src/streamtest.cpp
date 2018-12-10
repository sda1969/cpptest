/*
 * streamtest.cpp
 *
 *  Created on: 26 июн. 2017 г.
 *      Author: user
 */

#include <iostream>
#include <fstream>
#include <memory>

/*
ios::in	Open for input operations.
ios::out	Open for output operations.
ios::binary	Open in binary mode.
ios::ate	Set the initial position at the end of the file.
If this flag is not set, the initial position is the beginning of the file.
ios::app	All output operations are performed at the end of the file, appending the content to the current content of the file.
ios::trunc	If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.
*/

namespace streams {

using namespace std;

void filestest(){

	//Текстовые файлы

	fstream mfile("test01.txt", ios::out | ios::app);

	if(mfile.is_open()){
		mfile << "new line \n";
		mfile.close();
	}
	else {
		cout << "Unable to open file";
	}

	mfile.open("test01.txt", ios::in);
	string line;
	if(mfile.is_open()){
		while(getline(mfile, line)){  //строка до перевода строки
//		while( mfile >> line){ 		  //разбивает на слова
			if (mfile.good()){
				cout << line << endl; // getline возвращает строку без перевода строки
			}
		}
		if ( mfile.eof()){
			cout << "end of file" << endl;
		}

		mfile.close();
	}

	// Бинарные файлы

	//подсчет размера файла в байтах
	  streampos begin,end;
	  mfile.open("test01.txt",ios::in | ios::binary);
	  begin = mfile.tellg();
	  mfile.seekg (0, ios::end);
	  end = mfile.tellg();
	  mfile.close();
	  cout << "size is: " << (end-begin) << " bytes.\n";
	  cout << end << endl;

	  fstream mbfile ("test01.txt", ios::in|ios::binary|ios::ate);
	  if(mbfile.is_open()){
		  int size = mbfile.tellg();
		  shared_ptr<char> memblock (new char [size], default_delete<char[]>());
		  //shared_ptr<char> memblock (new char [size], [](char*p){delete[] p;}); //the same as above
		  //unique_ptr<char> memblock (new char [size]); // deleter is not required
		  mbfile.seekg (0, ios::beg);
		  mbfile.read (memblock.get(), size);
		  mbfile.close();
		  //hexdump(memblock, size);
	  }

}

void streamstest_run(){
	filestest();
}

}
