#include "vbr.h"
#define CHECK(_, __) fseek(_, 510, 0); \
						 fread(&__, 1, 4, _); \
  						 printf("%x\n", __)

vbrAnalyse::vbrAnalyse() {
	vsp.clear();
	vbrPart.clear();
}

void vbrAnalyse::readVSP() {
	int64_t vspTmp;
	ifstream fileRead("../tmp/VSP");
	while(fileRead >> vspTmp) {
		vsp.push_back(vspTmp);
	}
	fileRead.close();
}


void vbrAnalyse::getRawVBR(const char* diskISO) {
	char cmd[81], vbrName[81];
	$vbr tmp;
	for(int curVBRPos = 0; curVBRPos < vsp.size(); curVBRPos++) {
		tmp = $vbr();
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "sudo dd if=%s of=../tmp/vbr%d.dd bs=512 skip=%lld count=1 2> ../logs/vbrlog", diskISO, curVBRPos, vsp[curVBRPos]);
		system(cmd);
		memset(vbrName, 0, sizeof(vbrName));
		sprintf(vbrName, "../tmp/vbr%d.dd", curVBRPos);
		FILE* fp;
		fp = fopen(vbrName, "rb");

		fseek(fp, 3, 0);
		fread(&tmp.OEMName, 1, 8, fp);
		
		fseek(fp, 14, 0);
		fread(&tmp.sizeOfReservedArea, 1, 2, fp);

		fseek(fp, 16, 0);
		fread(&tmp.numberOfFAT, 1, 1, fp);
		
		fseek(fp, 22, 0);
		fread(&tmp._16bitSize, 1, 2, fp);
		
		fseek(fp, 11, 0);
		fread(&tmp.bytesPerSector, 1, 2, fp);

		if(tmp._16bitSize == 0) {
			fseek(fp, 36, 0);
			fread(&tmp._32bitSize, 1, 4, fp);
		}
		vbrPart.push_back(tmp);
		
		// int __;
		// CHECK(fp, __);
	}
}

void vbrAnalyse::findFAT() {
	for(int curVBRPos = 0; curVBRPos < vsp.size(); curVBRPos++) {
		vbrPart[curVBRPos].FATStartPosition = 
			vbrPart[curVBRPos].sizeOfReservedArea + vsp[curVBRPos];
			if(vbrPart[curVBRPos]._16bitSize != 0) {
				vbrPart[curVBRPos].FATStartPosition += 
					vbrPart[curVBRPos]._16bitSize * vbrPart[curVBRPos].numberOfFAT;
			}
			else {
				vbrPart[curVBRPos].FATStartPosition += 
					vbrPart[curVBRPos]._32bitSize * vbrPart[curVBRPos].numberOfFAT;
			}
		// printf("%lld\n", vbrPart[curVBRPos].FATStartPosition);
	}
}

void vbrAnalyse::saveFATMessage() {
	system("touch ../tmp/DSP");
	ofstream fileWrite;
	fileWrite.open("../tmp/DSP");
	for(int i = 0; i < vbrPart.size(); i++) {
		fileWrite << vbrPart[i].FATStartPosition << endl;
	}
	fileWrite.close();
}

void vbrAnalyse::showVBR() {
	cout << "For each partition. We have information below." << endl;
	cout << "----------------------------------------" << endl;
	for(int vbrIndex = 0; vbrIndex < vbrPart.size(); vbrIndex++) {
		cout << "File system " << vbrIndex + 1  
		     << " root directory intrance : " << 
			 vbrPart[vbrIndex].FATStartPosition << endl;
		cout << "Bytes per sector : " << vbrPart[vbrIndex].bytesPerSector << endl;
		if(vbrIndex < vsp.size() - 1) {
			cout << "...................................." << endl;
		}
	}
	cout << "----------------------------------------" << endl;	
}




