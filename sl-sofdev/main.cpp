#include <slice.h>
#include <slicescroll.h>
scrScroll* Panel;
void InitPanel ()
{
	slBox* PanelBack = slCreateBox();
	slSetBoxDims(PanelBack,0,0,0.2,1,100);
	Panel = scrCreateScroll(PanelBack,24,.015);
};
void QuitPanel ()
{
	scrDestroyScroll(Panel);
};
void AskQuit ()
{
	/// Gray box over everything else to direct attention to dialog box.
	slBox* gray = slCreateBox();
	gray->backcolor = {191,191,191,127};
	slSetBoxDims(gray,0,0,1,1,
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
