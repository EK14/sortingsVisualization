//
// Created by Элина Карапетян on 19.07.2022.
//

#ifndef SORTINGVISUAL_MAIN_H
#define SORTINGVISUAL_MAIN_H
#include <SFML/Graphics.hpp>

void render(sf::RenderWindow *window, std::vector<sf::RectangleShape> &rectangles, int speed);
void selectionSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);
void swap(int ind1, int ind2, std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);
void initVisualization(std::vector<sf::RectangleShape> &rectangles);
void done(sf::RenderWindow *window, std::vector<sf::RectangleShape> &rectangles);
int partition (std::vector<sf::RectangleShape> &rectangles, int low, int high, sf::RenderWindow *window, int speed);
void quickSort(std::vector<sf::RectangleShape> &rectangles, int p, int r, sf::RenderWindow *window, int speed);
void BubbleSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);


#endif //SORTINGVISUAL_MAIN_H
