#pragma once
#include "entity.h"
#include <vector>

const uint16_t XCELLS = 80, YCELLS = 50;
const uint16_t CELL_W = 20, CELL_H = 20;

struct Dots
{
	Dots(size_t size) : size(size)
	{
		X.resize(size);
		Y.resize(size);
	}

	size_t size;
	std::vector<double> X;
	std::vector<double> Y;
};

struct LineStrip
{
	LineStrip(size_t size) : size(size)
	{
		X.resize(size);
		Y.resize(size);
	}

	size_t size;
	std::vector<double> X;
	std::vector<double> Y;
};

struct Intervals
{
	Intervals(size_t size) : size(size)
	{
		Xinterval.resize(size);
		Y.resize(size);
	}

	size_t size;
	std::vector<std::pair<double, double>> Xinterval;
	std::vector<double> Y;
};

class MyPlot : public MyEntity
{
public:

	MyPlot(sf::Color color) : m_color(color)
	{
		m_transform.translate(20, 20 + (YCELLS * CELL_H));
	}

	bool set(Dots dots, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
	{
		m_knots.clear();
		m_knots.setPrimitiveType(sf::Quads);
		m_knots.resize(dots.size * 4);

		for (int i = 0; i < dots.size; ++i) {
			m_knots[i * 4 + 0] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((dots.X[i] - Xshift) * CELL_W) / Xscale - 2),
				static_cast<float>(-((dots.Y[i] - Yshift) * CELL_H) / Yscale)
			), m_color);
			m_knots[i * 4 + 1] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((dots.X[i] - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-((dots.Y[i] - Yshift) * CELL_H) / Yscale + 2)
			), m_color);
			m_knots[i * 4 + 2] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((dots.X[i] - Xshift) * CELL_W) / Xscale + 2),
				static_cast<float>(-((dots.Y[i] - Yshift) * CELL_H) / Yscale)
			), m_color);
			m_knots[i * 4 + 3] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((dots.X[i] - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-((dots.Y[i] - Yshift) * CELL_H) / Yscale - 2)
			), m_color);
		}

		return true;
	}

	bool set(LineStrip dots, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
	{
		m_knots.clear();
		m_knots.setPrimitiveType(sf::LineStrip);
		m_knots.resize(dots.size);

		for (int i = 0; i < dots.size; ++i) {
			m_knots[i] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((dots.X[i] - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-((dots.Y[i] - Yshift) * CELL_H) / Yscale)
			), m_color);
		}

		return true;
	}

	bool set(Intervals intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
	{
		m_knots.clear();
		m_knots.setPrimitiveType(sf::Quads);
		m_knots.resize(intervals.size * 4);

		for (int i = 0; i < intervals.size; ++i) {
			m_knots[i * 4] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((intervals.Xinterval[i].first - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-Yshift * CELL_H / Yscale)
			), m_color);
			m_knots[i * 4 + 1] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((intervals.Xinterval[i].first - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-(intervals.Y[i] * CELL_H + Yshift) / Yscale)
			), m_color);
			m_knots[i * 4 + 2] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((intervals.Xinterval[i].second - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-(intervals.Y[i] * CELL_H + Yshift) / Yscale)
			), m_color);
			m_knots[i * 4 + 3] = sf::Vertex(sf::Vector2f(
				static_cast<float>(((intervals.Xinterval[i].second - Xshift) * CELL_W) / Xscale),
				static_cast<float>(-Yshift * CELL_H / Yscale)
			), m_color);
		}

		return true;
	}

private:

	virtual void onDraw(sf::RenderTarget& target) const
	{
		target.draw(m_knots, m_transform);
	}

	sf::Transform m_transform;
	sf::VertexArray m_knots;
	sf::Color m_color;
};