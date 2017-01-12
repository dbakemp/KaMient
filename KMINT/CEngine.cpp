#include "CEngine.h"
#include "CDrawManager.h"
#include "CInputManager.h"
#include "CEntityManager.h"
#include "CTextureManager.h"
#include "CDebugLogger.h"
#include <time.h>
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "CEntityBee.h"
#include "CEntityMapBackground.h"
#include "CGraph.h"
#include "CEntityImker.h"
#include "CDebugLogger.h"
#include <math.h>
#include "CIntegerHelper.h"
#include <algorithm>

CEngine::CEngine()
{
	windowHeight = 600;
	windowWidth = 600;

	drawManager = new CDrawManager(this);
	inputManager = new CInputManager();
	entityManager = new CEntityManager();
	textureManager = new CTextureManager(this);

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("KMINT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Surface* icon = IMG_Load("Resources/Images/favicon.ico");
	SDL_SetWindowIcon(window, icon);
	
	background = nullptr;
	graph = nullptr;
	imker = nullptr;

	genetic = false;

	scale = 16.0f;

	Start();
	
}

CEngine::~CEngine()
{
	delete entityManager;
	delete drawManager;
	delete inputManager;
	delete textureManager;

	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void CEngine::Start()
{

	if (!genetic) {
		entityManager->Clear();
		caughtBees.clear();
		beeList.clear();

		for (int i = 0; i < 100; i++) {
			beeList.push_back(new CEntityBee(this));
		}
	}
	else {
		struct GeneticStruct {
			std::string dna;
			int value;
			double fraction;
			double expection;
		};

		std::vector<GeneticStruct*> geneticVector;

		int totalTicks = 0;
		for (CEntityBee* bee : caughtBees) {
			totalTicks += bee->ticks;
		}

		for (CEntityBee* bee : caughtBees) {
			GeneticStruct* gStruct = new GeneticStruct();
			gStruct->dna = bee->GetBeeGeneticString();
			gStruct->value = bee->ticks;
			gStruct->fraction = (double)gStruct->value / (double)totalTicks;
			gStruct->expection = (double)caughtBees.size()*(double)gStruct->fraction;

			geneticVector.push_back(gStruct);
		}

		struct ParticipateGenetics {
			std::string dna;
		};

		std::vector<ParticipateGenetics*> participationVector;

		for (GeneticStruct* gStruct : geneticVector) {
			int participation = std::floor(gStruct->expection / 1);
			gStruct->expection = std::fmod(gStruct->expection, 1);

			ParticipateGenetics* partGenetic = new ParticipateGenetics();
			partGenetic->dna = gStruct->dna;

			for (int i = 0; i < participation; i++) {
				participationVector.push_back(partGenetic);
			}
		}

		double maxExpect = 0;
		for (GeneticStruct* gStruct : geneticVector) {
			maxExpect += gStruct->expection;
		}

		maxExpect *= 10000;

		while (participationVector.size() < 100) {
			double random = ((double)CIntegerHelper::GetRandomIntBetween(0, maxExpect) / 10000);

			int stateInt = 0;

			for (int i = 0; i < geneticVector.size(); i++) {
				double totalChance = 0;
				for (int o = i; o >= 0; o--) {
					totalChance += geneticVector[i]->expection;
				}
				if (random <= totalChance) {
					ParticipateGenetics* partGenetic = new ParticipateGenetics();
					partGenetic->dna = geneticVector.at(i)->dna;
					participationVector.push_back(partGenetic);
					break;
				}
			}
		}


		std::vector<ParticipateGenetics*> participationCrossVector;

		for (ParticipateGenetics* partGen : participationVector) {
			ParticipateGenetics* partGenetic = new ParticipateGenetics();
			partGenetic->dna = partGen->dna;
			participationCrossVector.push_back(partGenetic);
		}

		std::random_shuffle(participationCrossVector.begin(), participationCrossVector.end());

		entityManager->Clear();
		caughtBees.clear();
		beeList.clear();

		for (int i = 0; i < participationVector.size(); i++) {
			std::string newDna = "";
			int split = CIntegerHelper::GetRandomIntBetween(0, participationVector[i]->dna.length());
			newDna += participationVector[i]->dna.substr(0, split);
			newDna += participationCrossVector[i]->dna.substr(split, participationVector[i]->dna.length()-split);

			int mutation = CIntegerHelper::GetRandomIntBetween(0, 100);
			if (mutation == 1) {
				int mutationPos = CIntegerHelper::GetRandomIntBetween(0, newDna.length()-1);
				if (newDna[mutationPos] == '1') {
					newDna[mutationPos] = '0';
				}
				else {
					newDna[mutationPos] = '1';
				}
			}

			beeList.push_back(new CEntityBee(this, newDna));
		}
	}

	background = new CEntityMapBackground(this);

	delete graph;
	graph = new CGraph(this);

	CEntityVertex* vertex103 = new CEntityVertex(this, 28, 31);
	graph->AddVertex(vertex103);
	CEntityVertex* vertex104 = new CEntityVertex(this, 60, 49);
	graph->AddVertex(vertex104);
	CEntityVertex* vertex105 = new CEntityVertex(this, 15, 76);
	graph->AddVertex(vertex105);
	CEntityVertex* vertex106 = new CEntityVertex(this, 39, 96);
	graph->AddVertex(vertex106);
	CEntityVertex* vertex107 = new CEntityVertex(this, 141, 97);
	graph->AddVertex(vertex107);
	CEntityVertex* vertex108 = new CEntityVertex(this, 129, 30);
	graph->AddVertex(vertex108);
	CEntityVertex* vertex109 = new CEntityVertex(this, 186, 64);
	graph->AddVertex(vertex109);
	CEntityVertex* vertex110 = new CEntityVertex(this, 201, 15);
	graph->AddVertex(vertex110);
	CEntityVertex* vertex111 = new CEntityVertex(this, 258, 49);
	graph->AddVertex(vertex111);
	CEntityVertex* vertex112 = new CEntityVertex(this, 213, 78);
	graph->AddVertex(vertex112);
	CEntityVertex* vertex113 = new CEntityVertex(this, 241, 94);
	graph->AddVertex(vertex113);
	CEntityVertex* vertex114 = new CEntityVertex(this, 216, 106);
	graph->AddVertex(vertex114);
	CEntityVertex* vertex115 = new CEntityVertex(this, 312, 157);
	graph->AddVertex(vertex115);
	CEntityVertex* vertex116 = new CEntityVertex(this, 289, 172);
	graph->AddVertex(vertex116);
	CEntityVertex* vertex117 = new CEntityVertex(this, 444, 235);
	graph->AddVertex(vertex117);
	CEntityVertex* vertex118 = new CEntityVertex(this, 487, 202);
	graph->AddVertex(vertex118);
	CEntityVertex* vertex119 = new CEntityVertex(this, 457, 186);
	graph->AddVertex(vertex119);
	CEntityVertex* vertex120 = new CEntityVertex(this, 483, 169);
	graph->AddVertex(vertex120);
	CEntityVertex* vertex121 = new CEntityVertex(this, 526, 138);
	graph->AddVertex(vertex121);
	CEntityVertex* vertex122 = new CEntityVertex(this, 556, 156);
	graph->AddVertex(vertex122);
	CEntityVertex* vertex123 = new CEntityVertex(this, 435, 96);
	graph->AddVertex(vertex123);
	CEntityVertex* vertex124 = new CEntityVertex(this, 408, 82);
	graph->AddVertex(vertex124);
	CEntityVertex* vertex125 = new CEntityVertex(this, 488, 61);
	graph->AddVertex(vertex125);
	CEntityVertex* vertex126 = new CEntityVertex(this, 399, 121);
	graph->AddVertex(vertex126);
	CEntityVertex* vertex127 = new CEntityVertex(this, 367, 108);
	graph->AddVertex(vertex127);
	CEntityVertex* vertex128 = new CEntityVertex(this, 346, 122);
	graph->AddVertex(vertex128);
	CEntityVertex* vertex129 = new CEntityVertex(this, 288, 91);
	graph->AddVertex(vertex129);
	CEntityVertex* vertex130 = new CEntityVertex(this, 351, 46);
	graph->AddVertex(vertex130);
	CEntityVertex* vertex131 = new CEntityVertex(this, 301, 15);
	graph->AddVertex(vertex131);
	CEntityVertex* vertex132 = new CEntityVertex(this, 402, 15);
	graph->AddVertex(vertex132);
	CEntityVertex* vertex133 = new CEntityVertex(this, 547, 18);
	graph->AddVertex(vertex133);
	CEntityVertex* vertex134 = new CEntityVertex(this, 531, 33);
	graph->AddVertex(vertex134);
	CEntityVertex* vertex135 = new CEntityVertex(this, 562, 49);
	graph->AddVertex(vertex135);
	CEntityVertex* vertex136 = new CEntityVertex(this, 541, 64);
	graph->AddVertex(vertex136);
	CEntityVertex* vertex137 = new CEntityVertex(this, 567, 79);
	graph->AddVertex(vertex137);
	CEntityVertex* vertex138 = new CEntityVertex(this, 544, 93);
	graph->AddVertex(vertex138);
	CEntityVertex* vertex139 = new CEntityVertex(this, 574, 112);
	graph->AddVertex(vertex139);
	CEntityVertex* vertex140 = new CEntityVertex(this, 568, 220);
	graph->AddVertex(vertex140);
	CEntityVertex* vertex141 = new CEntityVertex(this, 570, 250);
	graph->AddVertex(vertex141);
	CEntityVertex* vertex142 = new CEntityVertex(this, 543, 234);
	graph->AddVertex(vertex142);
	CEntityVertex* vertex143 = new CEntityVertex(this, 499, 264);
	graph->AddVertex(vertex143);
	CEntityVertex* vertex144 = new CEntityVertex(this, 553, 297);
	graph->AddVertex(vertex144);
	CEntityVertex* vertex145 = new CEntityVertex(this, 486, 341);
	graph->AddVertex(vertex145);
	CEntityVertex* vertex146 = new CEntityVertex(this, 430, 310);
	graph->AddVertex(vertex146);
	CEntityVertex* vertex147 = new CEntityVertex(this, 406, 327);
	graph->AddVertex(vertex147);
	CEntityVertex* vertex148 = new CEntityVertex(this, 376, 307);
	graph->AddVertex(vertex148);
	CEntityVertex* vertex149 = new CEntityVertex(this, 331, 345);
	graph->AddVertex(vertex149);
	CEntityVertex* vertex150 = new CEntityVertex(this, 297, 295);
	graph->AddVertex(vertex150);
	CEntityVertex* vertex151 = new CEntityVertex(this, 255, 325);
	graph->AddVertex(vertex151);
	CEntityVertex* vertex152 = new CEntityVertex(this, 274, 312);
	graph->AddVertex(vertex152);
	CEntityVertex* vertex153 = new CEntityVertex(this, 216, 280);
	graph->AddVertex(vertex153);
	CEntityVertex* vertex154 = new CEntityVertex(this, 147, 328);
	graph->AddVertex(vertex154);
	CEntityVertex* vertex155 = new CEntityVertex(this, 264, 393);
	graph->AddVertex(vertex155);
	CEntityVertex* vertex156 = new CEntityVertex(this, 229, 170);
	graph->AddVertex(vertex156);
	CEntityVertex* vertex157 = new CEntityVertex(this, 201, 154);
	graph->AddVertex(vertex157);
	CEntityVertex* vertex158 = new CEntityVertex(this, 178, 174);
	graph->AddVertex(vertex158);
	CEntityVertex* vertex159 = new CEntityVertex(this, 151, 156);
	graph->AddVertex(vertex159);
	CEntityVertex* vertex160 = new CEntityVertex(this, 162, 187);
	graph->AddVertex(vertex160);
	CEntityVertex* vertex161 = new CEntityVertex(this, 135, 201);
	graph->AddVertex(vertex161);
	CEntityVertex* vertex162 = new CEntityVertex(this, 108, 183);
	graph->AddVertex(vertex162);
	CEntityVertex* vertex163 = new CEntityVertex(this, 13, 187);
	graph->AddVertex(vertex163);
	CEntityVertex* vertex164 = new CEntityVertex(this, 144, 267);
	graph->AddVertex(vertex164);
	CEntityVertex* vertex165 = new CEntityVertex(this, 16, 357);
	graph->AddVertex(vertex165);
	CEntityVertex* vertex166 = new CEntityVertex(this, 70, 391);
	graph->AddVertex(vertex166);
	CEntityVertex* vertex167 = new CEntityVertex(this, 40, 411);
	graph->AddVertex(vertex167);
	CEntityVertex* vertex168 = new CEntityVertex(this, 61, 421);
	graph->AddVertex(vertex168);
	CEntityVertex* vertex169 = new CEntityVertex(this, 33, 438);
	graph->AddVertex(vertex169);
	CEntityVertex* vertex170 = new CEntityVertex(this, 63, 450);
	graph->AddVertex(vertex170);
	CEntityVertex* vertex171 = new CEntityVertex(this, 37, 466);
	graph->AddVertex(vertex171);
	CEntityVertex* vertex172 = new CEntityVertex(this, 97, 499);
	graph->AddVertex(vertex172);
	CEntityVertex* vertex173 = new CEntityVertex(this, 36, 544);
	graph->AddVertex(vertex173);
	CEntityVertex* vertex174 = new CEntityVertex(this, 109, 558);
	graph->AddVertex(vertex174);
	CEntityVertex* vertex175 = new CEntityVertex(this, 57, 528);
	graph->AddVertex(vertex175);
	CEntityVertex* vertex176 = new CEntityVertex(this, 156, 528);
	graph->AddVertex(vertex176);
	CEntityVertex* vertex177 = new CEntityVertex(this, 142, 472);
	graph->AddVertex(vertex177);
	CEntityVertex* vertex178 = new CEntityVertex(this, 112, 453);
	graph->AddVertex(vertex178);
	CEntityVertex* vertex179 = new CEntityVertex(this, 181, 402);
	graph->AddVertex(vertex179);
	CEntityVertex* vertex180 = new CEntityVertex(this, 244, 438);
	graph->AddVertex(vertex180);
	CEntityVertex* vertex181 = new CEntityVertex(this, 291, 406);
	graph->AddVertex(vertex181);
	CEntityVertex* vertex182 = new CEntityVertex(this, 387, 373);
	graph->AddVertex(vertex182);
	CEntityVertex* vertex183 = new CEntityVertex(this, 415, 391);
	graph->AddVertex(vertex183);
	CEntityVertex* vertex184 = new CEntityVertex(this, 387, 408);
	graph->AddVertex(vertex184);
	CEntityVertex* vertex185 = new CEntityVertex(this, 316, 451);
	graph->AddVertex(vertex185);
	CEntityVertex* vertex186 = new CEntityVertex(this, 442, 438);
	graph->AddVertex(vertex186);
	CEntityVertex* vertex187 = new CEntityVertex(this, 465, 421);
	graph->AddVertex(vertex187);
	CEntityVertex* vertex188 = new CEntityVertex(this, 487, 400);
	graph->AddVertex(vertex188);
	CEntityVertex* vertex189 = new CEntityVertex(this, 493, 436);
	graph->AddVertex(vertex189);
	CEntityVertex* vertex190 = new CEntityVertex(this, 540, 438);
	graph->AddVertex(vertex190);
	CEntityVertex* vertex191 = new CEntityVertex(this, 571, 424);
	graph->AddVertex(vertex191);
	CEntityVertex* vertex192 = new CEntityVertex(this, 543, 406);
	graph->AddVertex(vertex192);
	CEntityVertex* vertex193 = new CEntityVertex(this, 571, 394);
	graph->AddVertex(vertex193);
	CEntityVertex* vertex194 = new CEntityVertex(this, 538, 372);
	graph->AddVertex(vertex194);
	CEntityVertex* vertex195 = new CEntityVertex(this, 564, 358);
	graph->AddVertex(vertex195);
	CEntityVertex* vertex196 = new CEntityVertex(this, 351, 267);
	graph->AddVertex(vertex196);
	CEntityVertex* vertex197 = new CEntityVertex(this, 373, 249);
	graph->AddVertex(vertex197);
	CEntityVertex* vertex198 = new CEntityVertex(this, 402, 265);
	graph->AddVertex(vertex198);
	CEntityVertex* vertex199 = new CEntityVertex(this, 294, 232);
	graph->AddVertex(vertex199);
	CEntityVertex* vertex200 = new CEntityVertex(this, 316, 219);
	graph->AddVertex(vertex200);
	CEntityVertex* vertex201 = new CEntityVertex(this, 264, 216);
	graph->AddVertex(vertex201);
	CEntityVertex* vertex202 = new CEntityVertex(this, 238, 237);
	graph->AddVertex(vertex202);
	CEntityVertex* vertex203 = new CEntityVertex(this, 211, 219);
	graph->AddVertex(vertex203);
	CEntityVertex* vertex204 = new CEntityVertex(this, 352, 577);
	graph->AddVertex(vertex204);
	CEntityVertex* vertex205 = new CEntityVertex(this, 261, 529);
	graph->AddVertex(vertex205);
	CEntityVertex* vertex206 = new CEntityVertex(this, 303, 499);
	graph->AddVertex(vertex206);
	CEntityVertex* vertex207 = new CEntityVertex(this, 245, 469);
	graph->AddVertex(vertex207);
	CEntityVertex* vertex211 = new CEntityVertex(this, 87, 61);
	graph->AddVertex(vertex211);
	CEntityVertex* vertex306 = new CEntityVertex(this, 345, 468);
	graph->AddVertex(vertex306);
	CEntityVertex* vertex322 = new CEntityVertex(this, 213, 562);
	graph->AddVertex(vertex322);
	CEntityVertex* vertex325 = new CEntityVertex(this, 190, 576);
	graph->AddVertex(vertex325);
	CEntityVertex* vertex327 = new CEntityVertex(this, 384, 555); // Dit is de basis rechtsonder
	graph->baseVertex = vertex327;
	graph->AddVertex(vertex327);
	graph->AddEdge(new CEntityEdge(this, vertex103, vertex104));
	graph->AddEdge(new CEntityEdge(this, vertex106, vertex105));
	graph->AddEdge(new CEntityEdge(this, vertex104, vertex105));
	graph->AddEdge(new CEntityEdge(this, vertex211, vertex104));
	graph->AddEdge(new CEntityEdge(this, vertex211, vertex108));
	graph->AddEdge(new CEntityEdge(this, vertex211, vertex107));
	graph->AddEdge(new CEntityEdge(this, vertex107, vertex109));
	graph->AddEdge(new CEntityEdge(this, vertex109, vertex112));
	graph->AddEdge(new CEntityEdge(this, vertex112, vertex111));
	graph->AddEdge(new CEntityEdge(this, vertex111, vertex111));
	graph->AddEdge(new CEntityEdge(this, vertex113, vertex112));
	graph->AddEdge(new CEntityEdge(this, vertex113, vertex114));
	graph->AddEdge(new CEntityEdge(this, vertex114, vertex115));
	graph->AddEdge(new CEntityEdge(this, vertex115, vertex116));
	graph->AddEdge(new CEntityEdge(this, vertex115, vertex117));
	graph->AddEdge(new CEntityEdge(this, vertex117, vertex198));
	graph->AddEdge(new CEntityEdge(this, vertex198, vertex197));
	graph->AddEdge(new CEntityEdge(this, vertex197, vertex196));
	graph->AddEdge(new CEntityEdge(this, vertex196, vertex199));
	graph->AddEdge(new CEntityEdge(this, vertex199, vertex200));
	graph->AddEdge(new CEntityEdge(this, vertex199, vertex201));
	graph->AddEdge(new CEntityEdge(this, vertex201, vertex202));
	graph->AddEdge(new CEntityEdge(this, vertex202, vertex203));
	graph->AddEdge(new CEntityEdge(this, vertex203, vertex160));
	graph->AddEdge(new CEntityEdge(this, vertex160, vertex158));
	graph->AddEdge(new CEntityEdge(this, vertex158, vertex159));
	graph->AddEdge(new CEntityEdge(this, vertex158, vertex157));
	graph->AddEdge(new CEntityEdge(this, vertex157, vertex156));
	graph->AddEdge(new CEntityEdge(this, vertex160, vertex161));
	graph->AddEdge(new CEntityEdge(this, vertex161, vertex162));
	graph->AddEdge(new CEntityEdge(this, vertex107, vertex163));
	graph->AddEdge(new CEntityEdge(this, vertex163, vertex164));
	graph->AddEdge(new CEntityEdge(this, vertex129, vertex130));
	graph->AddEdge(new CEntityEdge(this, vertex128, vertex129));
	graph->AddEdge(new CEntityEdge(this, vertex128, vertex127));
	graph->AddEdge(new CEntityEdge(this, vertex127, vertex126));
	graph->AddEdge(new CEntityEdge(this, vertex126, vertex123));
	graph->AddEdge(new CEntityEdge(this, vertex123, vertex124));
	graph->AddEdge(new CEntityEdge(this, vertex123, vertex125));
	graph->AddEdge(new CEntityEdge(this, vertex134, vertex135));
	graph->AddEdge(new CEntityEdge(this, vertex135, vertex136));
	graph->AddEdge(new CEntityEdge(this, vertex136, vertex137));
	graph->AddEdge(new CEntityEdge(this, vertex137, vertex138));
	graph->AddEdge(new CEntityEdge(this, vertex138, vertex139));
	graph->AddEdge(new CEntityEdge(this, vertex139, vertex121));
	graph->AddEdge(new CEntityEdge(this, vertex121, vertex122));
	graph->AddEdge(new CEntityEdge(this, vertex121, vertex123));
	graph->AddEdge(new CEntityEdge(this, vertex121, vertex120));
	graph->AddEdge(new CEntityEdge(this, vertex120, vertex119));
	graph->AddEdge(new CEntityEdge(this, vertex119, vertex118));
	graph->AddEdge(new CEntityEdge(this, vertex118, vertex117));
	graph->AddEdge(new CEntityEdge(this, vertex118, vertex142));
	graph->AddEdge(new CEntityEdge(this, vertex142, vertex140));
	graph->AddEdge(new CEntityEdge(this, vertex142, vertex141));
	graph->AddEdge(new CEntityEdge(this, vertex142, vertex143));
	graph->AddEdge(new CEntityEdge(this, vertex143, vertex144));
	graph->AddEdge(new CEntityEdge(this, vertex144, vertex145));
	graph->AddEdge(new CEntityEdge(this, vertex145, vertex146));
	graph->AddEdge(new CEntityEdge(this, vertex146, vertex147));
	graph->AddEdge(new CEntityEdge(this, vertex147, vertex148));
	graph->AddEdge(new CEntityEdge(this, vertex148, vertex149));
	graph->AddEdge(new CEntityEdge(this, vertex149, vertex152));
	graph->AddEdge(new CEntityEdge(this, vertex152, vertex150));
	graph->AddEdge(new CEntityEdge(this, vertex152, vertex151));
	graph->AddEdge(new CEntityEdge(this, vertex152, vertex153));
	graph->AddEdge(new CEntityEdge(this, vertex153, vertex154));
	graph->AddEdge(new CEntityEdge(this, vertex154, vertex166));
	graph->AddEdge(new CEntityEdge(this, vertex166, vertex165));
	graph->AddEdge(new CEntityEdge(this, vertex165, vertex164));
	graph->AddEdge(new CEntityEdge(this, vertex164, vertex203));
	graph->AddEdge(new CEntityEdge(this, vertex172, vertex171));
	graph->AddEdge(new CEntityEdge(this, vertex171, vertex170));
	graph->AddEdge(new CEntityEdge(this, vertex170, vertex169));
	graph->AddEdge(new CEntityEdge(this, vertex169, vertex168));
	graph->AddEdge(new CEntityEdge(this, vertex167, vertex166));
	graph->AddEdge(new CEntityEdge(this, vertex168, vertex167));
	graph->AddEdge(new CEntityEdge(this, vertex173, vertex175));
	graph->AddEdge(new CEntityEdge(this, vertex172, vertex175));
	graph->AddEdge(new CEntityEdge(this, vertex177, vertex172));
	graph->AddEdge(new CEntityEdge(this, vertex178, vertex177));
	graph->AddEdge(new CEntityEdge(this, vertex178, vertex179));
	graph->AddEdge(new CEntityEdge(this, vertex179, vertex180));
	graph->AddEdge(new CEntityEdge(this, vertex155, vertex181));
	graph->AddEdge(new CEntityEdge(this, vertex155, vertex149));
	graph->AddEdge(new CEntityEdge(this, vertex155, vertex154));
	graph->AddEdge(new CEntityEdge(this, vertex183, vertex182));
	graph->AddEdge(new CEntityEdge(this, vertex183, vertex184));
	graph->AddEdge(new CEntityEdge(this, vertex183, vertex145));
	graph->AddEdge(new CEntityEdge(this, vertex145, vertex194));
	graph->AddEdge(new CEntityEdge(this, vertex194, vertex195));
	graph->AddEdge(new CEntityEdge(this, vertex194, vertex193));
	graph->AddEdge(new CEntityEdge(this, vertex193, vertex192));
	graph->AddEdge(new CEntityEdge(this, vertex192, vertex191));
	graph->AddEdge(new CEntityEdge(this, vertex188, vertex187));
	graph->AddEdge(new CEntityEdge(this, vertex184, vertex185));
	graph->AddEdge(new CEntityEdge(this, vertex205, vertex204));
	graph->AddEdge(new CEntityEdge(this, vertex205, vertex206));
	graph->AddEdge(new CEntityEdge(this, vertex185, vertex306));
	graph->AddEdge(new CEntityEdge(this, vertex206, vertex306));
	graph->AddEdge(new CEntityEdge(this, vertex207, vertex206));
	graph->AddEdge(new CEntityEdge(this, vertex176, vertex207));
	graph->AddEdge(new CEntityEdge(this, vertex176, vertex174));
	graph->AddEdge(new CEntityEdge(this, vertex174, vertex175));
	graph->AddEdge(new CEntityEdge(this, vertex187, vertex186));
	graph->AddEdge(new CEntityEdge(this, vertex187, vertex189));
	graph->AddEdge(new CEntityEdge(this, vertex186, vertex184));
	graph->AddEdge(new CEntityEdge(this, vertex191, vertex190));
	graph->AddEdge(new CEntityEdge(this, vertex111, vertex110));
	graph->AddEdge(new CEntityEdge(this, vertex130, vertex131));
	graph->AddEdge(new CEntityEdge(this, vertex130, vertex132));
	graph->AddEdge(new CEntityEdge(this, vertex132, vertex125));
	graph->AddEdge(new CEntityEdge(this, vertex133, vertex134));
	graph->AddEdge(new CEntityEdge(this, vertex322, vertex176));
	graph->AddEdge(new CEntityEdge(this, vertex180, vertex181));
	graph->AddEdge(new CEntityEdge(this, vertex325, vertex322));
	graph->AddEdge(new CEntityEdge(this, vertex204, vertex327));

	imker = new CEntityImker(this);

	Tick();
}

void CEngine::Tick()
{
	running = true;
	bool exit = false;

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				exit = true;
				SDL_Quit();
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_UP) {
					scale -= 1.45f;
					if (scale < 0) {
						scale = 0;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					scale += 1.45f;
					if (scale > 16.0f) {
						scale = 16.0f;
					}
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
					exit = false;
				}
			}
			inputManager->Tick(&event);
		}

		entityManager->Tick();
		drawManager->Tick(renderer);

		for (CEntityEdge* edge : imker->currentPath) {
			SDL_RenderDrawLine(renderer, edge->vertexA->position.x, edge->vertexA->position.y, edge->vertexB->position.x, edge->vertexB->position.y);
		}

		for (int i = beeList.size() - 1; i >= 0; i--) {
			if (beeList[i]->caught) {
				CEntityBee* bee = beeList.at(i);
				beeList.erase(beeList.begin()+i);
				caughtBees.push_back(bee);
			}
		}

		for (int i = caughtBees.size() - 1; i >= 0; i--) {
			if (!caughtBees[i]->caught) {
				CEntityBee* bee = caughtBees.at(i);
				caughtBees.erase(caughtBees.begin() + i);
				beeList.push_back(bee);
			}
		}

		if (beeList.empty()) {
			running = false;
			exit = false;
		}

		SDL_Delay(scale);
	}

	for (CEntityBee* bee : caughtBees) {
		CDebugLogger::PrintDebug(bee->GetBeeGeneticString());
	}

	if (exit == false) {
		genetic = true;
		Start();
	}
}