#include <iostream>

using namespace std;

const static int pointersPerInode = 5;
const static int inodesPerBlock = 128;
const static int inodeBlocks = 1;
const static size_t blockSize = 4096;

struct SuperBlock
{
	int blockNum;
};

struct Bitmap
{
	bool usedInodes[inodesPerBlock];
};

struct Inode
{
	int inodeNum;
	char type; // 'f' para file y 'd' para directory
	int creationDate;
	int fileSize;
	int blocks[pointersPerInode];
};

union Block
{
	SuperBlock s;
	Bitmap b;
	Inode inodes[inodesPerBlock];
	char data[blockSize];
};


class Disk
{
private:
	//3 bloques para datos
	Block blocks[6];

public:
	Block* read(int blockNum)
	{
		return &blocks[blockNum];
	}
	void write(int blockNum, Block newBlock)
	{
		blocks[blockNum] = newBlock;
	}
};

class StanLeeFS
{
public:
	StanLeeFS();
	
	
};

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}