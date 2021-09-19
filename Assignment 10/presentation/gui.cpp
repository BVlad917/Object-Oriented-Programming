//
// Created by VladB on 04-May-21.
//

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <map>
#include "gui.h"
#include "../errors/exceptions.h"
#include "../utils/size_filter.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereferences"
GUI::GUI(Service &srv) : srv{srv} {
    this->init_gui();
    this->populate_repository_list();
    this->gui_create_statistics();
    this->connect_signals_and_slots();
}

void GUI::init_gui() {
    this->setWindowTitle("Proper Trench Coats");    // Set the title of the app
    this->font = QFont{"Hallo Sans", 10, 50}; // A font we will use for the labels
    // Set the initial size of the app (according to the screen size)
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize((int) ((double) (width / 1.6)), (int) ((double) (height / 1.7)));

    // Set the layout of the class object and create the tab layout for the 3 tabs
    this->tab_layout = new QHBoxLayout{this};
    this->tab_widget = new QTabWidget{};
    this->tab_layout->addWidget(this->tab_widget);

    // Create the widgets for the 3 tabs (User, Admin, Statistics)
    this->user_widget = new QWidget{};
    this->admin_widget = new QWidget{};
    this->statistics_widget = new QWidget{};

    // Set the layout for the 3 widgets
    this->user_layout = new QHBoxLayout{this->user_widget};
    this->admin_layout = new QGridLayout{this->admin_widget};
    this->statistics_layout = new QVBoxLayout{this->statistics_widget};

    // Add the 3 widgets in the tab widget
    this->tab_widget->addTab(this->user_widget, "&User");
    this->tab_widget->addTab(this->admin_widget, "&Admin");
    this->tab_widget->addTab(this->statistics_widget, "&Statistics");

    // ==============================
    // ===== FOR THE ADMIN MODE =====
    // ==============================
    // Text fields for the Admin mode; Using these the client can add, remove, and update trench coats
    this->admin_text_fields_layout = new QFormLayout{};
    this->admin_size_field = new QLineEdit{};
    this->admin_colour_field = new QLineEdit{};
    this->admin_price_field = new QLineEdit{};
    this->admin_quantity_field = new QLineEdit{};
    this->admin_link_field = new QLineEdit{};
    this->admin_text_fields_layout->addRow("Size", this->admin_size_field);
    this->admin_text_fields_layout->addRow("Colour", this->admin_colour_field);
    this->admin_text_fields_layout->addRow("Price", this->admin_price_field);
    this->admin_text_fields_layout->addRow("Quantity", this->admin_quantity_field);
    this->admin_text_fields_layout->addRow("Link", this->admin_link_field);

    // Final step: Add this layout (with all of the above line edits in it) to the admin layout
    this->admin_layout->addLayout(this->admin_text_fields_layout, 0, 0);

    // Create a widget list for displaying the trench coats in the Admin mode
    this->admin_list_of_coats = new QListWidget{};
    // Create a label that will be used as the title for the above list
    this->admin_title_of_list_of_coats = new QLabel("Trench Coats");
    this->admin_title_of_list_of_coats->setFont(this->font);
    // The above list and label will be put into the below grid layout
    this->admin_list_and_title_layout = new QVBoxLayout{};
    this->admin_list_and_title_layout->addWidget(this->admin_title_of_list_of_coats, 0, Qt::AlignCenter);
    this->admin_list_and_title_layout->addWidget(this->admin_list_of_coats);
    // Final step: Add this grid layout (with the title label and the widget list in it) to the admin layout
    this->admin_layout->addLayout(this->admin_list_and_title_layout, 0, 1, 2, 1);

    // Add the 4 buttons available for the Admin mode: Add, Remove, Update, and Display table
    this->admin_buttons_layout = new QGridLayout{};
    this->admin_add_button = new QPushButton("Add");
    this->admin_add_button->setToolTip("Add a trench coat to the repository");
    this->admin_add_button->setToolTipDuration(5000);

    this->admin_remove_button = new QPushButton("Remove");
    this->admin_remove_button->setToolTip("Remove a trench coat from the repository");
    this->admin_remove_button->setToolTipDuration(5000);

    this->admin_update_button = new QPushButton("Update");
    this->admin_update_button->setToolTip("Update a trench coat from the repository");
    this->admin_update_button->setToolTipDuration(5000);

    this->admin_undo_button = new QPushButton("Undo");
    this->admin_undo_button->setToolTip("Undo the last performed operation");
    this->admin_undo_button->setToolTipDuration(5000);

    this->admin_redo_button = new QPushButton("Redo");
    this->admin_redo_button->setToolTip("Redo the last performed undo");
    this->admin_redo_button->setToolTipDuration(5000);

    this->admin_buttons_layout->addWidget(this->admin_add_button, 0, 0);
    this->admin_buttons_layout->addWidget(this->admin_remove_button, 0, 1);
    this->admin_buttons_layout->addWidget(this->admin_update_button, 0, 2);
    this->admin_undo_redo_layout = new QHBoxLayout();
    this->admin_undo_redo_layout->addWidget(this->admin_undo_button);
    this->admin_undo_redo_layout->addWidget(this->admin_redo_button);
    this->admin_buttons_layout->addLayout(this->admin_undo_redo_layout, 1, 0, 1, 3);

    // Final step: Add this layout (with all of the above buttons in it) to the admin layout
    this->admin_layout->addLayout(this->admin_buttons_layout, 1, 0);

    // =============================
    // ===== FOR THE USER MODE =====
    // =============================
    // Create the left side layout for the User Mode
    // It will contain a title (as a label), a list, a filter button + a field for the filter button
    this->user_left_side_layout = new QVBoxLayout{};
    this->user_one_by_one_title = new QLabel("Filtered By Size");   // The label
    this->user_one_by_one_title->setFont(this->font);
    this->user_one_by_one_list = new QListWidget{};   // The list
    // The filter button + its corresponding field (both put in a horizontal layout)
    this->user_filter_layout = new QHBoxLayout{};
    this->user_filter_field = new QLineEdit{};
    this->user_filter_button = new QPushButton("Filter");
    this->user_filter_button->setToolTip("Filter the coats by the given size");
    this->user_filter_button->setToolTipDuration(5000);
    this->user_filter_layout->addWidget(this->user_filter_button);
    this->user_filter_layout->addWidget(this->user_filter_field);
    // Add the above created title, list, and filter to the left side layout
    this->user_left_side_layout->addWidget(this->user_one_by_one_title, 0, Qt::AlignCenter);
    this->user_left_side_layout->addWidget(this->user_one_by_one_list);
    this->user_left_side_layout->addLayout(this->user_filter_layout);
    // Final step: Add the left side layout (with the above title, list, and filter) to the user layout
    this->user_layout->addLayout(this->user_left_side_layout);

    // Create the middle layout for the User Mode
    this->user_middle_layout = new QVBoxLayout{};
    // It will contain 4 buttons: "Add to cart", "Next", "Open Current" and "Open(CSV/HTML)"
    this->user_add_to_cart_button = new QPushButton("Add to cart");
    this->user_add_to_cart_button->setToolTip("Save the current coat to the basket");
    this->user_add_to_cart_button->setToolTipDuration(5000);

    this->user_remove_from_cart_button = new QPushButton("Remove from cart");
    this->user_remove_from_cart_button->setToolTip("Remove the selected coat from the shopping basket");
    this->user_remove_from_cart_button->setToolTipDuration(5000);

    this->user_open_current_coat_button = new QPushButton("Open Current");
    this->user_open_current_coat_button->setToolTip("Open the web page of the current coat");
    this->user_open_current_coat_button->setToolTipDuration(5000);

    this->user_next_button = new QPushButton("Next");
    this->user_next_button->setToolTip("Go to the next filtered coat");
    this->user_next_button->setToolTipDuration(5000);

    this->user_open_basket_button = new QPushButton("Open(CSV/HTML)");
    this->user_open_basket_button->setToolTip("Open the basket as an external file");
    this->user_open_basket_button->setToolTipDuration(5000);

    // Set the alignment of the middle layout such that the buttons will be close to each other, and not far apart
    this->user_middle_layout->setAlignment(Qt::AlignCenter);
    // Add the above created buttons to the middle layout
    this->user_middle_layout->addWidget(this->user_next_button, 0, Qt::AlignCenter);
    this->user_middle_layout->addWidget(this->user_add_to_cart_button, 0, Qt::AlignCenter);
    this->user_middle_layout->addWidget(this->user_open_current_coat_button, 0, Qt::AlignCenter);
    this->user_middle_layout->addWidget(this->user_open_basket_button, 0, Qt::AlignCenter);
    this->user_middle_layout->addWidget(this->user_remove_from_cart_button, 0, Qt::AlignCenter);

    // Final step: Add the middle layout (with the above 3 buttons) to the user layout
    this->user_layout->addLayout(this->user_middle_layout);

    // Create the right side layout for the User Mode
    // It will contain a title (as a label), a list, and a bottom label for displaying the cart total
    // + It will also contain the undo/redo buttons
    this->user_right_side_layout = new QVBoxLayout{};
    this->user_basket_title = new QLabel("Shopping Basket");
    this->user_basket_title->setFont(this->font);
    this->user_basket_list = new QListWidget{};
    this->user_label_layout = new QHBoxLayout{};
    this->user_basket_total_label = new QLabel("Total: 0$");
    this->user_basket_total_label->setFont(this->font);
    this->user_undo_button = new QPushButton("Undo");
    this->user_undo_button->setToolTip("Undo the last performed operation");
    this->user_undo_button->setToolTipDuration(5000);
    this->user_redo_button = new QPushButton("Redo");
    this->user_redo_button->setToolTip("Redo the last performed undo");
    this->user_redo_button->setToolTipDuration(5000);
    this->user_open_basket_table_view_button = new QPushButton("TableView");
    this->user_open_basket_table_view_button->setToolTip("See the shopping cart in a table.");
    this->user_open_basket_table_view_button->setToolTipDuration(5000);

    this->user_label_layout->addWidget(this->user_undo_button);
    this->user_label_layout->addWidget(this->user_redo_button);
    this->user_label_layout->addWidget(this->user_open_basket_table_view_button);
    this->user_label_layout->addWidget(this->user_basket_total_label, 0, Qt::AlignRight);
    // Add the above created title label, basket list, and total label to the right side layout
    this->user_right_side_layout->addWidget(this->user_basket_title, 0, Qt::AlignCenter);
    this->user_right_side_layout->addWidget(this->user_basket_list);
    this->user_right_side_layout->addLayout(this->user_label_layout);
    // Final step: Add the right side layout (with the above 2 labels and one list) to the user layout
    this->user_layout->addLayout(this->user_right_side_layout);

    // ==============================
    // ===== FOR THE STATISTICS =====
    // ==============================
    // Create the chart and set its title and animation
    this->chart = new QChart{};
    this->chart_view = new QChartView{this->chart};
    this->chart->setAnimationOptions(QChart::SeriesAnimations);
    this->chart->setTitle("Trench Coats by Size");
    this->chart->setTitleFont(this->font);
    this->chart->setFont(this->font);
    this->chart->legend()->setVisible(true);
    this->chart->legend()->setAlignment(Qt::AlignRight);
    this->chart->legend()->setFont(this->font);
    this->chart_series = new QPieSeries{};
    this->chart->addSeries(this->chart_series);
    this->chart_view->setRenderHint(QPainter::Antialiasing);
    this->statistics_layout->addWidget(this->chart_view);   // Add the chart view to the statistics layout

    // ==============================
    // ===== FOR THE TABLE VIEW =====
    // ==============================
    this->coats_table_model = new CoatsTableModel{this->srv};
    this->coats_widget = new CoatsWidget{this->coats_table_model};
    this->coats_widget->setWindowModality(Qt::ApplicationModal);
}

