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
void bubbleSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);
void insertionSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);
void merge(std::vector<sf::RectangleShape> &rectangles, int const left, int const mid, int const right, sf::RenderWindow *window, int speed);
void mergeSort(std::vector<sf::RectangleShape> &rectangles, int const begin, int const end, sf::RenderWindow *window, int speed);
void heapify(std::vector<sf::RectangleShape> &rectangles, int n, int i, sf::RenderWindow *window, int speed);
void heapSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed);



#endif //SORTINGVISUAL_MAIN_H
