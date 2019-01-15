
#include "MSRCR.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>

using namespace cv;
using namespace std;
extern int readDir(char *dirName, vector<string> &filesName);
struct imfo57_21
{
	string name;
	int objw;
	int objh;
	int width;
	int height;
	float ratiow;
	float ratioh;
};


//升序
bool LessSortw(imfo57_21 a, imfo57_21 b)
{

	return (a.ratiow<b.ratiow);
}
//升序
bool LessSorth(imfo57_21 a, imfo57_21 b)
{
	return (a.ratioh<b.ratioh);
}
int test57_21(int argc, char *argv[])
{



	string imgpath = "E:\\LISA-Traffic-Light\\dayTrainingall\\weight-leak";
	string imgpath1 = "E:\\LISA-Traffic-Light\\dayTrainingall";
	string txtpath = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip\\labels";



	string wtxt = imgpath1 + "\\" + "0_wratio.txt";
	fstream finWrite;
	finWrite.open(wtxt, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string htxt = imgpath1 + "\\" + "0_hratio.txt";
	fstream finWrite2;
	finWrite2.open(htxt, ios::out);
	if (!finWrite2.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}



	map<int, vector<imfo57_21>>mvfo;

	vector<string> v_img_; int num = 0;
	readDir((char*)imgpath.c_str(), v_img_);
	int short_size = 600; int max_long_size = 1000;

	float minw = 10000; float minh = 10000;
	float maxw = 0; float maxh = 0;
	vector<imfo57_21>vfo;
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('\\');
		int npos2 = v_img_[i].find_last_of('.');

		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		cout << name1 << endl;
		int npos3 = name1.find_last_of('-');
		string name2 = name1.substr(0, npos3);

		





		string str = txtpath + "\\" + name2 + ".txt";
		fstream finRead1;
		finRead1.open(str, ios::in);
		if (!finRead1.is_open())
		{
			cout << "finRead3 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line; int num1 = 0;

		while (getline(finRead1, line))
		{

			if (line.empty())
			{
				break;
			}

			num1++;

			int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			int objw = x2 - x1 + 1; int objh = y2 - y1 + 1;

			float objperw = objw*1.0 / img.cols;
			float objperh = objh*1.0 / img.rows;

			imfo57_21 vi;
			vi.name = name1;

			vi.ratiow = objperw;
			vi.ratioh = objperh;
		
			vi.objw = objw;
			vi.objh = objh;

			vi.width = img.cols;
			vi.height = img.rows;
			vfo.push_back(vi);


			if (objperw<minw)
			{
				minw = objperw;
			}
			if (objperh < minh)
			{
				minh = objperh;
			}

			if (objperw>maxw)
			{
				maxw = objperw;
			}
			if (objperh > maxh)
			{
				maxh = objperh;
			}

		}

		finRead1.close();

	}
	printf("perminw=%f,perminh=%f,permaxw=%f,permaxh=%f\n", minw, minh, maxw, maxh);

	sort(vfo.begin(), vfo.end(), LessSortw);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57_21 vi = vfo[j];
		finWrite << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.objw << " " << vi.objh 
			<< " " << vi.width << " " << vi.height << endl;
	}

	finWrite.close();


	sort(vfo.begin(), vfo.end(), LessSorth);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57_21 vi = vfo[j];
		finWrite2 << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.objw << " " << vi.objh 
			<< " " << vi.width << " " << vi.height << endl;
	}

	finWrite2.close();




	return 0;
}

int test57_22(int argc, char *argv[])
{



	string path = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip";
	/*string imgpath1 = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip\\frames-big";
	mkdir(imgpath1.c_str());
	string imgpath2 = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip\\frames-small";
	mkdir(imgpath2.c_str());*/
	//string txtpath = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip\\labels";



	string wtxt = path + "\\" + "0_wratio.txt";
	fstream finWrite;
	finWrite.open(wtxt, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string htxt = path + "\\" + "0_hratio.txt";
	fstream finWrite2;
	finWrite2.open(htxt, ios::out);
	if (!finWrite2.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}



	map<int, vector<imfo57_21>>mvfo;

	vector<string> v_img_; int num = 0;
	string pathimg = path + "\\" + "frames";
	readDir((char*)pathimg.c_str(), v_img_);
	int short_size = 600; int max_long_size = 1000;

	float minw = 10000; float minh = 10000;
	float maxw = 0; float maxh = 0;
	vector<imfo57_21>vfo;
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('\\');
		int npos2 = v_img_[i].find_last_of('.');

		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		cout << name1 << endl;
		






		string str = path+"\\"+"labels" + "\\" + name1 + ".txt";
		fstream finRead1;
		finRead1.open(str, ios::in);
		if (!finRead1.is_open())
		{
			cout << "finRead3 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line; int num1 = 0;

		while (getline(finRead1, line))
		{

			if (line.empty())
			{
				break;
			}

			num1++;

			int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			int objw = x2 - x1 + 1; int objh = y2 - y1 + 1;

			float objperw = objw*1.0 / img.cols;
			float objperh = objh*1.0 / img.rows;

			imfo57_21 vi;
			vi.name = name1;

			vi.ratiow = objperw;
			vi.ratioh = objperh;

			vi.objw = objw;
			vi.objh = objh;

			vi.width = img.cols;
			vi.height = img.rows;
			vfo.push_back(vi);


			if (objperw<minw)
			{
				minw = objperw;
			}
			if (objperh < minh)
			{
				minh = objperh;
			}

			if (objperw>maxw)
			{
				maxw = objperw;
			}
			if (objperh > maxh)
			{
				maxh = objperh;
			}

		}

		finRead1.close();

	}
	printf("perminw=%f,perminh=%f,permaxw=%f,permaxh=%f\n", minw, minh, maxw, maxh);

	sort(vfo.begin(), vfo.end(), LessSortw);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57_21 vi = vfo[j];
		finWrite << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.objw << " " << vi.objh
			<< " " << vi.width << " " << vi.height << endl;
	}

	finWrite.close();


	sort(vfo.begin(), vfo.end(), LessSorth);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57_21 vi = vfo[j];
		finWrite2 << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.objw << " " << vi.objh
			<< " " << vi.width << " " << vi.height << endl;
	}

	finWrite2.close();










	return 0;
}