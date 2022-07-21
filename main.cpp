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
    std::vector<bool> size(200, false);
    int choice = 1;
    for(int i = 0; i < windWidth / 10; ++i){
        while(size[choice]){
            choice = rand() % 200;
        }
        size[choice] = true;
        rectangles[i].setSize(sf::Vector2f(8, choice*4));
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

//*********************************************************************************************************************
//*************************************************Quick Sort**********************************************************

int partition (std::vector<sf::RectangleShape> &rectangles, int low, int high, sf::RenderWindow *window, int speed){
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

//*********************************************************************************************************************
//*************************************************Bubble Sort*********************************************************

void bubbleSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed){
    for (int i = 0; i < rectangles.size() - 1; i++) {
        for (int j = 0; j < rectangles.size() - i - 1; j++) {
            if (rectangles[j].getSize().y > rectangles[j + 1].getSize().y) {
                // swap elements
                swap(j, j+1, rectangles, window, speed);
            }
        }
    }
}

//*********************************************************************************************************************
//*************************************************Selection Sort******************************************************

void selectionSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed) {
    for (int step = 0; step < rectangles.size() - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < rectangles.size(); i++) {

            // To sort in descending order, change > to < in this line.
            // Select the minimum element in each loop.
            if (rectangles[i].getSize().y < rectangles[min_idx].getSize().y)
                min_idx = i;
        }

        // put min at the correct position
        swap(min_idx, step, rectangles, window, speed);
    }
}

//*********************************************************************************************************************
//*************************************************Insertion Sort******************************************************

void insertionSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed){
    sf::RectangleShape key;
    int i, j;
    for (i = 1; i < rectangles.size(); i++)
    {
        key = rectangles[i];
        j = i - 1;
        while (j >= 0 && rectangles[j].getSize().y > key.getSize().y)
        {
            rectangles[j + 1].setFillColor(sf::Color(255, 0, 0));
            rectangles[j + 1].setSize(sf::Vector2f(rectangles[j].getSize()));
            rectangles[j + 1].setPosition(sf::Vector2f(rectangles[j + 1].getPosition().x, windHeight - rectangles[j + 1].getSize().y));
            render(window, rectangles, speed);
            rectangles[j + 1].setFillColor(sf::Color(255, 255, 255));
            j = j - 1;
        }
        rectangles[j + 1].setFillColor(sf::Color(255, 0, 0));
        rectangles[j + 1].setSize(sf::Vector2f(key.getSize()));
        rectangles[j + 1].setPosition(sf::Vector2f(rectangles[j + 1].getPosition().x, windHeight - rectangles[j + 1].getSize().y));
        render(window, rectangles, speed);
        rectangles[j + 1].setFillColor(sf::Color(255, 255, 255));
    }
}

//*********************************************************************************************************************
//*************************************************Merge Sort**********************************************************

