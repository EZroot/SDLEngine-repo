#include "GParallaxScroller.h"
#include "ETexture.h"
#include "ELog.h"

GParallaxScroller::GParallaxScroller(SDL_Window * window, SDL_Renderer * renderer)
{
	base = new GBackground((char*)"Resources/bkgd_0.png", 2000, 0, 0,window, renderer);
	para1 = new GBackground((char*)"Resources/bkgd_1.png", 2000, 0.1f, 30, window, renderer);
	para2 = new GBackground((char*)"Resources/bkgd_2.png", 2000, 0.2f, 50, window, renderer);
	para3 = new GBackground((char*)"Resources/bkgd_3.png", 2000, 0.2f, 80, window, renderer);
	para4 = new GBackground((char*)"Resources/bkgd_4.png", 2000, 0.2f, 100, window, renderer);

	wideScreen = new GBackground((char*)"Resources/widescreen.png", 800, 0, 0, window, renderer);
}

GParallaxScroller::~GParallaxScroller()
{
	delete base;
	delete para1;
	delete para2;
	delete para3;
	delete para4;
	delete wideScreen;

	base = nullptr;
	para1 = nullptr;
	para2 = nullptr;
	para3 = nullptr;
	para4 = nullptr;
	wideScreen = nullptr;
}

void GParallaxScroller::Update(float updateStep)
{
	para1->Update(updateStep);
	para2->Update(updateStep);
	para3->Update(updateStep);
	para4->Update(updateStep);

}

void GParallaxScroller::Render(SDL_Renderer * renderer)
{
	base->Render(renderer);
	para1->Render(renderer);
	para2->Render(renderer);
	para3->Render(renderer);
	para4->Render(renderer);
	wideScreen->Render(renderer);
}
