#include "dir.h"


void ufs::init() {
	for(int i = 0; i < 256; i++) {
		father[i] = i;
	}
	memset(isUsed, 0, sizeof(isUsed));
}

uint16_t ufs::find(uint16_t x) {
	return x == father[x] ? x : father[x] = find(father[x]);
}

void ufs::unite(uint16_t x, uint16_t y) {
	x = find(x);
	y = find(y);
	if(x != y) {
		if(x > y) father[x] = y;
		else father[y] = x;
	}
}

ufs::ufs() {
	init();
}

dirAnalyse::dirAnalyse() {
	fileRelation.init();
}

void dirAnalyse::readDSP() {
	int32_t dspTmp;
	ifstream fileRead("../tmp/DSP");
	while(fileRead >> dspTmp) {
		dsp.push_back(dspTmp);
	}
	fileRead.close();
}

void dirAnalyse::getFATRelation() {
	for(int i = 255; i > 0; i--) {	// 0 is the vbr or empty
		if(fat[i] == 0x0000) {
			continue;
		}
		if(fat[i] == 0xffff) {
			fileRelation.isUsed[i] = 1;
			fileRelation.father[i] = i;
		}
		else {
			fileRelation.isUsed[i] = 1;
			fileRelation.unite(i, fat[i]);
		}
	}
//	for(int i = 1; i < 20; i++) {
//		cout << i << " " << fat[i] << " " << fileRelation.father[i] << endl;
//	}
}

void dirAnalyse::getFAT(size_t sizeOfReservedArea, int64_t vsp, const char* diskISO) {
	this->sizeOfReservedArea = sizeOfReservedArea;
	char cmd[81], fatName[81];
	sprintf(cmd, "sudo dd if=%s of=../tmp/FAT bs=512 skip=%d count=1 2>../logs/fatlog", diskISO, sizeOfReservedArea + vsp);
	system(cmd);
	sprintf(fatName, "../tmp/FAT");
	FILE* fp;
	fp = fopen(fatName, "rb");
	for(int i = 0; i < 256; i++) {
		fseek(fp, 2 * i, 0);
		fread(&fat[i], 2, 1, fp);
//		cout << fat[i] << " ";
	}
}

void dirAnalyse::getRawDIR(const char* diskISO) {
	char cmd[81], dirName[81];
	$dir tmp;
	for(int curDIRPos = 0; curDIRPos < dsp.size(); curDIRPos++) {
		tmp = $dir();
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "sudo dd if=%s of=../tmp/dir%d.dd bs=512 skip=%d count=5 2> ../logs/dirlog", diskISO, curDIRPos, dsp[curDIRPos]);
		system(cmd);
		memset(dirName, 0, sizeof(dirName));
		sprintf(dirName, "../tmp/dir%d.dd", curDIRPos);
		FILE* fp;
		fp = fopen(dirName, "rb");
		size_t offset = 0;
		while(1) {
			fseek(fp, offset + 11, 0);
			fread(&tmp.fileAttribute, 1, 1, fp);
	
			fseek(fp, offset + 20, 0);
			fread(&tmp.high2Address, 1, 2, fp);
	
			fseek(fp, offset + 26, 0);
			fread(&tmp.low2Address, 1, 2, fp);

			fseek(fp, offset + 28, 0);
			fread(&tmp.sizeOfFile, 1, 4, fp);
	
			fseek(fp, offset + 0, 0);
			fread(tmp.fileName, 1, 11, fp);

			offset += 32;
			
			if(tmp.fileAttribute == 0x0f || tmp.fileName[0] == 0xe5) {
				continue;
			}
			if(tmp.fileName[0] == 0) {
				break;
			}
			tmp.addressInSector = dsp[curDIRPos] + tmp.low2Address * sizeOfCluster;
			dirPart.push_back(tmp);

		}
	}

}

size_t dirAnalyse::getCertainSectorInformation(
size_t aimSector, vector<size_t>& involveSector) {
	cout << "The sector : " << aimSector << endl << "The Result :" << endl;
	size_t aimCluster = (aimSector - dsp[0]) / sizeOfCluster;
	size_t fileBegin = fileRelation.find(aimCluster);
	if(!fileRelation.isUsed[fileBegin]) return 0;
	while(fat[fileBegin] != 0xffff) {
		involveSector.push_back(fileBegin);
		fileBegin = fat[fileBegin];
	}
	involveSector.push_back(fileBegin);
	for(int i = 0; i < involveSector.size(); i++) {
		for(int j = 0; j < dirPart.size(); j++) {
			if(involveSector[i] == dirPart[j].low2Address) {
				cout << "The file name : " << dirPart[j].fileName  << endl;
				return involveSector[i];
			}
		}
	}
}

void dirAnalyse::getFileInformation(size_t fileHead, vector<size_t> involveSector) {
	char cmd[81];
	for(int i = 0; i < involveSector.size(); i++) {
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "sudo dd if=/dev/sdb of=../data/part%d.dat bs=512 count=1 skip=%d", i, fileHead * 16 + 2561);
		
	}
}

void dirAnalyse::showDIR() {
//	for(int i = 0; i < dirPart.size(); i++) {
//		cout << "Address : " << dirPart[i].addressInSector << " " << "Size : " << dirPart[i].sizeOfFile << endl;
//	}
}