void GUI::gui_show_shopping_basket_table_view() {
    this->coats_widget->show();
}

void GUI::gui_update_shopping_basket_table_view_width() {
    this->coats_widget->update_table_columns_width();
}

void GUI::populate_repository_list() {
    this->admin_list_of_coats->clear();
    std::vector<TrenchCoat> all_coats = this->srv.get_all_trenches_from_repo();
    std::string aux;
    for (TrenchCoat &t: all_coats) {
        aux = t.get_trench_size() + " - " + t.get_trench_colour();
        this->admin_list_of_coats->addItem(QString::fromStdString(aux));
    }
}

void GUI::populate_shopping_basket_list() {
    this->user_basket_list->clear();
    std::vector<TrenchCoat> shopping_cart_coats = this->srv.get_all_trenches_from_shopping_cart();
    std::string aux;
    int i = 1;
    for (TrenchCoat &t: shopping_cart_coats) {
        aux = std::to_string(i) + ") Proper Trench Coat " + t.get_trench_size() + ", " + t.get_trench_colour() + "\n";
        char price[10];
        sprintf(price, "%.2f", t.get_trench_price());
        aux += "     Price: " + std::string(price) + "$\n";
        aux += "     Quantity: " + std::to_string(t.get_trench_quantity()) + " units\n";
        aux += "     Store Link: " + t.get_trench_photograph();
        this->user_basket_list->addItem(QString::fromStdString(aux));
        i++;
    }
    // Now we need to update the "Total" label
    double total_price = this->srv.get_total_price();
    // We round the total price to 2 decimal places
    char total_as_char_array[10];
    sprintf(total_as_char_array, "%.2f", total_price);
    std::string total_price_string = std::string(total_as_char_array);
    // We change the old label to have as text the updated total price
    std::string new_total_label_string = "Total: " + total_price_string + "$";
    this->user_basket_total_label->setText(QString::fromStdString(new_total_label_string));
}

