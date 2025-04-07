#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <math.h>
#include <Windows.h>

int windowWidth = 750, windowHeight = 750,wall=10000;
float rad = 0.01745;
sf::Vector2f initPos = sf::Vector2f(80.0f, 40.0f);
sf::RenderWindow mapwindow(sf::VideoMode(500.0f, 500.0f), "map", sf::Style::Close | sf::Style::Titlebar);

sf::Vector2f prevMouse, mouse;

class Player {
public:
	sf::Vector2f position = initPos;
	float dir = 0;
};
Player player;

class Map {
	
private:
public:
	Map() {
		
	}
	int mat[200][200];
	int get(sf::Vector2f pos) {
		return mat[int(pos.x)][int(pos.y)];
	}
} map;

void init() {
	std::ifstream in("map.txt");
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			int x;
			in >> x;
			std::cout << x;
			if (x == 1) {
				map.mat[i][j] = 1;
				std::cout << i << " " << j << std::endl;
			}
			else map.mat[i][j] = 0;
		}
	}
}

void drawmap() {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(2.0f, 2.0f));
	rect.setFillColor(sf::Color::White);
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			if (map.mat[i][j] != 0) {
				rect.setPosition(i * 2.5f, j * 2.5f);
				mapwindow.draw(rect);
			}
		}
	}
}

int cast(sf::Vector2f initPos, float angle) {
	int dist=0;
	drawmap();
	sf::Vector2f pos = initPos,dir = sf::Vector2f(sin(angle),cos(angle));
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(1);
	while (map.get(pos)==0) {
		dist++;
		pos += dir;
		circ.setPosition(pos.x*2.5f,pos.y*2.5f);
		mapwindow.draw(circ);
		if ((pos.x > 200||pos.y>200) || (pos.x<0||pos.y<0)) {
			return -1;
		}
	}
	//dist = dist * cos(angle-player.dir);
	if (dist < 0) dist = -dist;	
	return dist;
}

void run() {
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "game", sf::Style::Close | sf::Style::Titlebar);
	
	while (window.isOpen()) {
		window.clear();

		sf::Event ev;
		while (window.pollEvent(ev)) if (ev.type == ev.Closed) window.close();
		else {
			mouse = sf::Vector2f(sf::Mouse::getPosition());
			if (prevMouse != mouse) {
				player.dir += (prevMouse.x - mouse.x)*0.05;
			}
			prevMouse = mouse;
			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::W) {
					player.position.x -= sin(player.dir)*10;
					player.position.y -= cos(player.dir)*10;
				}
			}
		}
		mapwindow.clear();
		for (float i = -15; i < 15; i+=0.05) {
			float distance = cast(sf::Vector2f(player.position.x+i*sin((player.dir-90)*rad),player.position.y+i*cos((player.dir-90)*rad)), (player.dir) * rad);
			//std::cout<<distance<< " ";
			if (distance>0) {
				sf::RectangleShape slice(sf::Vector2f(3, wall / distance));
				slice.setFillColor(sf::Color::Green);
				slice.setPosition(sf::Vector2f((i+15)*25, wall/(distance*2)));
				window.draw(slice);
			}
		}
		std::cout << std::endl;
		mapwindow.display();

		
		//draw stuff
		window.display();
		Sleep(1);
	}
}

int main()
{
	mouse = sf::Vector2f(sf::Mouse::getPosition());
	prevMouse = mouse;
	init();
	run();
}

