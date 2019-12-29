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

#ifndef WORKINMOTION_H
#define WORKINMOTION_H

#include <Handler.h>
#include <ScreenSaver.h>
#include <ObjectList.h>
#include <config/types.h>

class WorkInMotion : public BScreenSaver, public BHandler {
public:
						WorkInMotion(BMessage* archive, image_id id);
						~WorkInMotion();

	virtual void			StartConfig(BView* view);

	virtual status_t		StartSaver(BView* view, bool preview);
	virtual status_t		SaveState(BMessage* msg) const;
	virtual void			Draw(BView* view, int32 frame);

	virtual void			MessageReceived(BMessage* msg);

private:
	void				_Restart(BView* view);

	bool				fRestartNeeded;

	__haiku_std_uint8		rBackground;
	__haiku_std_uint8		gBackground;
	__haiku_std_uint8		bBackground;
	__haiku_std_uint8		aBackground;

	__haiku_std_uint8		rCircle;
	__haiku_std_uint8		gCircle;
	__haiku_std_uint8		bCircle;
	__haiku_std_uint8		aCircle;

	int		fWidth;
	int		fHeight;
	BPoint		fCenter;

	int		circleDistance;
	int		maxAbsIncreaseX;
	int		maxAbsIncreaseY;

	int		penSize;
	int32		penDecrease;

	BRect		rect;
	BRegion		*screen;
};

#endif