void GUI::refresh_current_filtered_coat() {
    if (this->filtered_coats.empty()) {
        return;
    }
    // First clear the previous filtered trench coats
    this->user_one_by_one_list->clear();
    // We need to re-filter. We will again call the filter function to get a new vector in this->filtered_coats.
    // This way we will get the updated versions of the coats.
    std::string filter_size = this->user_filter_field->text().toStdString();
    if (!filter_size.empty()) {
        TrenchCoat dummy_coat{filter_size, "blue", 1, 1, "dummy_link"};
        try {
            TrenchCoatValidator::validate(dummy_coat);
        }
        catch (ValidationException& ve) {
            QMessageBox::critical(this, "Error",  ve.what());
            return;
        }
    }
    SizeFilter filter{filter_size};
    this->filtered_coats = this->srv.filter_by(filter);
    // Now we can rewrite the currently filtered coat in the left list as well
    this->rewrite_current_filtered_coat();
}

void GUI::rewrite_current_filtered_coat() {
    // First clear the previous filtered trench coats
    this->user_one_by_one_list->clear();
    if (this->filtered_coats.empty()) {
        return;
    }
    if (this->current_filtered_coat_index == this->filtered_coats.size()) {
        this->current_filtered_coat_index = 0;
    }
    TrenchCoat current_coat = this->filtered_coats[this->current_filtered_coat_index];
    std::string output_string = std::to_string(this->current_filtered_coat_index + 1) + ") Proper Trench Coat\n";
    output_string += "     Size: " + current_coat.get_trench_size() + "\n";
    output_string += "     Colour: " + current_coat.get_trench_colour() + "\n";
    char price[10];
    sprintf(price, "%.2f", current_coat.get_trench_price());
    output_string += "     Price: " + std::string(price) + "$\n";
    output_string += "     Quantity: " + std::to_string(current_coat.get_trench_quantity()) + " units\n";
    output_string += "     Store Link: " + current_coat.get_trench_photograph();
    this->user_one_by_one_list->addItem(QString::fromStdString(output_string));
}

