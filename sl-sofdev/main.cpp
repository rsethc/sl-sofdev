#include <slice.h>
#include <slicescroll.h>

#include "asksave.h"

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
	Panel = scrCreateScroll(PanelBack,24,.015);
	PanelBack->backcolor = {239,239,239,255};
};
void QuitPanel ()
{
	scrDestroyScroll(Panel);
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
			switch (AskSave())
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
