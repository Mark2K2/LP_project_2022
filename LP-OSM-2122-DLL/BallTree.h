#pragma once
#include "pch.h"
#include "Ball.h"
#include "Util.h"
#include "Common.h"


class BallTree {

public:

	BallTree();
	~BallTree();
	bool fulla() const { if ((m_left == nullptr) && (m_right == nullptr) && (m_data != nullptr)) return true; else return false; }
	bool isEmpty() const { if (m_data == NULL) return true; else return false; }
	Ball* getRight() { return m_right; }
	Ball* getLeft() { return m_left; }
	Ball& getData() { return (*m_data); }

private:

	Ball* m_right;
	Ball* m_left;
	Ball* m_father;
	Ball* m_data;

};

