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
				else
				{
					kprintf("Kernel page: %x\n",addr);
				}
				addr += 0x1000;//which is one page (4096 bytes)
			}
		}
		mMap++;
	}
	kprintf("There are %u free available memory pages.\n", i);
}

void *mMAllocPage()
{
	int bm, i;
	//kprintf("[ALLC] Searching for free pages.\n");
	for(bm=0;bm<BITMAP_SIZE;bm++)
	{
		if(bitmap[bm] != 0)
		{
			//kprintf("[ALLC] Found space on page %u. Bitmap: %x\n",i,bitmap[bm]);
			for(i = 0;i<32;i++)
			{
				if((bitmap[bm] & (1<<i)) && (i != 0 || bm != 0)/*don't return null pointer*/)
				{
					bitmap[bm] &= ~(1<<i);
					return (void*)(0x1000*(bm*32+i));
				}
			}
		}
	}
	return NULL;//no space available :(
}

void mMFreePage(void *page)
{
	uintptr_t index = (uintptr_t)page/0x1000;
	bitmap[index/32] |= (1 << (index % 32));
	//kprintf("[FREE] Index: %u, Bitmap: %x\n", index/32,bitmap[index/32]);
}
