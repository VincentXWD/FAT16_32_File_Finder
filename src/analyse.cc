#include "analyse.h"

void analyse::go(const char* diskISO, const char* aimSector) {
	system("sudo mkdir ../logs ../tmp ../data 2> /dev/null");
	this->aimSector = atoi(aimSector);

	mbr.getRawMBR(diskISO);
	mbr.savingLBAMessage();
	
	vbr.readVSP();
	vbr.getRawVBR(diskISO);
	vbr.findFAT();
	vbr.saveFATMessage();
	
	dir.readDSP();
	dir.getRawDIR(diskISO);
	dir.getFAT(vbr.vbrPart[0].sizeOfReservedArea, vbr.vsp[0], diskISO);
	dir.getFATRelation();
	vector<size_t> involveSector;
	involveSector.clear();
//	this->show();	
	size_t sflag;
	if(this->aimSector < vbr.vsp[0]) {
		cout << "Error! This sector is beyond this partition!" << endl << endl;
		return;
	}
	sflag = dir.getCertainSectorInformation(this->aimSector, involveSector);
	if(sflag != 0) {
		cout << "We find it that there're " << involveSector.size() << " cluster(s) that the file is used." << endl;
		for(int i = 0; i < involveSector.size(); i++) {
			cout << "The " << i + 1 << "th cluster number : " << involveSector[i] << endl;
		}
		cout << endl;
	}
	else {
		cout << "Sorry. We don't find the sector's information. It's available." << endl << endl;
	}
	cout <<"-----------------------------------------" << endl;
//	if(involveSector.size() != 0) {
//		dir.getFileInformation(sflag, involveSector);
//	}
}

void analyse::show() {
	mbr.showMBR();
	cout << endl << endl;
	vbr.showVBR();
	cout << endl << endl;
	dir.showDIR();
	
}
