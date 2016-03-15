#include <string>

char* fsType(const size_t type) {
    std::string ans;
    switch(type) {
        case 0x00: ans = "Empty"; break;
        case 0x01: ans = "FAT12, CHS"; break;
        case 0x04: ans = "FAT16, 16-32MB, CHS"; break;
        case 0x05: ans = "Microsoft Extended, CHS"; break;
        case 0x06: ans = "FAT16, 32MB-2GB, CHS"; break;
        case 0x07: ans = "NTFS"; break;
        case 0x0b: ans = "FAT32, CHS"; break;
        case 0x0c: ans = "FAT32, LBA"; break;
        case 0x0e: ans = "FAT16, 32MB-2GB, LBA"; break;
        case 0x0f: ans = "Microsoft Extended, LBA"; break;
        case 0x11: ans = "Hidden FAT12, CHS"; break;
        case 0x14: ans = "Hidden FAT16, 16-32MB, CHS"; break;
        case 0x16: ans = "Hidden FAT16, 32MB-2GB, CHS"; break;
        case 0x1b: ans = "Hidden FAT32, CHS"; break;
        case 0x1c: ans = "Hidden FAT32, LBA"; break;
        case 0x1e: ans = "Hidden FAT16, 32MB-2GB, LBA"; break;
        case 0x42: ans = "Microsoft MBR. Dynamic Disk"; break;
        case 0x82: ans = "Solaris x86"; break;
        case 0x83: ans = "Linux"; break;
        case 0x84: ans = "Hibernation"; break;
        case 0x85: ans = "Linux Extended"; break;
        case 0x86: ans = "NTFS Volume Set"; break;
        case 0x87: ans = "NTFS Volume Set"; break;
        case 0xa0: ans = "Hibernation"; break;
        case 0xa1: ans = "Hibernation"; break;
        case 0xa5: ans = "FreeBSD"; break;
        case 0xa6: ans = "OpenBSD"; break;
        default : ans = "No Match";
    }
    return const_cast<char*>(ans.c_str());
}
