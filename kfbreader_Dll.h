#pragma once
#ifdef KFBREADER_EXPORTS
#define	KFBREADER_API __declspec(dllexport)
#else
#define	KFBREADER_API __declspec(dllimport)
#endif
#include <string>

class KFBREADER_API kfbreader
{
public:
	kfbreader();
	void ReadInfo(std::string kfbpath, int scale, int &w, int &h, int read_whole = true); // scale=20
	void ReadRoi(int x, int y, int w, int h, float scale,unsigned char **pd); 
	int readLabelImage(unsigned char** pd, int* w,int *h);
	int readPreviewImage(unsigned char** pd, int* w, int *h);
	int GetScale();
	void clear();
	~kfbreader();

private:
	int init();
	//Êý¾ÝÀà
	void * pKfbreader_;
};