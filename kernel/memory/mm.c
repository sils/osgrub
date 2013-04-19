#include "../include.h"

static uint32_t bitmap[BITMAP_SIZE];

void mMInit(const struct multiBoot *mbinfo)
{
	unsigned int i;
	//let's say everything is reserved
	for(i=0;i<BITMAP_SIZE;i++)
		bitmap[BITMAP_SIZE]=0x0;//1 is free, 0 is reserved - easier for conditions
	
	struct multiBootMap* mMap = mbinfo->mMapAddr;
	struct multiBootMap* mEndMap = (void*)((uintptr_t) mbinfo->mMapAddr + mbinfo->mMapLength);
	i=0;
	while(mMap < mEndMap)
	{
		if(mMap->type == 1)
		{
			uintptr_t addr = mMap->base;
			uintptr_t endAddr = mMap->base + mMap->length;
		
			while(addr < endAddr)
			{
				if(addr > (uintptr_t)&kernel_end || addr < (uintptr_t)&kernel_start)
				{
					mMFreePage((void*)addr);
					i++;
				}
				addr += 0x1000;//which is one page (4096 bytes)
			}
		}
		mMap++;
	}
	kprintf("There are %u free available memory pages.\n", i);
}

uintptr_t globIndex=0;

void *mMAllocPage()
{
	static uintptr_t start;
	start=globIndex-32;
	unsigned char i;
	while((bitmap[globIndex/32] == 0) && (start != globIndex))
	{
		if(globIndex/32 >= BITMAP_SIZE)
			globIndex=0;
		globIndex++;
	}
	if(bitmap[globIndex/32] != 0)
	{
		//there is space available
		for(i = 0;i<32;i++)
		{
			if(bitmap[globIndex/32] & (1<<i))
			{
				bitmap[globIndex/32] &= ~(1<<i);
				return (void*)(0x1000*(globIndex+i));
			}
		}
	}
	return NULL;//no space available :(
}

void mMFreePage(void *page)
{
	globIndex = (uintptr_t)page/0x1000;
	bitmap[globIndex/32] = (1 << (globIndex % 32));
}
