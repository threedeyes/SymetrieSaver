#include <StringView.h>
#include <Slider.h>
#include <stdlib.h>
#include <View.h>
#include <Polygon.h>
#include <Bitmap.h>
#include <Screen.h>
#include <stdio.h>
#include <time.h>

#include "Symetrie.h"

extern int32 	renderer(FBView *view);
extern int 		init(FBView *view);
extern void 	frame(double t);

extern float 	SPEED;
extern bool 	BIG_POINTS;
extern bool		CORNERS;


extern "C" _EXPORT BScreenSaver *instantiate_screen_saver(BMessage *message, image_id image)
{
	return new Symetrie(message, image);
}


Symetrie::Symetrie(BMessage *message, image_id image)
 : BScreenSaver(message, image), BHandler("SymetrieSaver")
{
	if (message) {
		if (message->FindFloat("Speed", &SPEED) < B_OK)
			SPEED = 0.2;
		if (message->FindBool("Corners", &CORNERS) < B_OK)
			CORNERS = true;
		if (message->FindBool("BigPoints", &BIG_POINTS) < B_OK)
			BIG_POINTS = false;
	}
}


Symetrie::~Symetrie()
{
	if (Looper()) {
		Looper()->RemoveHandler(this);
	}
}


void 
Symetrie::StartConfig(BView *view)
{
	BRect bounds = view->Bounds();
	bounds.InsetBy(10.0, 10.0);
	BRect frame(0.0, 0.0, bounds.Width(), bounds.Height());

	if (BWindow* window = view->Window())
		window->AddHandler(this);

	tview = new BStringView(frame, B_EMPTY_STRING, "SymetrieSaver");
	tview->SetFont(be_bold_font);
	tview->SetFontSize(15);
	view->AddChild(tview);
	tview->ResizeToPreferred();
	frame.top = tview->Frame().bottom+15;

	fCorners = new BCheckBox(frame, "corners setting",
								"Corners",
								new BMessage('CORN'),
								B_FOLLOW_LEFT);

	fCorners->SetValue(CORNERS);
	fCorners->ResizeToPreferred();
	view->AddChild(fCorners);
	fCorners->SetTarget(this);
	frame.top = fCorners->Frame().bottom+15;		

	fBigPoints = new BCheckBox(frame, "Big points setting",
								"Big points",
								new BMessage('BIGP'),
								B_FOLLOW_LEFT);

	fBigPoints->SetValue(BIG_POINTS);
	fBigPoints->ResizeToPreferred();
	view->AddChild(fBigPoints);
	fBigPoints->SetTarget(this);
	frame.top = fBigPoints->Frame().bottom+15;		
		
	fSpeedSlider = new BSlider(frame, "fSpeedSlider", "Speed",
			new BMessage('SPEE'), 1, 20, B_TRIANGLE_THUMB);
	view->AddChild(fSpeedSlider);
	fSpeedSlider->SetHashMarks(B_HASH_MARKS_TOP);
	fSpeedSlider->SetHashMarkCount(16);
	fSpeedSlider->SetValue(SPEED*60.0);
	fSpeedSlider->SetEnabled(true);		
	fSpeedSlider->SetTarget(this);	

	fSpeedSlider->ResizeToPreferred();
	frame.top = fSpeedSlider->Frame().bottom+15;
	
	view->AddChild(new BStringView(frame, B_EMPTY_STRING, "(c) 2009 Jan Kadlec (Řrřola), (c) 2010-13 3dEyes**"));	
}


status_t
Symetrie::SaveState(BMessage* into) const
{
	status_t ret = B_BAD_VALUE;
	if (into) {
		ret = into->AddFloat("Speed", SPEED);
		if (ret >= B_OK)
			ret = into->AddBool("Corners", CORNERS);
		if (ret >= B_OK)
			ret = into->AddBool("BigPoints", BIG_POINTS);
	}
	return ret;
}


void
Symetrie::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case 'CORN':
			CORNERS = fCorners->Value();
			break;
		case 'BIGP':
			BIG_POINTS = fBigPoints->Value();
			break;
		case 'SPEE':
			SPEED = fSpeedSlider->Value()/60.0;
			break;
		default:
			BHandler::MessageReceived(message);
	}
}

status_t 
Symetrie::StartSaver(BView *view, bool preview)
{
	SetTickSize(35000);
	fb = new FBView(view->Bounds() ,WIDTH, HEIGHT);
	view->AddChild(fb);	
	init(fb);
	return B_OK;
}


void
Symetrie::Draw(BView *view, int32)
{	
	renderer(fb);
}
