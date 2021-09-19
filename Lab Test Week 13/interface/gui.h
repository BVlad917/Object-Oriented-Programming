//
// Created by VladB on 24-May-21.
//

#ifndef T3_BVLAD917_GUI_H
#define T3_BVLAD917_GUI_H


#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include "../business/service.h"

class GUI : public QWidget {
Q_OBJECT
private:
    Service &srv;
    std::vector<TimeInterval> current_times;
    QVBoxLayout *main_layout{};
    QHBoxLayout *button_and_slider_layout{};
    QListWidget *times_list{};
    QPushButton *unfilter_button{};
    QSlider *slider{};
    QLabel* proba;
    std::vector<QCheckBox*> all_checks;

    std::vector<std::string> all_descriptions;

    void init_gui();

    void populate_list();

    void create_connections();

    void gui_filter();

    void set_slider_to_max();

    void check_all_boxes();

    void change_proba();

public:
    explicit GUI(Service &srv);
};


#endif //T3_BVLAD917_GUI_H
