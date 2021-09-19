//
// Created by VladB on 24-May-21.
//

#include <set>
#include <iostream>
#include "gui.h"

GUI::GUI(Service &srv): srv{srv} {
    this->init_gui();
    this->create_connections();
    this->populate_list();

}

void GUI::init_gui() {
    this->main_layout = new QVBoxLayout{this};
    this->button_and_slider_layout = new QHBoxLayout{};

    this->times_list = new QListWidget{};
    this->main_layout->addWidget(this->times_list);

    this->proba = new QLabel{"0%"};

    this->unfilter_button = new QPushButton{"Unfilter"};
    this->slider = new QSlider{Qt::Horizontal};
    this->slider->setRange(0, 100);

    this->button_and_slider_layout->addWidget(this->proba);

    this->button_and_slider_layout->addWidget(this->slider);
    this->button_and_slider_layout->addWidget(this->unfilter_button);
    this->main_layout->addLayout(this->button_and_slider_layout);

    this->all_descriptions = this->srv.srv_get_all_descriptions();
    for (auto& desc: all_descriptions) {
        this->all_checks.push_back(new QCheckBox{QString::fromStdString(desc)});
    }

    for (auto& check: all_checks) {
        this->main_layout->addWidget(check);
    }
}

void GUI::populate_list() {
    this->times_list->clear();
    std::vector<TimeInterval> all_times = this->srv.srv_get_all_times();
    std::string aux;
    for (auto& time: all_times) {
        aux = std::to_string(time.getStart()) + " -> " + std::to_string(time.getAnEnd()) + "; " + std::to_string(time.getProbability()) + "%; " + time.getDescription();
        this->times_list->addItem(QString::fromStdString(aux));
    }
}

void GUI::create_connections() {
    QObject::connect(this->slider, &QSlider::valueChanged, this, &GUI::gui_filter);
    QObject::connect(this->slider, &QSlider::valueChanged, this, &GUI::change_proba);
    QObject::connect(this->unfilter_button, &QPushButton::clicked, this, &GUI::populate_list);
    QObject::connect(this->unfilter_button, &QPushButton::clicked, this, &GUI::set_slider_to_max);
    QObject::connect(this->unfilter_button, &QPushButton::clicked, this, &GUI::check_all_boxes);
    for (auto& check: this->all_checks) {
        QObject::connect(check, &QCheckBox::stateChanged, this, &GUI::gui_filter);
    }
}

void GUI::gui_filter() {
    int p = this->slider->value();
    this->times_list->clear();
    std::vector<TimeInterval> filtered_by_prob = this->srv.srv_filter_by_probability(p);
    this->current_times = filtered_by_prob;

    std::vector<TimeInterval> filtered_by_desc;
    std::vector<TimeInterval> all_times = this->srv.srv_get_all_times();
    for (int i = 0; i < all_times.size(); i++) {
        for (auto& check: this->all_checks) {
            if (check->isChecked() && check->text().toStdString() == all_times[i].getDescription()) {
                filtered_by_desc.push_back(all_times[i]);
                break;
            }
        }
    }

    std::vector<TimeInterval> final;
    for (auto& t1: filtered_by_prob) {
        for (auto& t2: filtered_by_desc) {
            if (t1.getDescription() == t2.getDescription() && t1.getProbability() == t2.getProbability() &&
            t1.getStart() == t2.getStart() && t1.getAnEnd() == t2.getAnEnd()) {
                final.push_back(t1);
            }
        }
    }

    std::string aux;
    for (auto& time: final) {
        aux = std::to_string(time.getStart()) + " -> " + std::to_string(time.getAnEnd()) + "; " + std::to_string(time.getProbability()) + "%; " + time.getDescription();
        this->times_list->addItem(QString::fromStdString(aux));
    }
}

void GUI::set_slider_to_max() {
    this->slider->setValue(100);
}

void GUI::check_all_boxes() {
    for (auto& check: this->all_checks) {
        check->setChecked(true);
    }
}

void GUI::change_proba() {
    int p = this->slider->value();
    std::string aux = std::to_string(p) + "%";
    this->proba->setText(QString::fromStdString(aux));
}