void GUI::connect_signals_and_slots() {
    QObject::connect(this->admin_list_of_coats, &QListWidget::itemSelectionChanged, this, &GUI::gui_fill_admin_line_edits_when_selected);
    //QObject::connect(this->admin_add_button, &QPushButton::clicked, this, &GUI::gui_add_trench_coat);
    //QObject::connect(this->admin_remove_button, &QPushButton::clicked, this, &GUI::gui_remove_trench_coat);
    //QObject::connect(this->admin_update_button, &QPushButton::clicked, this, &GUI::gui_update_trench_coat);
    QObject::connect(this->admin_list_of_coats, &QListWidget::itemDoubleClicked, this, &GUI::gui_deselect_admin_list_on_double_click);
    QObject::connect(this->user_filter_button, &QPushButton::clicked, this, &GUI::gui_filter_coats);
    QObject::connect(this->user_next_button, &QPushButton::clicked, this, &GUI::gui_next_filtered_coat);
    QObject::connect(this->user_add_to_cart_button, &QPushButton::clicked, this, &GUI::gui_add_filtered_coat_to_shopping_cart);
    QObject::connect(this->user_remove_from_cart_button, &QPushButton::clicked, this, &GUI::gui_remove_coat_from_shopping_cart);
    QObject::connect(this->user_open_basket_button, &QPushButton::clicked, this, &GUI::gui_open_shopping_cart_file);
    QObject::connect(this->user_open_current_coat_button, &QPushButton::clicked, this, &GUI::gui_open_current_filtered_coat);

    QObject::connect(this->user_basket_list, &QListWidget::itemDoubleClicked, this, &GUI::gui_deselect_user_shopping_basket_list_on_double_click);
    QObject::connect(this->user_one_by_one_list, &QListWidget::itemDoubleClicked, this, &GUI::gui_deselect_user_filter_list_on_double_click);

    QObject::connect(this->admin_add_button, &QPushButton::clicked, this, &GUI::add_coat_button_handler);
    QObject::connect(this, SIGNAL(add_coat_signal(const std::string&, const std::string&, double, int, const std::string&)),
                     this, SLOT(add_coat_slot(const std::string&, const std::string&, double, int, const std::string&)));

    QObject::connect(this->admin_remove_button, &QPushButton::clicked, this, &GUI::remove_coat_button_handler);
    QObject::connect(this, SIGNAL(remove_coat_signal(int)), this, SLOT(remove_coat_slot(int)));

    QObject::connect(this->admin_update_button, &QPushButton::clicked, this, &GUI::update_coat_button_handler);
    QObject::connect(this, SIGNAL(update_coat_signal(int)), this, SLOT(update_coat_slot(int)));
    QObject::connect(this->admin_update_button, &QPushButton::clicked, this, &GUI::populate_shopping_basket_list);
    QObject::connect(this->admin_update_button, &QPushButton::clicked, this, &GUI::refresh_current_filtered_coat);

    QObject::connect(this, &GUI::coats_updated_signal, this, &GUI::populate_repository_list);
    QObject::connect(this, &GUI::coats_updated_signal, this, &GUI::gui_create_statistics);

    // Below we will connect all of the undo-redo related buttons (user & admin)
    // Admin
    QObject::connect(this->admin_undo_button, &QPushButton::clicked, this, &GUI::gui_admin_undo);
    QObject::connect(this->admin_redo_button, &QPushButton::clicked, this, &GUI::gui_admin_redo);

    QShortcut *admin_undo_shortcut = new QShortcut{QKeySequence("CTRL+Z"), this->admin_widget};
    QShortcut *admin_redo_shortcut = new QShortcut{QKeySequence("CTRL+SHIFT+Z"), this->admin_widget};
    QObject::connect(admin_undo_shortcut, &QShortcut::activated, this, &GUI::gui_admin_undo);
    QObject::connect(admin_redo_shortcut, &QShortcut::activated, this, &GUI::gui_admin_redo);

    // User
    QObject::connect(this->user_undo_button, &QPushButton::clicked, this, &GUI::gui_user_undo);
    QObject::connect(this->user_redo_button, &QPushButton::clicked, this, &GUI::gui_user_redo);

    QShortcut *user_undo_shortcut = new QShortcut{QKeySequence("CTRL+Z"), this->user_widget};
    QShortcut *user_redo_shortcut = new QShortcut{QKeySequence("CTRL+SHIFT+Z"), this->user_widget};
    QObject::connect(user_undo_shortcut, &QShortcut::activated, this, &GUI::gui_user_undo);
    QObject::connect(user_redo_shortcut, &QShortcut::activated, this, &GUI::gui_user_redo);

    QObject::connect(this->user_open_basket_table_view_button, &QPushButton::clicked, this, &GUI::gui_show_shopping_basket_table_view);
}

