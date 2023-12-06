#pragma once
#include "plot.h"
#include "grid.h"

class MyScene : public MyEntity
{
public:

    MyScene()
    {
        grid = std::make_unique<MyGrid>(sf::Color(0x0, 0x0, 0x0, 50));
        plot1 = std::make_unique<MyPlot>(sf::Color(0xff, 0x0, 0x0)); // curve
        plot2 = std::make_unique<MyPlot>(sf::Color(0x0, 0x0, 0x0)); // dots
        plot3 = std::make_unique<MyPlot>(sf::Color(0x0, 0x0, 0xff)); // bars
        plot4 = std::make_unique<MyPlot>(sf::Color(0x0, 0xff, 0x0, 0xaf)); // bars
        m_children.push_back(grid.get());
        m_children.push_back(plot3.get());
        m_children.push_back(plot4.get());
        m_children.push_back(plot1.get());
        m_children.push_back(plot2.get());
    }

    bool set_plot(LineStrip dots, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot1->set(dots, Xscale, Yscale, Xshift, Yshift);
    }

    bool set_dots(Dots intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot2->set(intervals, Xscale, Yscale, Xshift, Yshift);
    }

    bool set_plot(Intervals intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot3->set(intervals, Xscale, Yscale, Xshift, Yshift);
    }

    bool set_plot_transparent(Intervals intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot4->set(intervals, Xscale, Yscale, Xshift, Yshift);
    }

    void draw(sf::RenderTarget& target) const
    {
        for (std::size_t i = 0; i < m_children.size(); ++i)
            m_children[i]->draw(target);
    }

private:

    void onDraw(sf::RenderTarget& target) const override {};

    std::unique_ptr<MyGrid> grid;
    std::unique_ptr<MyPlot> plot1;
    std::unique_ptr<MyPlot> plot2;
    std::unique_ptr<MyPlot> plot3;
    std::unique_ptr<MyPlot> plot4;

    sf::Transform m_transform;
    std::vector<MyEntity*> m_children;
};