#include "Sequence.h"
#include<string>
Sequence::Sequence(string fn)
{
	filename = fn;
	ifRead = false;
	tempRepeatedIndex = 0;
	repeatedIndex = 0;
	fileData.reserve(1300000);
}

string Sequence::getFilename()
{
	return filename;
}

void Sequence::read()
{
	/*cout << "please input the file address: ";
	string fileAddress;
	cin >> fileAddress;*/
	string fileAddress = "/data/dna.txt";
	ifstream input(fileAddress, ios::in);
	int count = 0;
	if (!input)
	{
		cerr << "the file cannot be opened";
		exit(EXIT_FAILURE);
	}
	char temp;
	while (!input.eof())
	{
		input >> temp;
		if (temp!='/n')
		{
			fileData.push_back(temp);
			count++;
		}
	}
	fLength = count - 1;
	ifRead = true;
}

int Sequence::length()
{
	if (!ifRead)read();
	return fLength;
}

int Sequence::number(char base)
{
	int count = 0;
	if (base=='A'||base=='G'||base=='C'||base=='T')
	{
		if (ifRead)
		{
			for (size_t i = 0; i < fLength; i++)
			{
				if (fileData[i] == base)count++;
			}
		}
		else
		{
			/*cout << "please input the file address: ";
			string fileAddress;
			cin >> fileAddress;*/
			string fileAddress = "/data/dna.txt";
			ifstream input(fileAddress, ios::in);
			if (!input)
			{
				cerr << "the file cannot be opened";
				exit(EXIT_FAILURE);
			}
			char temp;
			int fDataCount = 0;
			while (!input.eof())
			{
				input >> temp;
				if (temp == base)count++;
				if (temp != '/t')
				{
					fileData[fDataCount] = temp;
					fDataCount++;
				}
			}
			fLength = fDataCount - 1;
			if (fileData[fLength-1] == fileData[fDataCount-1])count--;
			ifRead = true;
		}
		return count;
	}
	else
	{
		cout << "please input the right letters";
		return -1;
	}
}

string Sequence::longestConsecutive()
{
	int count = 1;
	int maxcount = 1;
	char base;
	if (ifRead)
	{
		for (size_t i = 0; i < fLength; i+=maxcount)
		{
			int j = i;
			while (i+1<fLength&&fileData[i] == fileData[i + 1]) 
			{
				++i;
				++count;
			}
			while (j-1>=0 && fileData[j] == fileData[j - 1])
			{
				--j;
				++count;
			}

			if (count > maxcount )
			{
				maxcount = count;
				base = fileData[i];
			}
			count = 1;
		}
	}
	else
	{
		/*cout << "please input the file address: ";
		string fileAddress;
		cin >> fileAddress;*/
		string fileAddress = "/data/dna.txt";
		ifstream input(fileAddress, ios::in);
		if (!input)
		{
			cerr << "the file cannot be opened";
			exit(EXIT_FAILURE);
		}

		char prev = 'a';
		char next;
		while (!input.eof())
		{
			input >> next;
			if (next!='/t')
			{
				if (next == prev)count++;
				else
				{
					if (count>maxcount)
					{
						maxcount = count;
						base = prev;
					}
					count = 1;
				}
				prev = next;
			}
		}
	}
	char *a = new char[maxcount + 1];
	for (size_t i = 0; i < maxcount; i++)
	{
		a[i] = base;
	}
	a[maxcount] = '\0';
	string b = a;
	delete[]a;
	return b;
}


int Sequence::charExchange(char a)
{
	int sum = 0;
	switch (a)
	{
	case 'A':
		sum = 3;
		break;
	case 'G':
		sum = 19 ;
		break;
	case 'T':
		sum =  79 ;
		break;
	case 'C':
		sum =  233;
		break;
	default:
		break;
	}
	return sum;
}