int GUI::get_selected_index_from_admin_list() const {
    QModelIndexList selected_indexes = this->admin_list_of_coats->selectionModel()->selectedIndexes();
    if (selected_indexes.size() != 1) {
        this->admin_size_field->clear();
        this->admin_colour_field->clear();
        this->admin_price_field->clear();
        this->admin_quantity_field->clear();
        this->admin_link_field->clear();
        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

int GUI::get_selected_index_from_shopping_basket_list() const {
    QModelIndexList selected_indexes = this->user_basket_list->selectionModel()->selectedIndexes();
    if (selected_indexes.size() != 1) {
        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}

void GUI::gui_fill_admin_line_edits_when_selected() {
    int selected_index = this->get_selected_index_from_admin_list();
    if (selected_index < 0) {
        return;
    }
    TrenchCoat t = this->srv.get_all_trenches_from_repo()[selected_index];
    this->admin_size_field->setText(QString::fromStdString(t.get_trench_size()));
    this->admin_colour_field->setText(QString::fromStdString(t.get_trench_colour()));
    this->admin_price_field->setText(QString::number(t.get_trench_price()));
    this->admin_quantity_field->setText(QString::number(t.get_trench_quantity()));
    this->admin_link_field->setText(QString::fromStdString(t.get_trench_photograph()));
}

void GUI::gui_deselect_admin_list_on_double_click(QListWidgetItem* itemClicked) {
    int selected_index = this->get_selected_index_from_admin_list();
    if (selected_index < 0) {
        return;
    }
    int row_of_clicked_item = this->admin_list_of_coats->row(itemClicked);
    if (selected_index == row_of_clicked_item) {
        this->admin_list_of_coats->clearSelection();
    }
}

void GUI::gui_deselect_user_filter_list_on_double_click(QListWidgetItem *itemClicked) {
    if (this->user_one_by_one_list->count() == 0) {
        return;
    }
    this->user_one_by_one_list->clearSelection();
}

void GUI::gui_deselect_user_shopping_basket_list_on_double_click(QListWidgetItem *itemClicked) {
    int selected_index = this->get_selected_index_from_shopping_basket_list();
    if (selected_index < 0) {
        return;
    }
    int row_of_clicked_item = this->user_basket_list->row(itemClicked);
    if (selected_index == row_of_clicked_item) {
        this->user_basket_list->clearSelection();
    }
}

void GUI::add_coat_button_handler() {
    std::string size = this->admin_size_field->text().toStdString();
    std::string colour = this->admin_colour_field->text().toStdString();
    double price = this->admin_price_field->text().toDouble();
    int quantity = this->admin_quantity_field->text().toInt();
    std::string photo_link = this->admin_link_field->text().toStdString();
    emit this->add_coat_signal(size, colour, price, quantity, photo_link);
}

void GUI::add_coat_slot(const std::string &size, const std::string &colour, double price, int quantity, const std::string &photo) {
    try {
        this->srv.add_trench(size, colour, price, quantity, photo);
    }
    catch (ValidationException& ve) {
        QMessageBox::critical(this, "Error", ve.what());
        return;
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
        return;
    }
    emit this->coats_updated_signal();
    // Set the selection on the currently added trench coat
    int last_element_index = (int) (this->srv.get_all_trenches_from_repo().size() - 1);
    this->admin_list_of_coats->setCurrentRow(last_element_index);
}

void GUI::remove_coat_button_handler() {
    int selected_index = this->get_selected_index_from_admin_list();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "No item selected.");
        return;
    }
    emit this->remove_coat_signal(selected_index);
}

void GUI::remove_coat_slot(int index) {
    TrenchCoat selected_coat = this->srv.get_all_trenches_from_repo()[index];
    this->srv.remove_trench(selected_coat.get_trench_size(), selected_coat.get_trench_colour());
    emit this->coats_updated_signal();
}

void GUI::update_coat_button_handler() {
    int selected_index = this->get_selected_index_from_admin_list();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Error", "No item selected.");
        return;
    }
    emit this->update_coat_signal(selected_index);
}

