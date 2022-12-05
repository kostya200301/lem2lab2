#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <ctime>


#include "windows.h"


using namespace std;




class Point {
private:
    float x;
    float y;
public:
    Point(float x, float y){
        this->x = x;
        this->y = y;
    }
    int GetX() {
        return this->x;
    }

    int GetY() {
        return this->y;
    }
};

void draw_line(sf::RenderWindow& window, Point start, Point end, int special=0) {
    if (special){

        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(start.GetX(), start.GetY()), sf::Color(255, 0, 0)),
                        sf::Vertex(sf::Vector2f(end.GetX(), end.GetY()), sf::Color(255, 0, 0))
                };
        window.draw(line, 2, sf::Lines);

    }
    else{


        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(start.GetX(), start.GetY())),
                        sf::Vertex(sf::Vector2f(end.GetX(), end.GetY()))
                };
        window.draw(line, 2, sf::Lines);

        sf::Vertex point1(sf::Vector2f(start.GetX(), start.GetY()), sf::Color::Yellow);
        sf::Vertex point2(sf::Vector2f(end.GetX(), end.GetY()), sf::Color::Yellow);
        window.draw(&point1, 1, sf::Points);
        window.draw(&point2, 1, sf::Points);
    }

}

float MaxTime(vector<pair<float, float>>& vec) {
    float maxx = vec[0].first;
    for (auto p : vec) {
        maxx = max(maxx, p.first);
    }
    return maxx;
}

float MinTime(vector<pair<float, float>>& vec) {
    float minn = vec[0].first;
    for (auto p : vec) {
        minn = min(minn, p.first);
    }
    return minn;
}

float MaxValue(vector<pair<float, float>>& vec) {
    float maxx = vec[0].second;
    for (auto p : vec) {
        maxx = max(maxx, p.second);
    }
    return maxx;
}


float MinValue(vector<pair<float, float>>& vec) {
    float minn = vec[0].second;
    for (auto p : vec) {
        minn = min(minn, p.second);
    }
    return minn;
}


int GetPow(float number) {
    int k = 0;
    while (number >= 1) {
        k++;
        number = number / 10;
    }
    return k - 1;
}

void WriteNumbersX(sf::RenderWindow& window, float minn, float maxx, int Width, int Height, int SizeMoveTo, int k, float step) {
    int COUNT = k;
    int interval = max((int)ceil((float)k / 10.0), 1);
    for (int i = 0; i < COUNT; i++) {

        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\user\\CLionProjects\\lizard\\ofont.ru_Departura.ttf"))
        {
            cout << "error\n";
        }
        text.setFont(font); // font is a sf::Font
        string data = to_string(step * i / (float)pow(10, GetPow(step * i)));
        string s = data.substr(0, 4) + "*10^" + to_string(abs(GetPow(step * i)));
        text.setString(s);
        text.setCharacterSize(17); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(SizeMoveTo + i * Width / COUNT, Height + 20);
        if (i % interval == 0) {
            window.draw(text);
        }
        draw_line(window, Point(SizeMoveTo + i * Width / COUNT, Height), Point(SizeMoveTo + i * Width / COUNT, Height + 10), 1);

    }
}

void WriteNumbersY(sf::RenderWindow& window, float minn, float maxx, int Height, int SizeMoveTo) {

    int FONTSIZE = 17;
    float COUNT = 10.0;
    float step = ((maxx - minn) / COUNT);
    for (int i = 0; i < COUNT; i++) {
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\user\\CLionProjects\\lizard\\ofont.ru_Departura.ttf")) {
            cout << "error\n";
        }
        text.setFont(font); // font is a sf::Font
        if (step * i < 10){
            text.setString(to_string(step * i + minn).substr(0, 4));
        }
        else {
            text.setString(to_string((int)(step * i) + minn).substr(0, 6));
        }
        text.setCharacterSize(FONTSIZE); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(2, Height - i * Height / COUNT - FONTSIZE);
        window.draw(text);
        draw_line(window, Point(SizeMoveTo, Height - i * Height / COUNT), Point(SizeMoveTo - 5, Height - i * Height / COUNT), 1);

    }
}


void Draw(vector<pair<float, float>>& vec, string name, int k, float step, pair<float, float> valueRange) {
    // create the window
    int Width = 1000;
    int Height = 600;
    int SizeMoveTo = 50;
    sf::RenderWindow window(sf::VideoMode(Width + SizeMoveTo, Height + SizeMoveTo), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

        }

        for (int i = 0; i < vec.size(); i++) {
            sf::RectangleShape rectangle(sf::Vector2f(((float)(Width - SizeMoveTo) / (float)k) * 0.9, (float)Height / (MaxValue(vec) - MinValue(vec)) * (vec[i].second - MinValue(vec))));
            rectangle.setPosition(SizeMoveTo + i * Width / k, Height - (float )Height / (MaxValue(vec) - MinValue(vec)) * (vec[i].second - MinValue(vec)));
            window.draw(rectangle);
        }


        draw_line(window, Point(SizeMoveTo, 0), Point(SizeMoveTo, Height), 1);
        draw_line(window, Point(SizeMoveTo, Height), Point(Width + SizeMoveTo, Height), 1);
        WriteNumbersX(window, MinTime(vec), MaxTime(vec), Width, Height, SizeMoveTo, k, step);
        WriteNumbersY(window, MinValue(vec), MaxValue(vec), Height, SizeMoveTo);
//        exit(0);


//        sf::Texture texture;
//        texture.create(window.getSize().x, window.getSize().y);
//        texture.update(window);
//        if (texture.copyToImage().saveToFile(name + ".jpg"))
//        {
//            std::cout << "screenshot saved to " << name + ".jpg" << std::endl;
//        }
        window.display();

    }
}

//int main()
//{
//
////    cout << GetPow(2) << " " << 2.0 / (float) pow(10, GetPow(2)) << endl;
////    cout << GetPow(1) << " " << GetPow(2) << " " << GetPow(10) << " " << GetPow(300) << " " << GetPow(150) << " " << endl;
//
////    vector<pair<float, float>> vec = { {100, 300}, {125, 600}, {150, 4}, {140, 700}, {190, 333}, {300, 666}, {333, 333} };
//    vector<pair<float, float>> vec;
//    vector<int> data;
//
//    for (int n = 10000; n < 800000; n += 10000){
//        auto start = clock();
//        data.push_back(n);
//        for (int i = 0; i < n; i++) {
//            sort(data.begin(), data.end());
//        }
//        vec.push_back({n, ((float)(clock() - start)) / 1000.0});
//        cout << n << endl;
//    }
//
//
////    for (int i = 10; i < 15 * 10; i++) {
////        vec.push_back({i * i, i * });
////    }
//    Draw(vec);
//
//
//    return 0;
//}

#ifndef SEM2LAB1_GRAPHIK_H
#define SEM2LAB1_GRAPHIK_H

#endif //SEM2LAB1_GRAPHIK_H