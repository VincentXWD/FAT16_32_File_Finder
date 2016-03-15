#include "includes.h"

using namespace std;


typedef struct $mbr {
	int32_t startingCHSAddress;
	int32_t endingCHSAddress;
	int64_t startingLBAAddress;
	int64_t sizeInSectors;
	int32_t partitionType;
	int64_t endingLBAAddress;
	
	$mbr() {
		startingCHSAddress = 0;
		endingCHSAddress = 0;
		startingLBAAddress = 0;
		sizeInSectors = 0;
		partitionType = 0;
		endingLBAAddress = 0;
	}
	void show() {
		cout << "LBA starting at : " << startingLBAAddress << endl
			 << "LBA ending at : " <<
			 startingLBAAddress + sizeInSectors - 1 << " " << endl
			 << "Size of this partition : " << sizeInSectors / 2048 << "MB"
			 << endl;
	}
}$mbr;

typedef class mbrAnalyse {
public:
	// friend class vbrAnalyse;
	mbrAnalyse();
	void getRawMBR(const char*);
	void showMBR();
	void savingLBAMessage();
private:
	std::vector<$mbr> mbrPart;
}mbrAnalyse;