void GUI::update_coat_slot(int index) {
    // If we have an item selected, then we update that selected item with what is in the line edits
    // Use the size and colour (the identifiers) of the currently selected item
    TrenchCoat selected_coat = this->srv.get_all_trenches_from_repo()[index];
    std::string size = selected_coat.get_trench_size();
    std::string colour = selected_coat.get_trench_colour();
    // Get the price, quantity, and photo_link (all possibly new) from the line edits
    double price = this->admin_price_field->text().toDouble();
    int quantity = this->admin_quantity_field->text().toInt();
    std::string photo_link = this->admin_link_field->text().toStdString();
    if (price == selected_coat.get_trench_price() && quantity == selected_coat.get_trench_quantity() &&
        photo_link == selected_coat.get_trench_photograph()) {
        QMessageBox::information(this, "Update", "Nothing to update.");
    }
    try {
        this->srv.update_trench(size, colour, price, quantity, photo_link);
    }
    catch (ValidationException& ve) {
        QMessageBox::critical(this, "Error", ve.what());
        return;
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
        return;
    }
    emit this->coats_updated_signal();
    // We have to reselect the item
    this->admin_list_of_coats->setCurrentRow(index);
    // Display a message if the update was successful
    QMessageBox::information(this, "Update", "Item updated.");
}

//void GUI::gui_add_trench_coat() {
//    std::string size = this->admin_size_field->text().toStdString();
//    std::string colour = this->admin_colour_field->text().toStdString();
//    double price = this->admin_price_field->text().toDouble();
//    int quantity = this->admin_quantity_field->text().toInt();
//    std::string photo_link = this->admin_link_field->text().toStdString();
//    try {
//        this->srv.add_trench(size, colour, price, quantity, photo_link);
//        // Don't forget to re-populate the list
//        this->populate_repository_list();
//        // Also update the Pie Chart
//        this->gui_create_statistics();
//        // Set the selection on the currently added trench coat
//        int last_element_index = (int) (this->srv.get_all_trenches_from_repo().size() - 1);
//        this->admin_list_of_coats->setCurrentRow(last_element_index);
//    }
//    catch (ValidationException& ve) {
//        QMessageBox::critical(this, "Error", ve.what());
//        return;
//    }
//    catch (RepositoryException& re) {
//        QMessageBox::critical(this, "Error", re.what());
//        return;
//    }
//}
//
//void GUI::gui_remove_trench_coat() {
//    int selected_index = this->get_selected_index_from_admin_list();
//    if (selected_index < 0) {
    //        QMessageBox::critical(this, "Error", "No item selected.");
    //        return;
//    }
//    TrenchCoat selected_coat = this->srv.get_all_trenches_from_repo()[selected_index];
//    this->srv.remove_trench(selected_coat.get_trench_size(), selected_coat.get_trench_colour());
//    // Don't forget to re-populate the list
//    this->populate_repository_list();
//    // Also update the Pie Chart
//    this->gui_create_statistics();
//}
//
//void GUI::gui_update_trench_coat() {
//    int selected_index = this->get_selected_index_from_admin_list();
//    if (selected_index < 0) {
//        QMessageBox::critical(this, "Error", "No item selected.");
//        return;
//    }
//    // If we have an item selected, then we update that selected item with what is in the line edits
//    // Use the size and colour (the identifiers) of the currently selected item
//    TrenchCoat selected_coat = this->srv.get_all_trenches_from_repo()[selected_index];
//    std::string size = selected_coat.get_trench_size();
//    std::string colour = selected_coat.get_trench_colour();
//    // Get the price, quantity, and photo_link (all possibly new) from the line edits
//    double price = this->admin_price_field->text().toDouble();
//    int quantity = this->admin_quantity_field->text().toInt();
//    std::string photo_link = this->admin_link_field->text().toStdString();
//    if (price == selected_coat.get_trench_price() && quantity == selected_coat.get_trench_quantity() &&
//        photo_link == selected_coat.get_trench_photograph()) {
//        QMessageBox::information(this, "Update", "Nothing to update.");
//        return;
//    }
//    try {
//        this->srv.update_trench(size, colour, price, quantity, photo_link);
//        // Don't forget to re-populate the list
//        this->populate_repository_list();
//        // Also update the Pie Chart
//        this->gui_create_statistics();
//        // We have to reselect the item
//        this->admin_list_of_coats->setCurrentRow(selected_index);
//        // Display a message if the update was successful
//        QMessageBox::information(this, "Update", "Item updated.");
//    }
//    catch (ValidationException& ve) {
//        QMessageBox::critical(this, "Error", ve.what());
//        return;
//    }
//    catch (RepositoryException& re) {
//        QMessageBox::critical(this, "Error", re.what());
//        return;
//    }
//}

