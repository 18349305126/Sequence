#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<fstream>

class Sequence
{
public:
	Sequence(string);
	string getFilename();
	void read();
	int length();
	int number(char);

	string longestConsecutive();
//--------------------------------------------------------------------------------------------------------
	string longestRepeated();
	/*步骤：
		  1.设定16种基本case：AA,AG,AC,AT,GA,GC......
		  2.扫描整个数组，每一个fileData[i]分别对应一个基本case，取出相同的case的项
		  3.设置一个int max
		  4.对每一种case，取出所有该case的项，对每一项的索引index开始，计算每一个index项到index+maxlength项的char值之和，将
		    这些和看成一个集合，若该集合中所有元素都不一样，则maxlength不变；若集合中有一样的元素，则将maxlength一直+1，
			直到集合中所有元素都不一样，这时再将maxlength-1,并记录上一次相同的序列*/

	int charExchange(char);
	//将字符转化为一个数字，A,G,C,T分别由一个质数表示（降低错误率）

	bool checkDuplicate(int a[], int n);
	//使用哈希查找判断是否有重复元素

	int longestNum(vector<int> &, int);
private:
	string filename;
	vector<char> fileData;
	int fLength;
	bool ifRead;
	int tempRepeatedIndex;
	int repeatedIndex;
	
};
