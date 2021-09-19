//
// Created by VladB on 05-Apr-21.
//

#include "ui.h"

#include <iostream>
#include <string>
#include <iomanip>

UI::UI(Service &srv) : srv(srv) {}

void UI::ui_print_menu() {
    std::cout << "\nCommands:\n"
                 "\t1 - Add a gene\n"
                 "\t2 - Show all genes in decreasing order\n"
                 "\t3 - Filter by sequence\n"
                 "\t4 - Show longest common subsequence\n"
                 "\t5 - Exit\n";
    std::cout << "\nMake a choice: ";
}

void UI::start() {
    std::string command;
    int cmd_as_int;
    bool keep_running = true;
    this->srv.fill_repo();
    while (keep_running) {
        this->ui_print_menu();
        std::cin >> command;
        cmd_as_int = std::atoi(command.c_str());
        try {
            switch (cmd_as_int) {
                case 1:
                    this->ui_add_gene();
                    break;
                case 2:
                    this->ui_print_decreasing_genes();
                    break;
                case 3:
                    this->ui_print_filtered_genes();
                    break;
                case 4:
                    this->ui_longest_subsequence();
                    break;
                case 5:
                    keep_running = false;
                    break;
                default:
                    std::cout << "\nInvalid input.\n";
                    break;
            }
        }
        catch (std::exception& e) {
            std::cout << e.what();
        }
    }
}

void UI::ui_add_gene() {
    std::string name, sequence, organism;
    std::cout << "\nEnter organism: ";
    std::cin >> organism;
    std::cout << "\nEnter name: ";
    std::cin >> name;
    std::cout << "\nEnter sequence: ";
    std::cin >> sequence;
    this->srv.srv_add_gene(organism, name, sequence);
    std::cout << "\nGene added.\n";
}

void UI::ui_print_decreasing_genes() {
    DynamicArray decreasing_genes = this->srv.get_decreasing_genes();
    int max_name_len = 0, max_organism_len = 0, max_seq_len = 0;
    if (decreasing_genes.get_dynamic_array_size() == 0) {
        std::cout << "\nThere are no genes in the repository.\n";
    }
    std::cout << "\nThese are the genes from the repository in decreasing order of sequence length:\n";
    for (int i = 0; i < decreasing_genes.get_dynamic_array_size(); i++) {
        if (decreasing_genes[i].get_name().length() > max_name_len)
            max_name_len = decreasing_genes[i].get_name().length();
        if (decreasing_genes[i].get_organism().length() > max_organism_len)
            max_organism_len = decreasing_genes[i].get_organism().length();
        if (decreasing_genes[i].get_sequence().length() > max_seq_len)
            max_seq_len = decreasing_genes[i].get_sequence().length();
    }

    for (int i = 0; i < decreasing_genes.get_dynamic_array_size(); i++) {
        std::cout << std::left << std::setw(max_organism_len) << decreasing_genes[i].get_organism() << " | ";
        std::cout << std::left << std::setw(max_name_len) << decreasing_genes[i].get_name() << " | ";
        std::cout << std::right << std::setw(max_seq_len) << decreasing_genes[i].get_sequence() << "\n";
    }
}

void UI::ui_print_filtered_genes() {
    std::string sub_seq;
    int max_name_len = 0, max_seq_len = 0, max_organism_len = 0;
    std::cout << "\nGive the subsequence for filtering: ";
    std::cin >> sub_seq;
    DynamicArray filtered = this->srv.filtered_genes(sub_seq);

    if (filtered.get_dynamic_array_size() == 0) {
        std::cout << "\nThere are no genes with the given subsequence in the repository.\n";
    }

    std::cout << "\nThese are the genes filtered by subsequence:\n";
    for (int i = 0; i < filtered.get_dynamic_array_size(); i++) {
        if (filtered[i].get_name().length() > max_name_len)
            max_name_len = filtered[i].get_name().length();
        if (filtered[i].get_sequence().length() > max_seq_len)
            max_seq_len = filtered[i].get_sequence().length();
        if (filtered[i].get_organism().length() > max_organism_len)
            max_organism_len = filtered[i].get_organism().length();
    }
    for (int i = 0; i < filtered.get_dynamic_array_size(); i++) {
        std::cout << std::left << std::setw(max_organism_len) << filtered[i].get_organism() << " | ";
        std::cout << std::left << std::setw(max_name_len) << filtered[i].get_name() << " | ";
        std::cout << std::right << std::setw(max_seq_len) << filtered[i].get_sequence() << "\n";
    }

}

void UI::ui_longest_subsequence() {
    std::string org1, org2, name1, name2, longest_subsequence;
    std::cout << "\nGive the first organism name: ";
    std::cin >> org1;
    std::cout << "\nGive the first gene name: ";
    std::cin >> name1;
    std::cout << "\nGive the second organism name: ";
    std::cin >> org2;
    std::cout << "\nGive the second gene name: ";
    std::cin >> name2;
    std::string lcs = this->srv.longest_subseq_of_gene_pair(org1, name1, org2, name2);
    if (lcs == "-1") {
        std::cout << "\nThe 2 genes have no subsequence in common.\n";
    }
    else {
        std::cout << "\nThe longest common subsequence between the 2 genes is: " << lcs << "\n";
    }
}