void GUI::gui_filter_coats() {
    // First clear the previous filtered trench coats
    this->user_one_by_one_list->clear();
    std::string filter_size = this->user_filter_field->text().toStdString();
    if (!filter_size.empty()) {
        TrenchCoat dummy_coat{filter_size, "blue", 1, 1, "dummy_link"};
        try {
            TrenchCoatValidator::validate(dummy_coat);
        }
        catch (ValidationException& ve) {
            QMessageBox::critical(this, "Error",  ve.what());
            return;
        }
    }
    SizeFilter filter{filter_size};
    this->filtered_coats = this->srv.filter_by(filter);
    this->current_filtered_coat_index = 0;
    if (this->filtered_coats.empty()) {
        QMessageBox::warning(this, "Filter", "No trench coats with the given size.");
        return;
    }
    TrenchCoat first_coat = this->filtered_coats[this->current_filtered_coat_index];
    std::string output_string = "1) Proper Trench Coat\n";
    output_string += "     Size: " + first_coat.get_trench_size() + "\n";
    output_string += "     Colour: " + first_coat.get_trench_colour() + "\n";
    char price[10];
    sprintf(price, "%.2f", first_coat.get_trench_price());
    output_string += "     Price: " + std::string(price) + "$\n";
    output_string += "     Quantity: " + std::to_string(first_coat.get_trench_quantity()) + " units\n";
    output_string += "     Store Link: " + first_coat.get_trench_photograph();
    this->user_one_by_one_list->addItem(QString::fromStdString(output_string));
}

void GUI::gui_next_filtered_coat() {
    // First clear the previous filtered trench coats
    this->user_one_by_one_list->clear();
    this->current_filtered_coat_index += 1;
    if (this->current_filtered_coat_index == this->filtered_coats.size()) {
        this->current_filtered_coat_index = 0;
    }
    TrenchCoat current_coat = this->filtered_coats[this->current_filtered_coat_index];
    std::string output_string = std::to_string(this->current_filtered_coat_index + 1) + ") Proper Trench Coat\n";
    output_string += "     Size: " + current_coat.get_trench_size() + "\n";
    output_string += "     Colour: " + current_coat.get_trench_colour() + "\n";
    char price[10];
    sprintf(price, "%.2f", current_coat.get_trench_price());
    output_string += "     Price: " + std::string(price) + "$\n";
    output_string += "     Quantity: " + std::to_string(current_coat.get_trench_quantity()) + " units\n";
    output_string += "     Store Link: " + current_coat.get_trench_photograph();
    this->user_one_by_one_list->addItem(QString::fromStdString(output_string));
}

void GUI::gui_add_filtered_coat_to_shopping_cart() {
    if (this->filtered_coats.empty()) {
        QMessageBox::warning(this, "Shopping Cart", "No filter applied. Cannot add to shopping cart.");
        return;
    }
    try {
        this->srv.put_trench_in_shopping_cart(this->filtered_coats[this->current_filtered_coat_index]);
        // Now we need to refresh the shopping cart list
        this->populate_shopping_basket_list();
        emit this->coats_table_model->layoutChanged();
        this->gui_update_shopping_basket_table_view_width();
    }
    catch (RepositoryException& se) {
        QMessageBox::warning(this, "Error", se.what());
        return;
    }
}

void GUI::gui_remove_coat_from_shopping_cart() {
    int selected_index = this->get_selected_index_from_shopping_basket_list();
    if (selected_index < 0) {
        QMessageBox::critical(this, "Shopping Cart", "No shopping cart coat selected.");
        return;
    }
    TrenchCoat t = this->srv.get_all_trenches_from_shopping_cart()[selected_index];
    this->srv.remove_trench_from_shopping_cart(t);
    // Now we need to refresh the shopping cart list
    this->populate_shopping_basket_list();
    emit this->coats_table_model->layoutChanged();
    this->gui_update_shopping_basket_table_view_width();
}

void GUI::gui_open_shopping_cart_file() {
    this->srv.open_shopping_basket_file();
}

