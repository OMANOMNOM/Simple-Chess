#pragma once
#include "Screen.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string
#include <chrono>                  // for operator""s, chrono_literals
#include <thread>  // for sleep_for
#include <functional>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui
class ScreenFTX :
	public Screen
{
public:


	std::vector<std::string> entries;
	ftxui::MenuOption option;
	int selected = 0;
	int timer;
	ftxui::Component menuObject;
	ftxui::Component renderMenu;

	ScreenFTX(ftxui::Component* curScreen) {
		using namespace ftxui;
		using namespace std::chrono_literals;

		//Menu stuff
		entries = {
		"New Game",
		"Options",
		"Exit",
		};
		selected = 0;
		curScreen = nullptr;
		menuObject = Menu(&entries, &selected, &option);

		renderMenu = Renderer(menuObject, [&] {
			// Stick everything in here that i want to render
			return
				gridbox({
					{
					filler(),
					vbox({
						text("Chess game"),
						vbox({
							text(R"(                                                       .::.)"),
							text(R"(                                            _()_       _::_)"),
							text(R"(                                  _O      _/____\_   _/____\_)"),
							text(R"(           _  _  _     ^^__      / //\    \      /   \      /)"),
							text(R"(          | || || |   /  - \_   {     }    \____/     \____/)"),
							text(R"(          |_______| <|    __<    \___/     (____)     (____))"),
							text(R"(    _     \__ ___ / <|    \      (___)      |  |       |  |)"),
							text(R"(   (_)     |___|_|  <|     \      |_|       |__|       |__|)"),
							text(R"(  (___)    |_|___|  <|______\    /   \     /    \     /    \)"),
							text(R"(  _|_|_    |___|_|   _|____|_   (_____)   (______)   (______))"),
							text(R"( (_____)  (_______) (________) (_______) (________) (________))"),
							text(R"( /_____\  /_______\ /________\ /_______\ /________\ /________\)"),
							text(R"(                                             __By Alefith 22.02.95__)"),

						}),
						separator(),
						border(
							vbox({
							menuObject->Render(),
							})
						),
					}),
					filler(),
					}
					}) |
				border;
			});

		//option.on_enter = &startTimer;
		//using Closure = std::function<void()>;
		//std::cout << "Selected element = " << selected << std::endl;
	}

	virtual void start() {};
	virtual void loop() {};
	virtual void end() {};
};

