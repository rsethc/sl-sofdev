#include <slice.h>
#include <slicescroll.h>

#include "asksave.h"
#include "grid.h"

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
	slSetBoxDims(PanelBack,0,0,0.2,1,100);
	Panel = scrCreateScroll(PanelBack,24,.012);
	/// Override defaults set by slice-scroll, for stylistic purposes.
	PanelBack->backcolor = {175,175,175,255};
	Panel->bar->behind->backcolor = {145,145,145,255};
	Panel->bar->mark->backcolor = {111,111,111,255};
	Panel->bar->mark->hoverbackcolor = {95,95,95,255};
	Panel->upbutton->backcolor = {111,111,111,255};
	Panel->upbutton->hoverbackcolor = {95,95,95,255};
	Panel->downbutton->backcolor = {111,111,111,255};
	Panel->downbutton->hoverbackcolor = {95,95,95,255};
};
void QuitPanel ()
{
	scrDestroyScroll(Panel);
};


int main ()
{
	slInit(); // Initialize the engine before doing ANYTHING else!

	/// Unlike a game, this is a desktop application so we will just
	/// force these settings to hardcoded values.
	slSetVSync(true); // No need to draw more frames than will ever be seen.
	slSetFullscreen(false); // Fullscreen mode is not needed for this app.

	// Initialize GUI
	InitPanel();

	glClearColor(.95,.95,.95,0); // Background color is 95% of solid white. Alpha doesn't matter.
	slSetCamWH_Mode(slCamWH_CutArea); // Show no blank space!
	slSetCustomDrawStage_Back(DrawGrid); // The engine will call this function before drawing anything, so it's "behind" other things visually.

	while (true)
	{
		slCycle();

		if (slGetExitReq())
		{
			switch (AskSave())
			{
				case AskSave_Save: Save();
				case AskSave_Discard: goto CloseApp;

				case AskSave_Cancel: slRejectExit();
			};
		};
	};

	CloseApp:

	// Clean up GUI
	QuitPanel();

	slQuit(); // Deinitialize the engine LAST because this call will close the program!
};
