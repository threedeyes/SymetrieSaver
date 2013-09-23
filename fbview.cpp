#include <stdio.h>

#include "fbview.h"

FBView::FBView(BRect rect) : 
	BView(rect, "FBView", B_FOLLOW_ALL, B_WILL_DRAW|B_PULSE_NEEDED|B_FRAME_EVENTS)
{
	FBView(rect, rect.IntegerWidth(), rect.IntegerHeight());
}


FBView::FBView(BRect rect, int width, int height) : 
	BView(rect, "FBView", B_FOLLOW_ALL, B_WILL_DRAW|B_PULSE_NEEDED|B_FRAME_EVENTS)
{
	buffer_width = width;
	buffer_height = height;
	
	BRect	fbRect = BRect(0,0,buffer_width-1,buffer_height-1);	
	bufferView = new BView(fbRect, "bufferView", B_FOLLOW_ALL_SIDES, 0);
	bufferBitmap = new BBitmap(fbRect, B_RGB32, true);	
	bufferBitmap->AddChild(bufferView);		
}


FBView::~FBView()
{
	
}


void 
FBView::Paint()
{
  if(LockLooper())	{
 	 bufferView->LockLooper();
 	 SetDrawingMode(B_OP_COPY);
	 DrawBitmap(bufferBitmap,bufferView->Bounds(),Bounds());
	 bufferView->UnlockLooper();
	 UnlockLooper();
	}
}


uint32 *
FBView::GetBuffer()
{
	if(bufferBitmap) {
		return (uint32*)bufferBitmap->Bits();
	}
	return NULL;
}


uint32	
FBView::GetBufferSize()
{
	if(bufferBitmap) {
		return bufferBitmap->BitsLength()/4;
	}
	return 0;
}


int
FBView::Width() 
{
	return buffer_width;
}


int
FBView::Height()
{
	return buffer_height;
}


