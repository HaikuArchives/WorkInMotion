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

/*
static const BString kName = "Work in Motion";
static const BString kAuthor = "Panagiotis Vasilopoulos";

static const int32 K_RED_BACKGROUND = 'bgcr';
static const int32 K_GREEN_BACKGROUND = 'bgcg';
static const int32 K_BLUE_BACKGROUND = 'bgcb';
static const int32 K_ALPHA_BACKGROUND = 'bgca';

static const int32 K_RED_CIRCLE = 'crcr';
static const int32 K_GREEN_CIRCLE = 'crcg';
static const int32 K_BLUE_CIRCLE = 'crcb';
static const int32 K_ALPHA_CIRCLE = 'crca';

static const int32 K_PEN_DECREASE = 'pend';
*/

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
        BSlider*	rBackgroundSlider;
        BSlider*	gBackgroundSlider;
        BSlider*	bBackgroundSlider;
        BSlider*	aBackgroundSlider;

        BSlider*	rCircleSlider;
        BSlider*	gCircleSlider;
        BSlider*	bCircleSlider;
        BSlider*	aCircleSlider;

	BSlider*	penDecreaseSlider;

	BWindow* win = view->Window();

	if (win)
		win->AddHandler(this);

	BStringView* name = new BStringView("name", "Work In Motion");
	BStringView* author = new BStringView("author", "© Panagiotis Vasilopoulos");
	name->SetFont(be_bold_font);
/*
	BStringView* backgroundColorLabel = new BStringView("backgroundColor", "Background Color");

	rBackgroundSlider = new BSlider("Background Red", "", new BMessage(K_RED_BACKGROUND), 0, 255, B_HORIZONTAL);
	rBackgroundSlider->SetValue(rBackground);
	rBackgroundSlider->SetTarget(this);
	rBackgroundSlider->SetLimitLabels("less red", "more red");

	gBackgroundSlider = new BSlider("Background Green", "", new BMessage(K_GREEN_BACKGROUND), 0, 255, B_HORIZONTAL);
	gBackgroundSlider->SetValue(gBackground);
	gBackgroundSlider->SetTarget(this);
	gBackgroundSlider->SetLimitLabels("less green", "more green");

	bBackgroundSlider = new BSlider("Background Blue", "", new BMessage(K_BLUE_BACKGROUND), 0, 255, B_HORIZONTAL);
	bBackgroundSlider->SetValue(bBackground);
	bBackgroundSlider->SetTarget(this);
	bBackgroundSlider->SetLimitLabels("less blue", "more blue");

	aBackgroundSlider = new BSlider("Background Alpha", "", new BMessage(K_ALPHA_BACKGROUND), 0, 255, B_HORIZONTAL);
	aBackgroundSlider->SetValue(aBackground);
	aBackgroundSlider->SetTarget(this);
	aBackgroundSlider->SetLimitLabels("less visible", "more visible");

	BStringView* circleColorLabel = new BStringView("circleColor", "Circle Color");

	rCircleSlider = new BSlider("Circle Red", "", new BMessage(K_RED_CIRCLE), 0, 255, B_HORIZONTAL);
	rCircleSlider->SetValue(rCircle);
	rCircleSlider->SetTarget(this);
	rCircleSlider->SetLimitLabels("less red", "more red");

	gCircleSlider = new BSlider("Circle Blue", "", new BMessage(K_BLUE_CIRCLE), 0, 255, B_HORIZONTAL);
	gCircleSlider->SetValue(gCircle);
	gCircleSlider->SetTarget(this);
	gCircleSlider->SetLimitLabels("less green", "more green");

	bCircleSlider = new BSlider("Circle Green", "", new BMessage(K_GREEN_CIRCLE), 0, 255, B_HORIZONTAL);
	bCircleSlider->SetValue(bCircle);
	bCircleSlider->SetTarget(this);
	bCircleSlider->SetLimitLabels("less blue", "more blue");

	aCircleSlider = new BSlider("Circle Alpha", "", new BMessage(K_ALPHA_CIRCLE), 0, 255, B_HORIZONTAL);
	aCircleSlider->SetValue(aCircle);
	aCircleSlider->SetTarget(this);
	aCircleSlider->SetLimitLabels("less visible", "more visible");

//	BStringView* circleSettingsLabel = new BStringView("circleSettings", "Circle Settings");

	BStringView* penSettingsLabel = new BStringView("circleColor", "Pen Decrease");

	penDecreaseSlider = new BSlider("Pen Decrease", "", new BMessage(K_PEN_DECREASE), 1, 30, B_HORIZONTAL);
	penDecreaseSlider->SetValue(penDecrease * -1);
	penDecreaseSlider->SetTarget(this);
	penDecreaseSlider->SetLimitLabels("a bit", "a lot");
*/
	BLayoutBuilder::Group<>(view, B_VERTICAL, B_USE_ITEM_SPACING)
		.SetInsets(B_USE_WINDOW_INSETS)
		.SetExplicitAlignment(BAlignment(B_ALIGN_HORIZONTAL_CENTER, B_ALIGN_TOP))
		.AddGroup(B_HORIZONTAL)
			.Add(name)
			.Add(author)
			.AddGlue()
		.End()
/*
		.AddGlue()
		.AddGroup(B_VERTICAL)
			.Add(circleColorLabel)
			.Add(rCircleSlider)
			.Add(bCircleSlider)
			.Add(gCircleSlider)
			.Add(aCircleSlider)
			.AddGlue()
		.End()
		.AddGlue()
		.AddGroup(B_VERTICAL)
			.Add(backgroundColorLabel)
			.Add(rBackgroundSlider)
			.Add(bBackgroundSlider)
			.Add(gBackgroundSlider)
			.Add(aBackgroundSlider)
			.AddGlue()
		.End()
		.AddGroup(B_VERTICAL)
			.Add(penSettingsLabel)
			.Add(penDecreaseSlider)
		.End()*/;
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

	for (int i = 0; ( i < fWidth || i < fHeight); i += circleDistance) {
		
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
/*	case K_RED_BACKGROUND:
		rBackground = msg->GetInt8("be:value", rBackground);
		fRestartNeeded = true;
		break;
	case K_GREEN_BACKGROUND:
		gBackground = msg->GetInt8("be:value", gBackground);
		fRestartNeeded = true;
		break;
	case K_BLUE_BACKGROUND:
		bBackground = msg->GetInt8("be:value", bBackground);
		fRestartNeeded = true;
		break;
	case K_ALPHA_BACKGROUND:
		aBackground = msg->GetInt8("be:value", aBackground);
		fRestartNeeded = true;
		break;
	case K_RED_CIRCLE:
		rCircle = msg->GetInt8("be:value", rCircle);
		fRestartNeeded = true;
		break;
	case K_GREEN_CIRCLE:
		gCircle = msg->GetInt8("be:value", gCircle);
		fRestartNeeded = true;
		break;
	case K_BLUE_CIRCLE:
		bCircle = msg->GetInt8("be:value", bCircle);
		fRestartNeeded = true;
		break;
	case K_ALPHA_CIRCLE:
		aCircle = msg->GetInt8("be:value", aCircle);
		fRestartNeeded = true;
		break;
	case K_PEN_DECREASE:
		penDecrease = msg->GetInt32("be:value", penDecrease);
		fRestartNeeded = true;
		break;
*/	default:
		BHandler::MessageReceived(msg);	
	}
}

status_t WorkInMotion::SaveState(BMessage *msg) const
{
	return B_OK;
}
