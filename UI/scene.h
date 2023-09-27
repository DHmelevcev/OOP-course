#pragma once
#include "plot.h"
#include "grid.h"

class MyScene : public MyEntity
{
public:

    MyScene()
    {
        grid = std::make_unique<MyGrid>(sf::Color(0x0, 0x0, 0x0, 50));
        plot1 = std::make_unique<MyPlot>(sf::Color(0xff, 0x0, 0x0));
        plot2 = std::make_unique<MyPlot>(sf::Color(0x0, 0x0, 0xff));
        plot3 = std::make_unique<MyPlot>(sf::Color(0x0, 0xff, 0x0, 0xaf));
        m_children.push_back(&*grid);
        m_children.push_back(&*plot2);
        m_children.push_back(&*plot3);
        m_children.push_back(&*plot1);
    }

    bool set_plot(Dots dots, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot1->set(dots, Xscale, Yscale, Xshift, Yshift);
    }

    bool set_plot(Intervals intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot2->set(intervals, Xscale, Yscale, Xshift, Yshift);
    }

    bool set_plot_transparent(Intervals intervals, double Xscale = 1, double Yscale = 1, double Xshift = 0, double Yshift = 0)
    {
        return plot3->set(intervals, Xscale, Yscale, Xshift, Yshift);
    }

    void draw(sf::RenderTarget& target) const
    {
        for (std::size_t i = 0; i < m_children.size(); ++i)
            m_children[i]->draw(target);
    }

private:

    virtual void onDraw(sf::RenderTarget& target) const {};

    std::unique_ptr<MyGrid> grid;
    std::unique_ptr<MyPlot> plot1;
    std::unique_ptr<MyPlot> plot2;
    std::unique_ptr<MyPlot> plot3;

    sf::Transform m_transform;
    std::vector<MyEntity*> m_children;
};