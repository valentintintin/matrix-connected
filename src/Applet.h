#ifndef MATRIX_CONNECTED_APPLET_H
#define MATRIX_CONNECTED_APPLET_H


class Applet {
public:
    Applet();

    void onInit();
    void onPause();
    void OnResume();
    void onDestroy();

    bool hasSomethingToDo();
    void update();
    void refresh();
};


#endif //MATRIX_CONNECTED_APPLET_H
