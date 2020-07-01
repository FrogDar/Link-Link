/*****************************************************************//**
 * \file   Control.cpp
 * \brief  Control��Ķ���
 * Control��ĺ�������
 * \author FrogDar
 * \date   June 2020
 *********************************************************************/
#include "Control.h"
#include "StartScene.h"
#include "GameScene.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <deque>
namespace fs = std::filesystem;
extern Control* now;
bool hasEnabledAutoMode = false;
int autoSpeed[4] = { 1, 5, 10, 20 };
int autoSpeedIndicator = 0;

/**
 * Control����вι��캯��.
 * ����һ��width*height��С�Ĵ���
 * \param _width ���ڿ��
 * \param _height ���ڸ߶�
 */
Control::Control(int _width, int _height) :width{ _width }, height{ _height }, scene{ nullptr }
{
	/*��ʼ�����������*/
	std::srand((int)time(NULL));
	/*��ʼ��SDL��Ϣ*/
	SDL_Init(SDL_INIT_EVERYTHING);
	/*��ʼ��������Ϣ*/
	window = SDL_CreateWindow("Link Up", 100, 100, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Mix_Init(127);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 2048);
	/*��ʼ��SDL��������չ*/
	TTF_Init();
}

/**
 * Control����޲ι��캯��.
 *
 */
Control::Control() : Control{ 1366, 768 }
{
}

/**
 * Control�����������.
 * ����ָ������
 *
 */
Control::~Control()
{
	for (auto i : Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	delete scene;
	scene = nullptr;
}

/**
 * ��ѭ��.
 * ��������߼������岿��
 */
void Control::mainLoop()
{
	/*���س�����Դ�ļ���ͼƬ����Ƶ*/
	Initmywavs(fs::path{ "./Sound" });
	Initmypngs(fs::path{ "./Pic" });

	/*��ʼ����ΪStartScene*/
	this->scene = new StartScene();

	/*�û��Ƿ�ѡ���˳�*/
	bool quit = false;
	/*�û��������¼�*/
	SDL_Event e;

	std::deque<SDL_Keycode> keyCodeBuffer;

	int cnt = 0;

	while (!quit)
	{
		/*��¼��ǰʱ�䣨Ϊ�˿���֡��*/
		Uint64 start = SDL_GetPerformanceCounter();

		cnt = 0;
		while (SDL_PollEvent(&e) != 0 && ++cnt < 20)
		{
			//�û�ѡ���˳�
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				scene->onMouse(e.button.x, e.button.y);
			}

			if (e.type == SDL_KEYDOWN) {
				// Auto mode /////
				keyCodeBuffer.push_back(e.key.keysym.sym);
				if (keyCodeBuffer.size() > 4)keyCodeBuffer.pop_front();
				if (keyCodeBuffer.size() == 4
					&& keyCodeBuffer[0] == SDLK_a
					&& keyCodeBuffer[1] == SDLK_u
					&& keyCodeBuffer[2] == SDLK_t
					&& keyCodeBuffer[3] == SDLK_o
					)
				{
					hasEnabledAutoMode = !hasEnabledAutoMode;
				}
				if (keyCodeBuffer.size() > 3
					&& keyCodeBuffer[3] == SDLK_s)
				{
					if ((++autoSpeedIndicator) >= sizeof(autoSpeed))
					{
						autoSpeedIndicator = 0;
					}
				}
			}
		}

		SDL_RenderClear(renderer);
		scene->update();
		SDL_RenderPresent(renderer);

		/*Ϊ����֡��Ϊ60���ֶ�delayʣ���ʱ��*/
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		/*16.666fԼ����60fps*/
		if (elapsedMS < 16.666f)
			SDL_Delay(static_cast<int>(floor(16.666f - elapsedMS)));
	}
}

/**
 * ��ȡControl�൱ǰ��Renderer.
 *
 * \return Renderer��ָ��
 */
SDL_Renderer* Control::getRenderer()
{
	return renderer;
}

/**
 * ����һ��ͼƬ.
 *
 * \param path ͼƬ��·��
 * \param x ���Ƶ�ĺ�����
 * \param y ���Ƶ��������
 * \param width ��Ҫ���Ƶ�ͼƬ���
 * \param height ��Ҫ���Ƶ�ͼƬ�ĸ߶�
 */
void Control::putImage(std::string path, int x, int y, int width, int height)
{
	if (Textures[path] == nullptr)
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		Textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
	auto& texture = Textures[path];
	SDL_Rect box = { x, y, width, height };
	SDL_RenderCopy(renderer, texture, NULL, &box);
}

/**
 * ��������path��cnt��.
 * ֻ֧��wav��ʽ������
 * \param channel ���ֲ��ŵ�Ƶ��
 * \param path ���ֵ�·��
 * \param cnt ���Ŵ�����-1Ϊ��������
 */
void Control::playSound(int channel, std::string path, int cnt)
{
	Mix_PlayChannel(channel, Sounds[path], 0);
}
void Control::addVolume(int channel) {
	if (1 == channel) {
		volm1 += 0.25;
		if (volm1 > 1)volm1 = 1;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel) {
		volm2 += 0.25;
		if (volm2 > 1)volm2 = 1;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}
void Control::decVolume(int channel) {
	if (1 == channel) {
		volm1 -= 0.25;
		if (volm1 < 0)volm1 = 0;
		Mix_Volume(channel, (int)(volm1 * MIX_MAX_VOLUME));
	}
	if (2 == channel) {
		volm2 -= 0.25;
		if (volm2 < 0)volm2 = 0;
		Mix_Volume(channel, (int)(volm2 * MIX_MAX_VOLUME));
	}
}
double Control::getVolm1() {
	return volm1;
}
double Control::getVolm2() {
	return volm2;
}
/**
 * ��ȡ�����.
 *
 * \return һ�������
 */
int Control::getRand() { return std::rand(); }

/**
 * ���������Ϣ.
 * ��(x,y)������ֺ�Ϊsize������c
 * \param x ������
 * \param y ������
 * \param c �������
 * \param size �ֺŴ�С
 */
void Control::xyprintf(int x, int y, const char* c, int size = 20)
{
	if (Fonts.find(size) == Fonts.end())
	{
		Fonts[size] = TTF_OpenFont("./MyFont.ttf", size);
	}
	auto& font = Fonts[size];
	SDL_Color color = { 2, 2, 2, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, c, color);
	SDL_Rect box = { x, y, surface->w, surface->h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &box);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

/**
 * ����png��Դ.
 * �Զ��ݹ������cpp17��׼
 * \param strPath ���ص��ļ���
 */
void Control::Initmypngs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))
		{
			if (fFiename != "." && fFiename != "..")
				Initmypngs(fp);
		}
		else
			if (fs::is_regular_file(fp))
				now->putImage(fp.generic_string().c_str(), 0, 0, 100, 100);
	}
}

/**
 * ����wav��Դ.
 * �Զ��ݹ������cpp17��׼
 * \param strPath ���ص��ļ���
 */
void Control::Initmywavs(fs::path strPath)
{
	for (auto& fe : fs::directory_iterator(strPath))
	{
		auto fp = fe.path();
		auto fFiename = fp.filename();
		if (fs::is_directory(fe))
		{
			if (fFiename != "." && fFiename != "..")
				Initmywavs(fp);
		}
		else
			if (fs::is_regular_file(fp)) {
				Sounds[fp.generic_string()] = Mix_LoadWAV(fp.generic_string().c_str());
			}
	}
}