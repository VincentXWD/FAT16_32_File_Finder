#include "includes.h"

using namespace std;

typedef struct $vbr {
	char OEMName[9];
	size_t sizeOfReservedArea;
	size_t numberOfFAT;
	size_t _16bitSize;
	size_t _32bitSize;
	size_t bytesPerSector;
	int64_t FATStartPosition;

	$vbr() {
		sizeOfReservedArea = 0;
		numberOfFAT = 0;
		memset(OEMName, 0, sizeof(OEMName));
		_16bitSize = 0;
		_32bitSize = 0;
	}
}$vbr;

typedef class vbrAnalyse {
public:
	friend class dirAnalyse;
	vbrAnalyse();
	void readVSP();
	void getRawVBR(const char*);
	void findFAT();
	void saveFATMessage();
	void showVBR();
public:
	vector<int64_t> vsp;
	vector<$vbr> vbrPart;
	
}vbrAnalyse;