//使用哈希查找判断是否有重复元素------------------------------------------------------------------
bool Sequence::checkDuplicate(int a[], int n)
{
	vector<int> hashTable(10000);
	for (size_t i = 0; i < hashTable.size(); i++)
	{
		hashTable[i] = 0;
	}
	for (size_t i = 0; i < n; i++)
	{
		if (a[i]>=hashTable.size())
		{
			for (size_t j = hashTable.size(); j <= a[i]; j++)
			{
				hashTable.push_back(0);
			}
		}
		++hashTable[a[i]];
		if (hashTable[a[i]] == 2)
		{
			tempRepeatedIndex = i;
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------------------------------

int Sequence::longestNum(vector<int>& v, int max)
{
	int *sums = new int[v.size()];
	for (size_t j = 0; j < v.size(); j++)
	{
		int sum = 0;
		for (size_t k = 0; k < max; k++)
		{
			if(v[j]+k<fLength)
			sum = sum + charExchange(fileData[v[j] + k])*(k + 1);
		}
		sums[j] = sum;
	}
	
	if (checkDuplicate(sums, v.size()))
	{
		int i = 0;
		while (checkDuplicate(sums, v.size()))
		{
			repeatedIndex = v[tempRepeatedIndex];
			++i;
			for (size_t j = 0; j < v.size(); j++)
			{
				if(v[j]+max+i-1<fLength)
				sums[j] = sums[j] + charExchange(fileData[v[j] + max + i - 1])*(max + i);
			}
		}
		delete[]sums;
		return (i + max - 1);
	}
	else 
	{
		delete[]sums;
		return max;
	}
}

string Sequence::longestRepeated()
{
	if (!ifRead)read();
	vector<int> AAindex;
	vector<int> AGindex;
	vector<int> ACindex;
	vector<int> ATindex;
	vector<int> GAindex;
	vector<int> GGindex;
	vector<int> GCindex;
	vector<int> GTindex;
	vector<int> CAindex;
	vector<int> CGindex;
	vector<int> CCindex;
	vector<int> CTindex;
	vector<int> TAindex;
	vector<int> TGindex;
	vector<int> TCindex;
	vector<int> TTindex;

	for (size_t i = 0; i < fLength - 1; i++)
	{
		if (fileData[i] == 'A'&&fileData[i + 1] == 'A')AAindex.push_back(i);
		else if (fileData[i] == 'A'&&fileData[i + 1] == 'G')AGindex.push_back(i);
		else if (fileData[i] == 'A'&&fileData[i + 1] == 'C')ACindex.push_back(i);
		else if (fileData[i] == 'A'&&fileData[i + 1] == 'T')ATindex.push_back(i);
		else if (fileData[i] == 'C'&&fileData[i + 1] == 'A')CAindex.push_back(i);
		else if (fileData[i] == 'C'&&fileData[i + 1] == 'C')CCindex.push_back(i);
		else if (fileData[i] == 'C'&&fileData[i + 1] == 'G')CGindex.push_back(i);
		else if (fileData[i] == 'C'&&fileData[i + 1] == 'T')CTindex.push_back(i);
		else if (fileData[i] == 'G'&&fileData[i + 1] == 'A')GAindex.push_back(i);
		else if (fileData[i] == 'G'&&fileData[i + 1] == 'C')GCindex.push_back(i);
		else if (fileData[i] == 'G'&&fileData[i + 1] == 'G')GGindex.push_back(i);
		else if (fileData[i] == 'G'&&fileData[i + 1] == 'T')GTindex.push_back(i);
		else if (fileData[i] == 'T'&&fileData[i + 1] == 'A')TAindex.push_back(i);
		else if (fileData[i] == 'T'&&fileData[i + 1] == 'G')TGindex.push_back(i);
		else if (fileData[i] == 'T'&&fileData[i + 1] == 'C')TCindex.push_back(i);
		else if (fileData[i] == 'T'&&fileData[i + 1] == 'T')TTindex.push_back(i);
	}

	int max = 3;
	max = longestNum(AAindex, max);
	max = longestNum(AGindex, max);
	max = longestNum(ACindex, max);
	max = longestNum(ATindex, max);
	max = longestNum(GAindex, max);
	max = longestNum(GGindex, max);
	max = longestNum(GCindex, max);
	max = longestNum(GTindex, max);
	max = longestNum(CAindex, max);
	max = longestNum(CGindex, max);
	max = longestNum(CCindex, max);
	max = longestNum(CTindex, max);
	max = longestNum(TAindex, max);
	max = longestNum(TGindex, max);
	max = longestNum(TCindex, max);
	max = longestNum(TTindex, max);

	char *a = new char[max+1];
	for (size_t i = 0; i < max; i++)
	{
		a[i] = fileData[i+repeatedIndex];
	}
	a[max] = '\0';
	string b = a;
	delete[]a;
	return b;
}
