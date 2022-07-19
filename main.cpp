#include <vector>
#include "main.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#define windWidth 2000
#define windHeight 800

void swap(int ind1, int ind2, std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed){
    sf::Vector2f buf;

    rectangles[ind1].setFillColor(sf::Color(255, 0, 0));
    rectangles[ind2].setFillColor(sf::Color(255, 0, 0));
    buf = rectangles[ind1].getSize();
    rectangles[ind1].setSize(sf::Vector2f(rectangles[ind2].getSize()));
    rectangles[ind2].setSize(sf::Vector2f(buf));
    rectangles[ind1].setPosition(sf::Vector2f(rectangles[ind1].getPosition().x, windHeight - rectangles[ind1].getSize().y));
    rectangles[ind2].setPosition(sf::Vector2f(rectangles[ind2].getPosition().x, windHeight - rectangles[ind2].getSize().y));
    render(window, rectangles, speed);
    rectangles[ind1].setFillColor(sf::Color(255, 255, 255));
    rectangles[ind2].setFillColor(sf::Color(255, 255, 255));
}

void initVisualization(std::vector<sf::RectangleShape> &rectangles){
    for(int i = 0; i < windWidth / 10; ++i){
        rectangles[i].setSize(sf::Vector2f(8, rand() % (windHeight - 30)));
        rectangles[i].setFillColor(sf::Color(255, 255, 255));
        rectangles[i].setPosition(sf::Vector2f(10 * i, windHeight - rectangles[i].getSize().y));
        rectangles[i].setOutlineThickness(1);
        rectangles[i].setOutlineColor(sf::Color(75, 75, 75));
    }
}

void done(sf::RenderWindow *window, std::vector<sf::RectangleShape> &rectangles){
    window->clear(sf::Color(75, 75, 75));
    for(int i = 0; i < windWidth / 10; ++i){
        window->clear(sf::Color(75, 75, 75));
        for(int j = 0; j < windWidth / 10; ++j) {
            rectangles[i].setFillColor(sf::Color(255, 0, 0));
            window->draw(rectangles[j]);
        }
        usleep(5000);
        window->display();
        rectangles[i].setFillColor(sf::Color(124,252,0));
    }
}
void render(sf::RenderWindow *window, std::vector<sf::RectangleShape> &rectangles, int speed){
    window->clear(sf::Color(75, 75, 75));
    for(int i = 0; i < windWidth / 10; ++i){
        window->draw(rectangles[i]);
    }
    window->display();
    usleep(speed);
}

int partition (std::vector<sf::RectangleShape> &rectangles, int low, int high, sf::RenderWindow *window, int speed)
{
    sf::RectangleShape pivot = rectangles[high];// pivot
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if (rectangles[j].getSize().y <= pivot.getSize().y)
        {
            i++;    // increment index of smaller element
            swap(i, j, rectangles, window, speed);
        }
    }
    swap(i+1, high, rectangles, window, speed);
    return (i + 1);
}

void quickSort(std::vector<sf::RectangleShape> &rectangles, int p, int r, sf::RenderWindow *window, int speed){
    int q;
    if(p >= r)
        return;
    else{
        q = partition(rectangles, p, r, window, speed);
        quickSort(rectangles, p, q - 1, window, speed);
        quickSort(rectangles, q + 1, r, window, speed);
    }
}

void BubbleSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed){
    for (int i = 0; i < rectangles.size() - 1; i++) {
        for (int j = 0; j < rectangles.size() - i - 1; j++) {
            if (rectangles[j].getSize().y > rectangles[j + 1].getSize().y) {
                // swap elements
                swap(j, j+1, rectangles, window, speed);
            }
        }
    }
}

int main()
{
    bool isSorted = false;

    std::srand(static_cast<unsigned>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(windWidth, windHeight), "Sortings");

    std::vector<sf::RectangleShape> rectangles(windWidth/10);
    sf::RectangleShape rect;
    int answer;

    initVisualization(rectangles);

    // run the program as long as the window is open
    render(&window, rectangles, 10000);
    while (window.isOpen())
    {
        window.clear(sf::Color(75, 75, 75));
        render(&window, rectangles, 10000);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(!isSorted){
            std::cout << "\nWhat sorting algorithm do you want to use?\n1. Bubble Sort\n2. Quick Sort\nEnter the number > ";
            std::cin >> answer;
            switch(answer){
                case 1:
                    BubbleSort(rectangles, &window, 100);
                    break;
                case 2:
                    quickSort(rectangles, 0, rectangles.size() - 1, &window, 10000);
                    break;
            }
            isSorted = true;
            done(&window, rectangles);
        }
        else{
            std::cout << "\nRestart?\n1. yes\n2. no\nEnter the number > ";
            std::cin >> answer;
            switch(answer){
                case 1:
                    isSorted = false;
                    initVisualization(rectangles);
                    break;
                case 2:
                    window.close();
                    break;
            }
        }
    }

    return 0;
}