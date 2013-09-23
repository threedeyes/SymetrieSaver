#include <ScreenSaver.h>
#include <StringView.h>
#include <String.h>
#include <Slider.h>
#include <Font.h>
#include <CheckBox.h>

#include "fbview.h"

#define WIDTH	1024
#define HEIGHT	768

class Symetrie : public BScreenSaver, public BHandler 
{
public:
				Symetrie(BMessage *message, image_id id);
	virtual		~Symetrie();				
	void		StartConfig(BView *view);
	status_t	StartSaver(BView *v, bool preview);
	void		Draw(BView *v, int32 frame);
	virtual	status_t			SaveState(BMessage* into) const;
	virtual	void				MessageReceived(BMessage* message);
private:
	BStringView		*tview;
	BSlider			*fSpeedSlider;
	BCheckBox		*fCorners;
	BCheckBox		*fBigPoints;
	FBView			*fb;

	
};
