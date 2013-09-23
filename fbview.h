#ifndef _H_FBVIEW_
#define _H_FBVIEW_

#include <SupportDefs.h>
#include <Bitmap.h>
#include <View.h>
#include <Rect.h>

class FBView : public BView 
{
 public:
		FBView(BRect rect);
		FBView(BRect rect, int width, int height);
		~FBView();
		
		void 	Paint();
		uint32	*GetBuffer();
		uint32	GetBufferSize();
		
		int		Width();
		int		Height();
 private:
 		int		buffer_width;
 		int		buffer_height;
		BView	*bufferView;
		BBitmap *bufferBitmap; 		
};

#endif
