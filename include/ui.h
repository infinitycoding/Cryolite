#include <SDL.h>
#include <List.h>

class CheckBox
{
    public:
        CheckBox *object;

        CheckBox();
        ~CheckBox();

        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;

        bool visible;
        bool activ;
        bool focus;

        bool checked;

        int x,y;
        int height,width;

        SDL_Color background,content,focusborder, border;
        char *descrition;
        SDL_Surface *image;


};


class Button
{
    public:
        Button *object;

        Button();
        ~Button();
        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;

        bool visible;
        bool activ;
        bool focus;
        int x,y;
        int height,width;
        SDL_Color background,Font,focusborder, border;
        char *descrition;
        char *title;
        SDL_Surface *image;
};

class Tab
{
    public:
        Tab *object;

        Tab();
        ~Tab();

        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;

        bool visible;
        bool activ;
        bool focus;
        char *descrition;
        char *title;

        int fieldX,fieldY;
        int fieldHeight,fielWidth;

        SDL_Color background, Font, focusborder, tab, tabfocus;

        SDL_Surface *backgroundImage;

        List<Button> *Buttons;
        List<Tab> *TabArrays;
        List<CheckBox> *CheckBoxes;


};

class TabArray
{
    public:
        TabArray *object;

        TabArray();
        ~TabArray();
        int addTab(Tab *T);
        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;

        bool visible;
        bool activ;
        bool focus;
        int borderWidth;

        int posX, posY;
        int width,height;

        int barX, barY;
        int tabWidth, tabHeight;
        bool horizontal;

        SDL_Color background, Font, focusborder, border;
        SDL_Surface *backgroundImage;

        List<Tab> *Tabs;
};


class Option
{
    public:
        Option *object;

        Option();
        ~Option();

        virtual void mouseover();
        virtual void onSelection();

        bool activMouseOver;
        bool activSelected;

        bool visible;
        bool selected;

        char *title;
        char *description;
};


class Selection
{
    public:
        Selection *object;

        Selection();
        ~Selection();

        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();
        virtual void onchange();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;
        bool activOnchange;

        bool visible;
        bool activ;
        bool focus;
        bool folded;

        int posX, posY;
        int width,height;

        SDL_Color background, Font, focusentry, border;
        SDL_Surface *backgroundImage;

        Option *selectedOption;
        List<Option> *options;
};

class Text
{
    public:
        Text *object;

        Text();
        ~Text();

        virtual void onclick();
        virtual void mouseover();

        bool activOnclick;
        bool activMouseover;

        bool visible;
        bool folded;
        bool activ;

        int posX, posY;
        int width,height;

        int fontsize;

        SDL_Color background, Font, border;

        char *content;
        char *description;
};

class Image
{
    public:
        Image *object;

        Image();
        ~Image();
        virtual void onclick();
        virtual void mouseover();
        virtual void onfocus();

        bool activOnclick;
        bool activMouseover;
        bool activOnfocus;

        int posX, posY;
        int width,height;

        bool visible;
        bool activ;
        bool focus;

        char *description;

        SDL_Surface *background;
};



class UI
{
    UI();
    UI(char *layout);
    ~UI();

    int loadLayout(char* layout);
    int addButton(Button *B);
    int addTabArray(TabArray *A);
    int addCheckBox(CheckBox *C);
    int addSelection(Selection *S);
    int addText(Text *T);
    int addImage(Image *I);


    SDL_Surface *renderSurface();
    GLuint       renderTexture();
};
