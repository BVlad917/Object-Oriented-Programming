//
// Created by VladB on 04-May-21.
//

#ifndef A67_BVLAD917_GUI_H
#define A67_BVLAD917_GUI_H

#include <QTabWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QTCharts>
#include "../business/service.h"

class GUI : public QWidget {

Q_OBJECT

private:
    Service &srv;
    std::vector<TrenchCoat> filtered_coats;
    int current_filtered_coat_index{};
    // The font we will use for the window labels
    QFont font{};

    // The tab widget, where 3 tabs will be displayed: User, Admin, and Statistics
    QHBoxLayout *tab_layout{};
    QTabWidget *tab_widget{};

    // The widgets of the 3 tabs
    QWidget *user_widget{};
    QWidget *admin_widget{};
    QWidget *statistics_widget{};

    // The layouts of the above 3 widgets
    QHBoxLayout *user_layout{};
    QGridLayout *admin_layout{};
    QVBoxLayout *statistics_layout{};

    // ==============================
    // ===== FOR THE ADMIN MODE =====
    // ==============================
    // The layout and the text fields for adding, removing, and updating trench coats
    QFormLayout *admin_text_fields_layout{};
    QLineEdit *admin_size_field{};
    QLineEdit *admin_colour_field{};
    QLineEdit *admin_price_field{};
    QLineEdit *admin_quantity_field{};
    QLineEdit *admin_link_field{};

    // The widget list used for displaying the trench coats in the admin mode, and its label used as title
    QListWidget *admin_list_of_coats{};
    QLabel *admin_title_of_list_of_coats{};
    QVBoxLayout *admin_list_and_title_layout{};

    // The 3 buttons available for the Admin mode and the layout they are put in
    QGridLayout *admin_buttons_layout{};
    QPushButton *admin_add_button{};
    QPushButton *admin_remove_button{};
    QPushButton *admin_update_button{};

    // =============================
    // ===== FOR THE USER MODE =====
    // =============================
    // The left side of the user mode window contains the "Filter by Size" part (title + list + button & field)
    QVBoxLayout *user_left_side_layout{};
    QLabel *user_one_by_one_title{};
    QListWidget *user_one_by_one_list{};
    QHBoxLayout *user_filter_layout{};
    QLineEdit *user_filter_field{};
    QPushButton *user_filter_button{};
    QPushButton *user_open_current_coat_button{};
    // The middle of the user mode window contains the buttons ("Add to cart", "Next", and "Open(CSV/HTML)")
    QVBoxLayout *user_middle_layout{};
    QPushButton *user_add_to_cart_button{};
    QPushButton *user_next_button{};
    QPushButton *user_open_basket_button{};
    // The left side of the user mode window contains the "Shopping Basket" part (title + list + "Total" label)
    QVBoxLayout *user_right_side_layout{};
    QLabel *user_basket_title{};
    QListWidget *user_basket_list{};
    QLabel *user_basket_total_label{};

    // ==============================
    // ===== FOR THE STATISTICS =====
    // ==============================
    QChart *chart{};    // The chart where we will put the Qt Pie Chart object
    QChartView *chart_view{};   // Used to display the chart
    QPieSeries *chart_series{};     // Used to add objects to the chart

private:
    void init_gui();

    void populate_repository_list();

    void connect_signals_and_slots();

    int get_selected_index_from_admin_list() const;

    void gui_fill_admin_line_edits_when_selected();

    void gui_add_trench_coat();

    void gui_remove_trench_coat();

    void gui_update_trench_coat();

    void gui_filter_coats();

    void gui_next_filtered_coat();

    void gui_add_filtered_coat_to_shopping_cart();

    void gui_open_shopping_cart_file();

    void gui_open_current_filtered_coat();

    void gui_create_statistics();

    std::vector<std::string> get_all_sizes_from_repo();

    void gui_deselect_admin_list_on_double_click(QListWidgetItem * itemClicked);

    void gui_deselect_user_filter_list_on_double_click(QListWidgetItem * itemClicked);

    void add_coat_button_handler();

    void remove_coat_button_handler();

    void update_coat_button_handler();

signals:
    void add_coat_signal(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo);

    void remove_coat_signal(int index);

    void update_coat_signal(int index);

    void coats_updated_signal();

public slots:
    void add_coat_slot(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo);

    void remove_coat_slot(int index);

    void update_coat_slot(int index);

public:
    explicit GUI(Service &srv);
};


#endif //A67_BVLAD917_GUI_H
