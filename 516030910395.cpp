#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Suffix {
public:
	string suf;
	int times;
};

int main() {
	int num;  //length of suffix
	cout << "Input interger:";
	cin >> num;
	map<string, int> suffixmap;
	char buffer[256];
	fstream out;
	out.open("dictionary.txt", ios::in);
	
	while (!out.eof()) {
		out.getline(buffer, 256,'\n');
		string word = buffer;
		string suf= "";
		if (word.length() >= num) {
			for (int i = word.length() - num; i < word.length(); i++) 	suf += word[i];
			if (suffixmap[suf] == 0) {
				suffixmap[suf] = 1;	
			}
			else {
				suffixmap[suf] += 1;
			}
		}
	}
	out.close();
	//sort suffixmap[suf] value
	vector<Suffix> v_suf;
	//int count = 0;
	map<string, int>::iterator iter;
	for (iter = suffixmap.begin(); iter != suffixmap.end(); ++iter)
	{
		Suffix suff;
		suff.suf = iter->first;
		suff.times = iter->second;
		if (iter == suffixmap.begin()) v_suf.push_back(suff);
		else {
			vector<Suffix>::iterator viter;
			for (viter = v_suf.begin();viter!=v_suf.end();viter++)
			{
				//count++;
				//if (count > 10) break;
				if (suff.times > viter->times) {
					v_suf.insert(viter,suff);
					break;
				}
				else if (viter == v_suf.end()) v_suf.push_back(suff);
			}
		}
	}
	cout << "Top 10:" << endl;
	for (int i = 0; i != 10; i++) {
		cout << v_suf[i].suf << ":" << v_suf[i].times << endl;
	}

	cout << "Input a suffix given:";
	string searchsuffix;
	cin >> searchsuffix;
	out.open("Document.txt", ios::in);
	vector<string> v_search;
	while (!out.eof()) {
		out.getline(buffer, 256, '\n');
		string word = buffer;
		if (word.length()>num && word.substr(word.length() - num,num) == searchsuffix) {
			v_search.push_back(word);
		}
	}
	out.close();
	vector<string>::iterator viter;
	for (int i = 0; i < v_search.size();i++)
	{
		cout << v_search[i] << endl;
	}
	cin.get();

	return 0;
}