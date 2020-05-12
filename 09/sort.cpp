#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;
size_t mem_size = 1000;

void sort_file(){

	ifstream file;
	file.open("file.txt", ios::binary | ios::in);
	vector<string> names;
	int k = 0;
	while(!file.eof()) {
		uint64_t *buffer = new uint64_t[mem_size];
		file.read(reinterpret_cast<char *>(buffer), mem_size * sizeof(uint64_t));
		auto size_read = file.gcount();

		if(size_read>0){
			names.push_back(to_string(k));
			k++;
			names.push_back(to_string(k));
			k++;

			size_t buffer_size = file.gcount() / sizeof(uint64_t);

			thread thread1([buffer, buffer_size]()
			{
				sort(buffer, buffer + buffer_size / (2 ));
			});

			thread thread2([buffer, buffer_size]()
			{
				sort(buffer + buffer_size / (2), buffer + buffer_size);
			});

			thread1.join();
			thread2.join();
			ofstream cur_file;
			cur_file.open(names[k - 1],ios::binary| ios::out);
			for (size_t i = 0; i < buffer_size / (2); i++) {
				cur_file.write((char *)(&buffer[i]), sizeof(uint64_t));
			}

			cur_file.close();
			ofstream cur_file4;
			cur_file4.open(names[k - 2],ios::binary| ios::out);
			for (size_t i = buffer_size / 2; i < buffer_size ; i++)  {
				cur_file4.write((char *)(&buffer[i]), sizeof(uint64_t));
			}
			cur_file4.close();
		}
		delete[] buffer;
	}
	
	for(int i = 1; i < k; i++){
		int s = 1;
		uint64_t *num = new uint64_t[s];
		uint64_t *buffer1 = new uint64_t[mem_size/2];
		ifstream cur_file1;
		cur_file1.open(names[i],ios::binary| ios::in);
		cur_file1.read(reinterpret_cast<char *>(buffer1), mem_size/2 * sizeof(uint64_t));
		auto size_read = cur_file1.gcount()/ sizeof(uint64_t);
		cur_file1.close();
		ifstream cur_file2;
		cur_file2.open(names[i-1],ios::binary| ios::in);
		cur_file2.read(reinterpret_cast<char *>(num), s*sizeof(uint64_t));
		size_t j = 0;

		if(i == k - 1){
			names[i] = "output.txt";
		}
		ofstream f_res(names[i], ios::binary| ios::out);

		while(!cur_file2.eof() && j<size_read){
			if (num[0]<=buffer1[j]){
				f_res.write((char *)(&num[0]), sizeof(uint64_t));
				cur_file2.read(reinterpret_cast<char *>(&num[0]), sizeof(uint64_t));
			} else{
				f_res.write((char *)(&buffer1[j]), sizeof(uint64_t));
				j++;
			}
		}
		if(cur_file2.eof()){
			f_res.write(reinterpret_cast<const char *>(&buffer1[j]), sizeof(uint64_t) * (mem_size/2 - j));
		}
		if(!cur_file2.eof()){
			f_res.write((char *)(&num[0]), sizeof(uint64_t));
		}
		while (!cur_file2.eof()) {
			auto *n = new uint64_t;
			cur_file2.read(reinterpret_cast<char *>(n), sizeof(uint64_t));
		}
		cur_file2.close();
		f_res.close();
		if(i == k - 1){
			names[i] = to_string(k - 1);
		}
		delete[] buffer1;
	}
	for_each(names.begin(), names.end() , [](string & name) { remove(name.c_str());});

}





int main(){
	ofstream file("file.txt", ios::binary | ios::out);
	for (int i = 0; i < 100000; ++i) {
		auto *n = new uint64_t(std::rand() % 100000);
		file.write(reinterpret_cast<char *>(n), sizeof(uint64_t));
		cout<<*n<<' ';
	}
	file.close();
	sort_file();
	ifstream file1;
	printf("\nresult:\n");
	file1.open("output.txt",ios::binary | ios::in);
	
	while (!file1.eof()) {
		uint64_t n;
		file1.read(reinterpret_cast<char *>(&n), sizeof(uint64_t));
		cout << n << ' ';
	}
	return 0;
}