/* 
 * The MIT License (MIT)
 * 
 * Copyright 2019, Panagiotis Vasilopoulos
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "WorkInMotion.h"

#include <math.h>
#include <stdlib.h>

#include <Alignment.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <Slider.h>
#include <String.h>
#include <StringView.h>
#include <Window.h>
#include <View.h>


static const BString kName = "Work in Motion";
static const BString kAuthor = "Panagiotis Vasilopoulos";

extern "C" BScreenSaver*
instantiate_screen_saver(BMessage* msg, image_id id)
{
	return new WorkInMotion(msg, id);
}

WorkInMotion::WorkInMotion(BMessage *msg, image_id image)
	: BScreenSaver(msg, image)
{
	rBackground = 0;
	gBackground = 0;
	bBackground = 0;
	aBackground = 255;

	rCircle = 255;
	gCircle = 255;
	bCircle = 255;
	aCircle = 255;

	maxAbsIncreaseX = 2;
	maxAbsIncreaseY = 2;
	circleDistance = 75;

	penDecrease = 1.5;
}

WorkInMotion::~WorkInMotion()
{

}

void WorkInMotion::StartConfig(BView *view)
{
	BWindow* win = view->Window();

	if (win)
		win->AddHandler(this);

	BStringView* name = new BStringView("name", "Work In Motion");
	BStringView* author = new BStringView("author", "© Panagiotis Vasilopoulos");
	name->SetFont(be_bold_font);

	BLayoutBuilder::Group<>(view, B_VERTICAL, B_USE_ITEM_SPACING)
		.SetInsets(B_USE_WINDOW_INSETS)
		.SetExplicitAlignment(BAlignment(B_ALIGN_HORIZONTAL_CENTER, B_ALIGN_TOP))
		.AddGroup(B_HORIZONTAL)
			.Add(name)
			.Add(author)
			.AddGlue()
		.End();
}

status_t WorkInMotion::StartSaver(BView* view, bool rev)
{
	_Restart(view);

	return B_OK;
}

void WorkInMotion::Draw(BView* view, int32 frame)
{

	if (fRestartNeeded)
		_Restart(view);

	rect = view->Bounds();
	fWidth = (int) rect.Width() + 1;
	fHeight = (int) rect.Height() + 1;
	fCenter.Set(fWidth / 2, fHeight / 2);

	view->SetLowColor(rBackground, gBackground, bBackground, aBackground);
	view->SetHighColor(rCircle, gCircle, bCircle, aCircle);
		// sin(frame) causes a wobbly effect

	view->FillRect(view->Bounds(), B_SOLID_LOW);

	penSize = sin(frame) * 4 + 25;

	for (int i = 0; (i < fWidth || i < fHeight); i += circleDistance) {		
		/*
		 * i stands for the intercept of the x axis, should
		 * sin(frame) = y = 0
		 *
		 * sin(frame) allows for a repetitive motion that repeats itself
		 * on a specific interval, with the help of a steadily increasing
		 * number.
		 */

		if (!i)
			continue;

		view->SetPenSize(penSize);
		penSize -= penDecrease;

		view->StrokeEllipse(fCenter, \
				sin(frame) * maxAbsIncreaseX + i, \
				sin(frame) * maxAbsIncreaseY + i);
	}
}

void WorkInMotion::_Restart(BView* view)
{
	fRestartNeeded = false;

	Draw(view, 0);
}

void WorkInMotion::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	default:
		BHandler::MessageReceived(msg);	
	}
}

status_t WorkInMotion::SaveState(BMessage *msg) const
{
	return B_OK;
}
