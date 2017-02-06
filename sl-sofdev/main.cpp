#include <slice.h>
#include <slicescroll.h>


void SaveToFile (FILE* file)
{

};
void Save ()
{
	/* Save objects to a file! (TO DO) */
};
void LoadFromFile (FILE* file)
{

};
void Load ()
{
	/* Load objects from a file! (TO DO) */
};


// Properties panel on the left of the screen.
scrScroll* Panel;
void InitPanel ()
{
	slBox* PanelBack = slCreateBox();
	slSetBoxDims(PanelBack,0.7,0,0.2,1,100);
	Panel = scrCreateScroll(PanelBack,24,.015);
};
void QuitPanel ()
{
	scrDestroyScroll(Panel);
};
#define AskSave_Waiting 0
#define AskSave_Save 1
#define AskSave_Discard 2
#define AskSave_Cancel 3
Uint8 AskSaveResult;
void AskSave_SigSave () { AskSaveResult = AskSave_Save; };
void AskSave_SigDiscard () { AskSaveResult = AskSave_Discard; };
void AskSave_SigCancel () { AskSaveResult = AskSave_Cancel; };
Uint8 AskSave ()
{
	/// Gray box over everything else to direct attention to dialog box.
	slBox* gray = slCreateBox();
	gray->backcolor = {255,255,255,0};
	slSetBoxDims(gray,0,0,1,1,15);
	gray->onclick = slDoNothing; // Absorb any clicks that would be on boxes behind this one.

	slBox* dialogbox = slCreateBox();
	slSetBoxDims(dialogbox,0.25,0.4,0.5,0.2,14);
	dialogbox->backcolor = {71,71,71,255};
	dialogbox->bordercolor = {0,0,0,255};

	slBox* dialogtitle = slCreateBox(slRenderText("Do you want to save your work?"));
	slSetBoxDims(dialogtitle,0.05,0.15,0.9,0.2,13);
	slRelBoxDims(dialogtitle,dialogbox);

	slBox* savebutton = slCreateBox(slRenderText("Save"));
	slSetBoxDims(savebutton,0.15,0.65,0.2,0.2,13);
	slRelBoxDims(savebutton,dialogbox);
	savebutton->bordercolor = {191,191,191,255};
	savebutton->hoverable = true;
	savebutton->hoverbackcolor = {0,0,0,63};
	savebutton->hoverbordercolor = {255,255,255,255};
	savebutton->onclick = AskSave_SigSave;

	slBox* discardbutton = slCreateBox(slRenderText("Discard"));
	slSetBoxDims(discardbutton,0.4,0.65,0.2,0.2,13);
	slRelBoxDims(discardbutton,dialogbox);
	discardbutton->bordercolor = {191,191,191,255};
	discardbutton->hoverable = true;
	discardbutton->hoverbackcolor = {0,0,0,63};
	discardbutton->hoverbordercolor = {255,255,255,255};
	discardbutton->onclick = AskSave_SigDiscard;

	slBox* cancelbutton = slCreateBox(slRenderText("Cancel"));
	slSetBoxDims(cancelbutton,0.65,0.65,0.2,0.2,13);
	slRelBoxDims(cancelbutton,dialogbox);
	cancelbutton->bordercolor = {191,191,191,255};
	cancelbutton->hoverable = true;
	cancelbutton->hoverbackcolor = {0,0,0,63};
	cancelbutton->hoverbordercolor = {255,255,255,255};
	cancelbutton->onclick = AskSave_SigCancel;

	AskSaveResult = AskSave_Waiting;
	slScalar graybox_opacity = 0; // Initial capacity of gray box.
	while (AskSaveResult == AskSave_Waiting)
	{
		graybox_opacity += (slGetDelta() * 0.625) / 0.375; // Reach final opacity after 0.375 seconds.
		if (graybox_opacity > 0.625) graybox_opacity = 0.625; // Final opacity of gray box.
		gray->backcolor.a = slClamp255(graybox_opacity);
		slCycle(); // Continue rendering and processing input while user makes a choice.
	};

	// Now clean up these objects since we are done with them.
	slDestroyBox(gray);
	slDestroyBox(dialogbox);
	slDestroyBox(dialogtitle);
	slDestroyBox(savebutton);
	slDestroyBox(discardbutton);
	slDestroyBox(cancelbutton);
};
int main ()
{
	slInit();
	/// Unlike a game, this is a desktop application so we will just
	/// hard-code settings that would otherwise be in an options menu.
	slSetVSync(false);
	slSetFullscreen(false);
	/// We will also keep track of whether the window was maximized, etc

	InitPanel();

	while (true)
	{
		slCycle();

		if (slGetExitReq())
		{
			AskSave();
			switch (AskSaveResult)
			{
				case AskSave_Save: Save();
				case AskSave_Discard: goto CloseApp;

				case AskSave_Cancel: slRejectExit();
			};
		};
	};

	CloseApp:

	QuitPanel();

	slQuit();
};
