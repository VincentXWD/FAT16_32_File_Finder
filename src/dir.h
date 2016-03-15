#include "includes.h"
#include <stdint.h>
using namespace std;

#ifndef SIZEOFCLUSTER
#define SIZEOFCLUSTER
const size_t sizeOfCluster = 16;
#endif

typedef struct $dir {
	unsigned char fileAttribute;
	uint32_t high2Address;	// high 2 bytes
	uint32_t low2Address; 	// low 2 bytes
	uint32_t sizeOfFile;	// zero for directories
	char fileName[21];		// first char (0x00 or 0xe5)
	uint32_t addressInSector;
}$dir;

typedef class ufs {
public:
	ufs();
	void init();
	uint16_t find(uint16_t);
	void unite(uint16_t, uint16_t);
public:
	uint16_t father[256];
	bool isUsed[256];
}ufs;

typedef class dirAnalyse {
public:
	dirAnalyse();
	void readDSP();
	void getFATRelation();
	void getRawDIR(const char*);
	void getFileInformation(size_t, vector<size_t>);
	void showDIR();
	void getFAT(size_t, int64_t, const char*);
	size_t getCertainSectorInformation(size_t, vector<size_t>&);
public:
	size_t sizeOfReservedArea;
	vector<int32_t> dsp;
	vector<$dir> dirPart;
	uint16_t fat[256];
	ufs fileRelation;
}dirAnalyse;