void merge(std::vector<sf::RectangleShape> &rectangles, int const left, int const mid, int const right, sf::RenderWindow *window, int speed){
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new sf::RectangleShape[subArrayOne], *rightArray = new sf::RectangleShape[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++){
        leftArray[i].setFillColor(sf::Color(255, 0, 0));
        leftArray[i].setSize(sf::Vector2f(rectangles[left + i].getSize()));
        leftArray[i].setPosition(sf::Vector2f(leftArray[i].getPosition().x, windHeight - leftArray[i].getSize().y));
        render(window, rectangles, speed);
        leftArray[i].setFillColor(sf::Color(255, 255, 255));
    }
    for (auto j = 0; j < subArrayTwo; j++){
        rightArray[j].setFillColor(sf::Color(255, 0, 0));
        rightArray[j].setSize(sf::Vector2f(rectangles[mid + 1 + j].getSize()));
        rightArray[j].setPosition(sf::Vector2f(rightArray[j].getPosition().x, windHeight - rightArray[j].getSize().y));
        render(window, rectangles, speed);
        rightArray[j].setFillColor(sf::Color(255, 255, 255));
    }

    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
    indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].getSize().y <= rightArray[indexOfSubArrayTwo].getSize().y) {
            rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 0, 0));
            rectangles[indexOfMergedArray].setSize(sf::Vector2f(leftArray[indexOfSubArrayOne].getSize()));
            rectangles[indexOfMergedArray].setPosition(sf::Vector2f(rectangles[indexOfMergedArray].getPosition().x, windHeight - rectangles[indexOfMergedArray].getSize().y));
            render(window, rectangles, speed);
            rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 255, 255));
            indexOfSubArrayOne++;
        }
        else {
            rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 0, 0));
            rectangles[indexOfMergedArray].setSize(sf::Vector2f(rightArray[indexOfSubArrayTwo].getSize()));
            rectangles[indexOfMergedArray].setPosition(sf::Vector2f(rectangles[indexOfMergedArray].getPosition().x, windHeight - rectangles[indexOfMergedArray].getSize().y));
            render(window, rectangles, speed);
            rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 255, 255));
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 0, 0));
        rectangles[indexOfMergedArray].setSize(sf::Vector2f(leftArray[indexOfSubArrayOne].getSize()));
        rectangles[indexOfMergedArray].setPosition(sf::Vector2f(rectangles[indexOfMergedArray].getPosition().x, windHeight - rectangles[indexOfMergedArray].getSize().y));
        render(window, rectangles, speed);
        rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 255, 255));
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 0, 0));
        rectangles[indexOfMergedArray].setSize(sf::Vector2f(rightArray[indexOfSubArrayTwo].getSize()));
        rectangles[indexOfMergedArray].setPosition(sf::Vector2f(rectangles[indexOfMergedArray].getPosition().x, windHeight - rectangles[indexOfMergedArray].getSize().y));
        render(window, rectangles, speed);
        rectangles[indexOfMergedArray].setFillColor(sf::Color(255, 255, 255));
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(std::vector<sf::RectangleShape> &rectangles, int const begin, int const end, sf::RenderWindow *window, int speed){
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(rectangles, begin, mid, window, speed);
    mergeSort(rectangles, mid + 1, end, window, speed);
    merge(rectangles, begin, mid, end, window, speed);
}

//*********************************************************************************************************************
//*************************************************Heap Sort***********************************************************

void heapify(std::vector<sf::RectangleShape> &rectangles, int n, int i, sf::RenderWindow *window, int speed){
    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && rectangles[l].getSize().y > rectangles[largest].getSize().y)
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < n && rectangles[r].getSize().y > rectangles[largest].getSize().y)
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(i, largest, rectangles, window, speed);

        // Recursively heapify the affected
        // sub-tree
        heapify(rectangles, n, largest, window, speed);
    }
}

// Main function to do heap sort
void heapSort(std::vector<sf::RectangleShape> &rectangles, sf::RenderWindow *window, int speed){

    // Build heap (rearrange array)
    for (int i = rectangles.size() / 2 - 1; i >= 0; i--)
        heapify(rectangles, rectangles.size(), i, window, speed);

    // One by one extract an element
    // from heap
    for (int i = rectangles.size() - 1; i > 0; i--) {

        // Move current root to end
        swap(0, i, rectangles, window, speed);

        // call max heapify on the reduced heap
        heapify(rectangles, i, 0, window, speed);
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
            std::cout << "\nWhat sorting algorithm do you want to use?\n1. Bubble Sort\n2. Quick Sort\n"
                         "3. Selection Sort\n4. Insertion Sort\n5. Merge Sort\n6. Heap Sort\nEnter the number > ";
//            std::cin >> answer;
            answer = 6;
            switch(answer){
                case 1:
                    bubbleSort(rectangles, &window, 100);
                    break;
                case 2:
                    quickSort(rectangles, 0, rectangles.size() - 1, &window, 10000);
                    break;
                case 3:
                    selectionSort(rectangles, &window, 50000);
                    break;
                case 4:
                    insertionSort(rectangles, &window, 1000);
                    break;
                case 5:
                    mergeSort(rectangles, 0, rectangles.size() - 1, &window, 1000);
                    break;
                case 6:
                    heapSort(rectangles, &window, 10000);
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