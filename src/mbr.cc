#include "mbr.h"
#include "fstype.h"

mbrAnalyse::mbrAnalyse() {
	mbrPart.clear();
}

void mbrAnalyse::getRawMBR(const char* diskISO) {
	char cmd[81];
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "sudo dd if=%s of=../tmp/mbr.dd bs=1 skip=446 count=66 2> ../logs/mbrlog", diskISO);
	system(cmd);
	FILE* fp;
	fp = fopen("../tmp/mbr.dd", "rb");
	$mbr tmp;
	for(size_t offset = 0; offset < 64; offset += 16) {
		tmp = $mbr();
		fseek(fp, 1+offset, 0);
		fread(&tmp.startingCHSAddress, 1, 3, fp);

		fseek(fp, 4+offset, 0);
		fread(&tmp.partitionType, 1, 1, fp);

		fseek(fp, 5+offset, 0);
		fread(&tmp.endingCHSAddress, 1, 3, fp);
		
		fseek(fp, 8+offset, 0);
		fread(&tmp.startingLBAAddress, 1, 4, fp);
		
		fseek(fp, 12+offset, 0);
		fread(&tmp.sizeInSectors, 1, 4, fp);
		if(!tmp.startingLBAAddress) {
			continue;
		}

		tmp.endingLBAAddress = tmp.startingLBAAddress + tmp.sizeInSectors - 1;
		mbrPart.push_back(tmp);
	}
}

void mbrAnalyse::showMBR() {
	cout << "Partition(s) number : " << mbrPart.size() << endl;
	cout << "------------------------------------" << endl;
	for(int i = 0; i < mbrPart.size(); i++) {
		cout << "Partition " << i + 1 << endl;
		cout << "Paritition type : " << fsType(mbrPart[i].partitionType) << endl;
		mbrPart[i].show();
		if(i < mbrPart.size() - 1) {
			cout << ".................................." << endl;
		}
	}
	cout << "------------------------------------" << endl;
}

void mbrAnalyse::savingLBAMessage() {
	system("touch ../tmp/VSP");
	ofstream fileWrite;
	fileWrite.open("../tmp/VSP");
	for(int i = 0; i < mbrPart.size(); i++) {
		fileWrite << mbrPart[i].startingLBAAddress << endl;
	}
	fileWrite.close();
}








