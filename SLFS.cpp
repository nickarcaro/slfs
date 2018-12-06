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
	const static int diskSize = 6;
	Block blocks[diskSize];

public:
	Disk()
	{
		for (int i = 0; i < diskSize; ++i)
		{
			Block blk;
			blocks[i] = blk;
		}
	}

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
	void mount(Disk *d)
	{
		SuperBlock sb;
		sb.blockNum = 6;

		Bitmap bmp;
		bmp.usedInodes[1] = true;
		for (int i = 1; i < inodesPerBlock; ++i)
		{
			bmp.usedInodes[i] = 0
		}

		Inode newInodes[inodesPerBlock];



	}

	void createDir()
	{

	}

	void createFile()
	{

	}

	//readFile()
};

int main(int argc, char const *argv[])
{
	Block blk;
	blk.data[0] = 'x';

	Disk *d = new Disk;
	d->write(0, blk);

	//cout << d.read(0)->data[0];

	return 0;
}