//
// Created by VladB on 05-Apr-21.
//

#include "service.h"

#include <utility>
#include <cstring>

Service::Service(Repository &repo) : repo(repo) {}

void Service::srv_add_gene(std::string organism, std::string name, std::string sequence) {
    Gene new_gene{std::move(organism), std::move(name), std::move(sequence)};
    this->repo.repo_add_gene(new_gene);
}

DynamicArray Service::get_decreasing_genes() {
    DynamicArray all_genes = this->repo.get_all_genes_from_repo();
    for (int i = 0; i < all_genes.get_dynamic_array_size() - 1; i++) {
        for (int j = i + 1; j < all_genes.get_dynamic_array_size(); j++) {
            if (all_genes[i].get_sequence().length() < all_genes[j].get_sequence().length()) {
                Gene aux = all_genes[i];
                all_genes[i] = all_genes[j];
                all_genes[j] = aux;
            }
        }
    }
    return all_genes;
}

DynamicArray Service::filtered_genes(const std::string &sub_seq) {
    DynamicArray all_genes = this->repo.get_all_genes_from_repo();
    DynamicArray filtered;
    for (int i = 0; i < all_genes.get_dynamic_array_size(); i++) {
        if (strstr(all_genes[i].get_sequence().c_str(), sub_seq.c_str())) {
            filtered.add_to_dynamic_array(all_genes[i]);
        }
    }
    for (int i = 0; i < filtered.get_dynamic_array_size() - 1; i++) {
        for (int j = i + 1; j < filtered.get_dynamic_array_size(); j++) {
            if (filtered[i].get_sequence().length() < filtered[j].get_sequence().length()) {
                Gene aux = filtered[i];
                filtered[i] = filtered[j];
                filtered[j] = aux;
            }
        }
    }
    return filtered;
}

void Service::fill_repo() {
    Gene new_gene{"E_Coli_K12", "yqgE", "ATGACATCATCATTG"};
    this->repo.repo_add_gene(new_gene);
    Gene new_gene_2{"M_tuberculosis", "ppiA", "TCTTCATCATCATCGG"};
    this->repo.repo_add_gene(new_gene_2);
    Gene new_gene_3{"Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG"};
    this->repo.repo_add_gene(new_gene_3);
    Gene new_gene_4{"E_Coli_ETEC", "yqgE", "GTGACAGCGCCCTTCTTTCCACG"};
    this->repo.repo_add_gene(new_gene_4);
    Gene new_gene_5{"E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC"};
    this->repo.repo_add_gene(new_gene_5);
}

Gene Service::find_gene(const std::string &organism, const std::string &name) {
    for (int i = 0; i < this->repo.get_all_genes_from_repo().get_dynamic_array_size(); i++) {
        if (this->repo.get_all_genes_from_repo()[i].get_organism() == organism &&
            this->repo.get_all_genes_from_repo()[i].get_name() == name) {
            return this->repo.get_all_genes_from_repo()[i];
        }
    }
    throw std::runtime_error("\nERROR: Gene couldn't be found.\n");
}

std::string Service::longest_common_substr(std::string x, std::string y) {
    int current_row, end, result = 0, m = x.length(), n = y.length(), len[2][n];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i > 0 && j > 0 && x[i - 1] == y[j - 1]) {
                len[current_row][j] = len[1 - current_row][j - 1] + 1;
                if (len[current_row][j] > result) {
                    result = len[current_row][j];
                    end = i - 1;
                }
            } else {
                len[current_row][j] = 0;
            }
        }
        current_row = 1 - current_row;
    }
    if (result == 0) {
        return "-1";
    }
    return x.substr(end - result + 1, result);
}

std::string Service::longest_subseq_of_gene_pair(const std::string &o1, const std::string &n1, const std::string &o2,
                                                 const std::string &n2) {
    Gene g1 = this->find_gene(o1, n1);
    Gene g2 = this->find_gene(o2, n2);
    return this->longest_common_substr(g1.get_sequence(), g2.get_sequence());
}
