#include <slice.h>

/// TO DO: Options in the user interface for enable/disable dots & grid.
/// TO DO: Menu to customize colors such as those for grid & dots?
/// TO DO: allow modification of Grid Interval, perhaps with multiple profiles for zoomed-in vs zoomed-out, etc
bool GridEnabled = true;
bool DotsEnabled = true;
SDL_Color GridColor = {191,191,191,255};
SDL_Color DotsColor = {31,31,31,255};
slScalar GridInterval = 0.1;
/// TO DO: Bind scroll wheel to zooming in & out (unless the mouse is over some UI object).
/// TO DO: Pan when mouse is hovered around edges of the canvas
/// TO DO: Pan when mouse is hovered

void DrawGrid ()
{
	if (!GridEnabled && !DotsEnabled) return; /// return early if these are both disabled

	slLoadWorldOrtho();
	slSetDrawColor(GridColor);

	/// Get information about the current viewport
	slScalar cam_x,cam_y,cam_w,cam_h;
	slGetCamXY(&cam_x,&cam_y);
	slGetCamWH(&cam_w,&cam_h);
	cam_w *= .5; cam_y *= .5; // Half w,h: distances from center to edge of screen

	/// starting positions for iteration
	slScalar start_x = ceil((cam_x - cam_w) / GridInterval) * GridInterval;
	slScalar start_y = ceil((cam_y - cam_h) / GridInterval) * GridInterval;

	/// screen boundaries
	slScalar top = cam_y + cam_h;
	slScalar right = cam_x + cam_w;

	slScalar x,y;

	if (GridEnabled)
	{
		// only need to calculate these if we're drawing grid, not needed for dots
		slScalar bottom = cam_y - cam_h;
		slScalar left = cam_x - cam_w;

		slSetDrawColor(GridColor);
		for (x = start_x; x < right; x += GridInterval) slDrawLine(x,bottom,x,top); // Vertical lines: common x-coordinate, y goes across whole screen
		for (y = start_y; y < top; y += GridInterval) slDrawLine(left,y,right,y); // Horizontal lines: common y-coordinate, x goes across whole screen
	};

	if (DotsEnabled)
	{
		slSetDrawColor(DotsColor);
		for (y = start_y; y < top; y += GridInterval) for (x = start_x; x < right; x += GridInterval) slDrawPoint(x,y);
	};
};