void GUI::gui_open_current_filtered_coat() {
    if (this->filtered_coats.empty()) {
        QMessageBox::warning(this, "Open Link", "Cannot open link. No trench coats filtered.");
        return;
    }
    TrenchCoat t = this->filtered_coats[this->current_filtered_coat_index];
    std::string open_web = "start " + t.get_trench_photograph();
    system(open_web.c_str());
}

void GUI::gui_admin_undo() {
    try {
        this->srv.admin_undo();
    }
    catch (ServiceException& se) {
        QMessageBox::critical(this, "Undo", se.what());
        return;
    }
    this->populate_repository_list();
    this->populate_shopping_basket_list();
    this->rewrite_current_filtered_coat();
    this->gui_create_statistics();
    emit this->coats_table_model->layoutChanged();
    this->gui_update_shopping_basket_table_view_width();
}

void GUI::gui_admin_redo() {
    try {
        this->srv.admin_redo();
    }
    catch (ServiceException& se) {
        QMessageBox::critical(this, "Redo", se.what());
        return;
    }
    this->populate_repository_list();
    this->populate_shopping_basket_list();
    this->rewrite_current_filtered_coat();
    this->gui_create_statistics();
    emit this->coats_table_model->layoutChanged();
    this->gui_update_shopping_basket_table_view_width();
}

void GUI::gui_user_undo() {
    try {
        this->srv.user_undo();
    }
    catch (ServiceException& se) {
        QMessageBox::critical(this, "Undo", se.what());
        return;
    }
    this->populate_shopping_basket_list();
    emit this->coats_table_model->layoutChanged();
    this->gui_update_shopping_basket_table_view_width();
}

void GUI::gui_user_redo() {
    try {
        this->srv.user_redo();
    }
    catch (ServiceException& se) {
        QMessageBox::critical(this, "Undo", se.what());
        return;
    }
    this->populate_shopping_basket_list();
    emit this->coats_table_model->layoutChanged();
    this->gui_update_shopping_basket_table_view_width();
}

void GUI::gui_create_statistics() {
    this->chart_series->clear();    // Reset the chart everytime
    QStringList sizes;
    std::vector<TrenchCoat> all_coats = this->srv.get_all_trenches_from_repo();     // Holds all the coats
    std::vector<std::string> all_sizes = this->get_all_sizes_from_repo();   // Holds all the coat sizes
    std::map<std::string, double> sizes_frequency;  // Holds the count of coats for each size
    std::vector<std::string> insertion_order;   // Cache the order of insertion in the above map (increasing)
    // Initialize the sizes map and remember the insertion order
    for (std::string &size: all_sizes) {
        sizes_frequency.insert({size, 0});
        insertion_order.emplace_back(size);
    }
    // Find the count of coats for each size
    for (TrenchCoat& t: all_coats) {
        sizes_frequency[t.get_trench_size()] += t.get_trench_quantity();
    }
    // Add each count of coats to the chart series in the order of insertion
    for (const auto& x: insertion_order) {
        this->chart_series->append(QString::fromStdString(x), sizes_frequency[x]);
    }
    // Set the labels
    this->chart_series->setLabelsVisible();
    this->chart_series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
    // For each slice, set its border and display its percentage
    for (auto slice: this->chart_series->slices()) {
        slice->setBorderColor(Qt::black);
        slice->setBorderWidth(2);
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
        slice->setLabelColor(QColor(255, 255, 0));
        slice->setLabelFont(this->font);
    }
    // Add the sizes to the legend, along with each size's count
    int i = 0;
    std::string legend_label;
    for (const auto& x: insertion_order) {
        legend_label = x + " (" + std::to_string((int)sizes_frequency[x]) + " units)";
        this->chart->legend()->markers(this->chart_series)[i]->setLabel(QString::fromStdString(legend_label));
        i += 1;
    }
}

std::vector<std::string> GUI::get_all_sizes_from_repo() {
    std::vector<std::string> all_sizes;
    std::vector<TrenchCoat> all_coats = this->srv.get_all_trenches_from_repo();
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XXS") {
        all_sizes.emplace_back("XXS");
        break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XS") {
            all_sizes.emplace_back("XS");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "S") {
            all_sizes.emplace_back("S");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "M") {
            all_sizes.emplace_back("M");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "L") {
            all_sizes.emplace_back("L");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XL") {
            all_sizes.emplace_back("XL");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XXL") {
            all_sizes.emplace_back("XXL");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XXXL") {
            all_sizes.emplace_back("XXXL");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XXXXL") {
            all_sizes.emplace_back("XXXXL");
            break;
    }
    for (TrenchCoat& t: all_coats) if (t.get_trench_size() == "XXXXXL") {
            all_sizes.emplace_back("XXXXXL");
            break;
    }
    return all_sizes;
}

#pragma clang diagnostic pop