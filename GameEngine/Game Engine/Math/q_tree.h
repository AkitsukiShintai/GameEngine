/* Start Header -------------------------------------------------------
Copyright (C) 2018
DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:<q_tree.cpp>
Purpose:<implement quad tree for game objects management>
Language:<C++>
Platform:<windows 10>
Project:<CS529_w.zhongqiu_2_GameEngine>
Author:<Wang Zhongqiu, w.zhongqiu, 60003918>
Creation date:<11/15/2018>
History:

-End Header --------------------------------------------------------*/
#pragma once
#include"glm.hpp"
#include<vector>
#include<list>

namespace Q_TREE{
template<typename T>
struct Rectangle
{
	Rectangle(const glm::vec2 & a, const glm::vec2 & b) {
		centre = a;
		Size = b;
		data = nullptr;
	};
	Rectangle(const glm::vec2 & a, const glm::vec2 & b, T c) {
		centre = a;
		Size = b;
		data = c;
	};
	Rectangle() {
		centre = glm::vec2(0);
		Size = glm::vec2(0);
		data = nullptr;
	};
	glm::vec2 centre;//actually left down
	glm::vec2 Size;
	T data;

	float getWidth() {
		return Size.x;
	}
	float getHeight() {
		return Size.y;
	}

	float getX() {
		return centre.x;
	}

	float getY() {
		return centre.y;
	}

	bool contains(glm::vec2& a) const
	{
		if (a.x <= centre.x + Size.x && a.x >= centre.x - Size.x)
		{
			if (a.y <= centre.y + Size.y && a.y >= centre.y - Size.y)
			{
				return true;
			}
		}
		return false;
	}

};

template<typename T>
class Quadtree {

private: int MAX_OBJECTS = 4;
		 int MAX_LEVELS = 8;

		 int level;
		 std::vector<Rectangle<T>> objects;
		 // std::vector<Rectangle> objects;
		 Rectangle<T> bounds;
		 /* Quadtree* node1;
		  Quadtree* node2;
		  Quadtree* node3;
		  Quadtree* node4;*/
		 Quadtree* nodes[4];
		 /*
		   * Constructor
		   */
public:
	Quadtree<T>(int pLevel, Rectangle<T> pBounds) : objects(), nodes{ nullptr } {
		level = pLevel;
		bounds = pBounds;


	}


	Quadtree<T>() : bounds(), objects(4), nodes{ nullptr } {
		level = 0;
	}
	~Quadtree<T>() {
		if (nodes[0] != nullptr) {
			for (size_t i = 0; i < 4; i++)
			{
				delete nodes[i];
			}
		}
	}
	void clear() {
		objects.clear();
		if (nodes[0] != nullptr) {
			/*node1->clear();
			node1 = nullptr;
			node2->clear();
			node2 = nullptr;
			node3->clear();
			node3 = nullptr;
			node4->clear();
			node4 = nullptr;*/
			for (size_t i = 0; i < 4; i++)
			{
				nodes[i]->clear();
			}
		}
	}

	void split() {
		int subWidth = (int)(bounds.getWidth() / 2);
		int subHeight = (int)(bounds.getHeight() / 2);
		int x = (int)bounds.getX();
		int y = (int)bounds.getY();

		nodes[3] = new Quadtree(level + 1, Rectangle<T>(glm::vec2(x + subWidth, y), glm::vec2(subWidth, subHeight)));
		nodes[2] = new Quadtree(level + 1, Rectangle<T>(glm::vec2(x, y), glm::vec2(subWidth, subHeight)));
		nodes[1] = new Quadtree(level + 1, Rectangle<T>(glm::vec2(x, y + subHeight), glm::vec2(subWidth, subHeight)));
		nodes[0] = new Quadtree(level + 1, Rectangle<T>(glm::vec2(x + subWidth, y + subHeight), glm::vec2(subWidth, subHeight)));
	}

	int getIndex(Rectangle<T> pRect) {
		int index = -1;
		double verticalMidpoint = bounds.getX() + (bounds.getWidth() / 2);
		double horizontalMidpoint = bounds.getY() + (bounds.getHeight() / 2);

		// Object can completely fit within the top quadrants
		bool topQuadrant = (pRect.getY() > horizontalMidpoint);
		// Object can completely fit within the bottom quadrants
		bool bottomQuadrant = (pRect.getY() + pRect.getHeight() < horizontalMidpoint);

		// Object can completely fit within the left quadrants
		if (pRect.getX() + pRect.getWidth() < verticalMidpoint) {
			if (topQuadrant) {
				index = 1;
			}
			else if (bottomQuadrant) {
				index = 2;
			}
		}
		// Object can completely fit within the right quadrants
		else if (pRect.getX() > verticalMidpoint) {
			if (topQuadrant) {
				index = 0;
			}
			else if (bottomQuadrant) {
				index = 3;
			}
		}

		return index;
	}

	void insert(Rectangle<T> pRect) {

		if (nodes[0] != nullptr) {
			int index = getIndex(pRect);

			if (index != -1) {
				nodes[index]->insert(pRect);

				return;
			}
			else
			{
				objects.push_back(pRect);
				return;
			}
		}

		objects.push_back(pRect);
		if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
			split();

			int i = 0;
			while (i < objects.size()) {
				int index = getIndex(objects[i]);
				if (index != -1) {
					auto it = objects.begin() + i;
					nodes[index]->insert((*it));
					objects.erase(it);
				}
				else {
					i++;
				}
			}
		}
	}

	std::vector<Rectangle<T>>& retrieve(std::vector<Rectangle<T>>& result, Rectangle<T> pRect) {
		int index = getIndex(pRect);
		if (index != -1 && nodes[0] != nullptr) {
			nodes[index]->retrieve(result, pRect);
		}

		result.insert(result.end(), objects.begin(), objects.end());
		return result;
	}
	std::list<Rectangle<T>>& retrieve(std::list<Rectangle<T>>& result, Rectangle<T> pRect) {
		int index = getIndex(pRect);
		if (index != -1 && nodes[0] != nullptr) {
			nodes[index]->retrieve(result, pRect);
		}

		result.insert(result.end(), objects.begin(), objects.end());

		return result;
	}

	int GetCount() {
	
	
		int t = 0;
		t = objects.size();
		if (nodes[0] != nullptr) {
			/*node1->clear();
			node1 = nullptr;
			node2->clear();
			node2 = nullptr;
			node3->clear();
			node3 = nullptr;
			node4->clear();
			node4 = nullptr;*/
			for (size_t i = 0; i < 4; i++)
			{
				t+=nodes[i]->GetCount();
			}
		
		}
	
		return t;
	}


};

}