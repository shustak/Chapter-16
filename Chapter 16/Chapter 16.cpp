#include <iostream>
#include "Simple_window.h"
#include "Graph.h"

struct Lines_window : Window {
    Lines_window(Point xy, int w, int h, const string& title);

private:

    Open_polyline lines;

    Button next_button; 
    Button quit_button; 
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    //line color menu and button
    Menu color_menu;
    Button menu_button;
    //line style menu and button
    Button style_button;
    Menu line_style_menu;
              
    void next();
    void quit();

    void linecolor_hide();
    void linestyle_hide();

    //Change line colors
    void change(Color c) { lines.set_color(c); }
    void color_menu_pressed() { color_menu.show(); menu_button.hide();}

    void red_pressed() { change(Color::red); linecolor_hide();}
    void blue_pressed() { change(Color::blue); linecolor_hide(); }
    void black_pressed() { change(Color::black); linecolor_hide(); }

    //Change line style
    void change_line(Line_style c) { lines.set_style(c); }
    void line_style_menu_pressed() {line_style_menu.show(); style_button.hide();}

    void dash_pressed() { change_line(Line_style::dash); linestyle_hide();}
    void dot_pressed() { change_line(Line_style::dot); linestyle_hide();}
    void dashdot_pressed() { change_line(Line_style::dashdot); linestyle_hide();}
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    :Window{ xy, w, h, title },
    next_button{Point{x_max() - 150, 0}, 70, 20, "Next point",
        [](Address, Address pw)
            {
                reference_to<Lines_window>(pw).next(); 
            }
        },
    quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
        [](Address, Address pw)
            {
                reference_to<Lines_window>(pw).quit();
            }
        },
    
    next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
    next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
    xy_out{Point{100, 0}, 100, 20, "current (x,y):"},

    //line color menu
    color_menu{ Point{x_max() - 70, 30}, 70, 20, Menu::vertical, "color" },
    menu_button{ Point{x_max() - 80, 30}, 80, 20,"color menu",
         [](Address, Address pw)
             {
                  reference_to<Lines_window>(pw).color_menu_pressed();
             }
         },

    //line style menu
    line_style_menu{Point{x_max() - 70, 100}, 70, 20, Menu::vertical, "style" },
    style_button{Point{x_max() - 80, 110}, 80, 20,"style menu",
         [](Address, Address pw)
            {
                reference_to<Lines_window>(pw).line_style_menu_pressed();
            }
}

{
    //lines.set_color(Color::black); //I've added black color for lines.

    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no points");

    //color
    color_menu.attach(new Button{ Point{0, 0}, 0, 0, "red",
        [](Address, Address pw)
             {
                reference_to<Lines_window>(pw).red_pressed();
             }
    });
    color_menu.attach(new Button{ Point{0, 0}, 0, 0, "blue",
        [](Address, Address pw)
             {
                reference_to<Lines_window>(pw).blue_pressed();
             } 
    });
    color_menu.attach(new Button{ Point{0, 0}, 0, 0, "black",
        [](Address, Address pw)
             {
                reference_to<Lines_window>(pw).black_pressed();
             }
    });

    attach(color_menu);
    color_menu.hide();
    attach(menu_button);
    attach(lines);

    //style
    line_style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dash",
        [](Address, Address pw)
             {
                reference_to<Lines_window>(pw).dash_pressed(); 
             }
        });
    line_style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dot",
        [](Address, Address pw)
            {
                reference_to<Lines_window>(pw).dot_pressed(); 
            }
        });
    line_style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dash_dot",
        [](Address, Address pw)
            {
                reference_to<Lines_window>(pw).dashdot_pressed();
            }
        });

    attach(line_style_menu);
    line_style_menu.hide();
    attach(style_button);
}

//hide line style menu after selection line style
void Lines_window::linestyle_hide()
{
    line_style_menu.hide(); style_button.show();
}

//hide line color menu after selection line color
void Lines_window::linecolor_hide()
{
    color_menu.hide(); menu_button.show();
}

 void Lines_window::quit()
{
     hide();
}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();
    lines.add(Point{ x, y });

    ostringstream ss;
    ss << '(' << x <<',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}


int main()
{
    try {
        Lines_window win{ Point{100, 100}, 600, 400, "lines" };
        return gui_main();
    }
    catch (exception& e) {
        cerr << "Exception: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "Some Exception\n";
        return 2;
    }
}
