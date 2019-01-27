

#ifndef PCH_H
#define PCH_H

#include<stdio.h>
#include<Windows.h>
#include<iomanip>
#include<stdlib.h>
#include<io.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<conio.h>
#include<iostream>

using namespace std;


void CalculateOffset(int);

class dos_header
{
public:
	IMAGE_DOS_HEADER dosHeader;
	int fp;

	dos_header(int);
	void show_header();
};

class file_header
{
public:
	IMAGE_FILE_HEADER fileHeader;
	int fp;

	file_header(int);
	void show_header();
};

class opt_header
{
public:
	IMAGE_OPTIONAL_HEADER optHeader;
	int fp;

	opt_header(int);
	void show_header();
};

class sec_header
{
public:
	IMAGE_SECTION_HEADER secHeader;
	int NoOfSec;
	int fp;

	sec_header(int);
	void show_header();
};

#endif //PCH_H
