#include"pch.h"

long int OffDosHeader;
long int OffFileHeader;
long int OffOptHeader;
long int OffSecHeader;

void CalculateOffset(int fd)
{
	IMAGE_DOS_HEADER dosHeader;
	_read(fd,&dosHeader,sizeof(dosHeader));

	OffDosHeader = 0;
	cout << OffDosHeader<<endl;
	
	OffFileHeader = dosHeader.e_lfanew + 4;
	cout << OffFileHeader<< endl;

	OffOptHeader = OffFileHeader + 0x14;
	cout << OffOptHeader<< endl;

	OffSecHeader = OffOptHeader + sizeof(IMAGE_OPTIONAL_HEADER);
	cout << OffSecHeader << endl;

	_lseek(fd,0,0);
}

dos_header::dos_header(int f)
{
	fp = f;
	_lseek(fp,OffDosHeader,0);
	_read(f,&dosHeader,sizeof(dosHeader));
}

void dos_header::show_header()
{
	cout << endl << "--------------------DOS HEADER INFO-----------------------" << endl;
	cout << "Magic number:\t" << std::hex << dosHeader.e_magic << endl;
	cout << "Bytes on last page of file:\t" << dosHeader.e_cblp << endl;
	cout << "Pages in file:\t" << dosHeader.e_cp << endl;
	cout << "Relocation:\t" << dosHeader.e_crlc << endl;
	cout << "Size of header in paragraphs:\t" << dosHeader.e_cparhdr << endl;
	cout << "Minimum extra paragraph needed:\t" << dosHeader.e_minalloc << endl;
	cout << "Maximum extra paragraph needed:\t" << dosHeader.e_maxalloc << endl;
	cout << "Initial (relative) SS value:\t" << dosHeader.e_ss << endl;
	cout << "Initial SP value:\t" << dosHeader.e_sp << endl;
	cout << "Checksum:\t" << dosHeader.e_csum << endl;
	cout << "Initial IP value:\t" << dosHeader.e_ip << endl;
	cout << "Initial (relative) CS value:\t" << dosHeader.e_cs << endl;
	cout << "File address of relocation table:\t" << dosHeader.e_lfarlc << endl;
	cout << "Overlay number:\t" << dosHeader.e_ovno<< endl;
	cout << "OEM identifier:\t" << dosHeader.e_oemid << endl;
	cout << "OEM information(e_oemid specific):\t" << dosHeader.e_oeminfo << endl;
	cout << "RVA addres of PE header:\t" << dosHeader.e_lfanew << endl;
}


file_header::file_header(int f)
{
	fp = f;
	_lseek(fp,OffFileHeader,0);
	_read(f,&fileHeader,sizeof(fileHeader));
}

void file_header :: show_header()
{
	cout << endl << "-----------------------------------FILE HEADER INFO----------------------------" << endl;
	cout << "Machine:\t" << fileHeader.Machine << endl;
	cout << "Number of sections:\t" << fileHeader.NumberOfSections << endl;
	cout << "Time Date Stamp:\t" << fileHeader.TimeDateStamp<< endl;
	cout << "Pointer to symbol table:\t" << fileHeader.PointerToSymbolTable<< endl;
	cout << "Number of symbols:\t" << fileHeader.NumberOfSymbols<< endl;
	cout << "Size Of Optional Header:\t" << fileHeader.SizeOfOptionalHeader<< endl;
	cout << "Characteristics:\t" << fileHeader.Characteristics<< endl;
}

opt_header::opt_header(int f)
{
	fp = f;
	_lseek(fp, OffOptHeader, 0);
	_read(f, &optHeader, sizeof(optHeader));
}

void opt_header::show_header()
{
	cout << endl << "--------------------------------OPTIONAL HEADER INFO------------------------------------------" << endl;
	cout << "Magic:\t" << optHeader.Magic << endl;
	cout << "Size Of Code:\t" << optHeader.SizeOfCode<< endl;
	cout << "Size of initialized data:\t" << optHeader.SizeOfInitializedData << endl;
	cout << "Size of uninitialized data:\t" << optHeader.SizeOfUninitializedData<< endl;
	cout << "Address of entry point:\t" << optHeader.AddressOfEntryPoint<< endl;
	cout << "Base of code:\t" << optHeader.BaseOfCode<< endl;
	cout << "Base of data:\t" << optHeader.BaseOfData<< endl;
	cout << "Image base:\t" << optHeader.ImageBase<< endl;
	cout << "Section Alignment:\t" << optHeader.SectionAlignment<< endl;
	cout << "File Alignment:\t" << optHeader.FileAlignment<< endl;
	cout << "Major operating system version:\t" << optHeader.MajorOperatingSystemVersion<< endl;
	cout << "Minor operating system version:\t" << optHeader.MinorOperatingSystemVersion << endl;
	cout << "Major image version:\t" << optHeader.MajorImageVersion << endl;
	cout << "Minor image version:\t" << optHeader.MinorImageVersion<< endl;
	cout << "Major subsystem version:\t" << optHeader.MajorSubsystemVersion<< endl;
	cout << "Minor subsystem version:\t" << optHeader.MinorSubsystemVersion<< endl;
	cout << "Size of image:\t" << optHeader.SizeOfImage<< endl;
	cout << "Size of headers:\t" << optHeader.SizeOfHeaders << endl;
	cout << "Checksum:\t" << optHeader.CheckSum<< endl;
	cout << "Subsystem:\t" << optHeader.Subsystem<< endl;
	cout << "Dll Characteristics:\t" << optHeader.DllCharacteristics<< endl;
	cout << "Size of stack reserved:\t" << optHeader.SizeOfStackReserve<< endl;
	cout << "Size of stack commit:\t" << optHeader.SizeOfStackCommit << endl;
	cout << "Size of heap reserved:\t" << optHeader.SizeOfHeapReserve<< endl;
	cout << "Size of heap commit:\t" << optHeader.SizeOfHeapCommit << endl;
	cout << "Loader Flags:\t" << optHeader.LoaderFlags<< endl;
	cout << "Number of RVA and Sizes:\t" << optHeader.NumberOfRvaAndSizes<< endl;
}

sec_header::sec_header(int f)
{
	IMAGE_FILE_HEADER fileHeader;
	fp = f;
	_lseek(fp, OffFileHeader, 0);
	_read(f, &fileHeader, sizeof(fileHeader));
	NoOfSec = fileHeader.NumberOfSections;
	_lseek(fp, OffSecHeader, 0);
	_read(f, &secHeader, sizeof(secHeader));
}

void sec_header::show_header()
{
	cout << endl << "--------------------------------SECTION HEADER INFO------------------------------------------" << endl;
	while (NoOfSec!=0)
	{
		cout << "Name:\t" << secHeader.Name << endl;
		cout << "Virtual Address:\t" << secHeader.VirtualAddress<< endl;
		cout << "Size Of Raw Data:\t" << secHeader.SizeOfRawData<< endl;
		cout << "Pointer to raw data:\t" << secHeader.PointerToRawData << endl;
		cout << "Pointer to relocations:\t" << secHeader.PointerToRelocations<< endl;
		cout << "Pointer to line numbers:\t" << secHeader.PointerToLinenumbers<< endl;
		cout << "Number of relocation:\t" << secHeader.NumberOfRelocations << endl;
		cout << "Number of line numbers:\t" << secHeader.NumberOfLinenumbers<< endl;
		NoOfSec--;
		cout<<endl<<"-----------------------------------------------------------------------------"<<endl;
		_read(fp,&secHeader,sizeof(secHeader));
	}
}
