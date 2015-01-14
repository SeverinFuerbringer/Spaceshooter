#include "MainMenu.h"
#include "Level_000.h"
#include "MenuOptions.h"
#include "MenuCredits.h"
#include "SplashScreen.h"
#include "Engine/Engine.h"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}


void MainMenu::loadContent()
{
	try
	{
		if(!m_font.loadFromFile("bin/gfx/fonts/space_age.ttf") ||
		        !m_title_font.loadFromFile("bin/gfx/fonts/space_age.ttf"))
			throw se::Error::FilesMissing::Font();

		if(!m_menu_poster_texture.loadFromFile("bin/gfx/menuscreen/poster.png"))
			throw se::Error::FilesMissing::Image();
	}
	catch(const char* error_message)
	{
		se::MsgBox::show(error_message, "Error", se::MsgBox::Icon::Error);
	}
	this->initialize();
}


void MainMenu::unloadContent()
{
	delete trns;
}


void MainMenu::update(sf::RenderWindow& window)
{
	for(se::uint i = 0; i < m_menu.elements.size(); i++)
	{
		se::vec2f mp(se::vec2f(sf::Mouse::getPosition(window)));
		if(m_menu.elements[i].getDrawable().getGlobalBounds().contains(mp))
		{
			if(se::Engine::get().getEvent()->type == sf::Event::MouseButtonPressed
			        && se::Engine::get().getEvent()->mouseButton.button == sf::Mouse::Left)
			{
				switch(i)
				{
				case 0:
					se::Engine::get().switchScene(new Level_000);
					return;
					break;

				case 1:
					se::Engine::get().switchScene(new MenuOptions);
					return;
					break;

				case 2:
					se::Engine::get().switchScene(new MenuCredits);
					return;
					break;

				case 3:
					se::Engine::get().shutDown();
					break;
				}
			}
			else
			{
				m_menu.elements[i].getDrawableText().setColor(sf::Color(4, 4, 4, 255));
				m_menu.elements[i].getDrawable().setOutlineThickness(5.0f);
			}
		}
		else
		{
			m_menu.elements[i].getDrawableText().setColor(sf::Color(50, 40, 40, 200));
			m_menu.elements[i].getDrawable().setOutlineThickness(0.0f);
		}
	}
}


void MainMenu::draw(sf::RenderWindow& Window)
{

	Window.draw(m_menu_poster);
	Window.draw(m_title_text);
	m_menu.draw(Window);
	if(!trns->done)
		trns->animate();
}


void MainMenu::initialize()
{

	m_title_text.setFont(m_title_font);
	m_title_text.setPosition(se::vec2f(370, 120));
	m_title_text.setColor(sf::Color(5, 5, 5, 255));
	m_title_text.setString("\tSeverins\nSpace Shooter");
	m_title_text.setCharacterSize(38);

	m_menu_poster.setTexture(&m_menu_poster_texture);
	m_menu_poster.setPosition(se::vec2f(0, 0));

	m_menu_poster.setSize((se::vec2f)se::Engine::get().getWinSize());

	trns = new se::Transition(se::Transition::Fade, sf::Color::Black, 255, 0,
	                          sf::seconds(1), se::Engine::get().getRenderWindow());

	initButtons();
}

void MainMenu::initButtons()
{
	se::uint menu_elem_X = se::Engine::get().getWinSize().x / 18;
	se::uint menu_elem_Y = se::Engine::get().getWinSize().y / 15;
	se::uint nl = 0;

	std::string btn_titles[4];
	btn_titles[0] = "start";
	btn_titles[1] = "optionen";
	btn_titles[2] = "author";
	btn_titles[3] = "beenden";

	for(se::uint i = 0; i <= 3; i++)
	{
		se::MenuButton btn_temp;
		btn_temp.setElementColor(sf::Color(20, 220, 220, 120));
		btn_temp.setFontColor(sf::Color(50, 40, 40, 200));
		btn_temp.setString(btn_titles[i]);
		btn_temp.setFontSize(34);
		btn_temp.setFont(m_font);
		btn_temp.setPosition(se::vec2u(menu_elem_X, menu_elem_Y += nl));
		btn_temp.setSize(se::vec2u(300, 80));

		m_menu_btn_arr[i] = btn_temp;

		nl = 150;
	}

	for(se::uint i = 0; i <= 3; i++)
		m_menu += m_menu_btn_arr[i];

	for(auto& i : m_menu.elements)
	{
		i.getDrawable().setOutlineColor(sf::Color(5, 10, 10, 250));
		i.getDrawable().setOutlineThickness(5.0f);
	}
}