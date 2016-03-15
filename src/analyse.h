#ifndef ANALYSE_H
#define ANALYSE_H

#include "includes.h"
#include "mbr.h"
#include "vbr.h"
#include "dir.h"

using namespace std;

typedef class analyse {
public:
	analyse() {}
	void go(const char*, const char*);
	void show();
protected:
	mbrAnalyse mbr;
	vbrAnalyse vbr;
	dirAnalyse dir;

private:
	string diskISO;
	size_t aimSector;
}analyse;

#endif
