//
// Created by Julian on 25.06.18.
//

#include <decision_tree/generate.h>
#include <decision_tree/help.h>
#include <algorithm>
#include <fmt/format.h>

using namespace decision_tree;
namespace elem = decision_tree::graph_element;

using std::string;

void generate::init(const std::unique_ptr<Node> &root, const VecS &labels, string filepath) {
    std::ofstream myfile;
    myfile.open(filepath);

    if (!myfile.is_open()) {
        fmt::print("Couldn't open {}. Can't create Graphviz dot file.\n", filepath);
        return;
    }

    myfile << "digraph {\n";
    traverse_generate(root, labels, myfile);
    myfile << "}";
    myfile.close();

//    traverseTreeBFS(root, myfile);
}

void generate::traverse_generate(const std::unique_ptr<Node> &node, const VecS &labels, std::ofstream &file) {
    static const string spacing = "   ";
    static const string connector = " -> ";
    if (node == nullptr)
        return;

    if (node->predicts())
        return;

    const auto question = node->question().value().toString(labels);
    const auto hash = node->hash(labels);

    file << spacing << elem::box(question, hash);
    file << spacing << elem::node(hash) << connector;

    if (node->true_branch()->predicts()) {
        file << elem::result(node->true_branch()->predictions().value(), true);
    } else {
        file << elem::node(node->true_branch()->hash(labels)) << elem::label("True");
    }

    file << spacing << elem::node(hash) << connector;

    if (node->false_branch()->predicts()) {
        file << elem::result(node->false_branch()->predictions().value(), false);
    } else {
        file << elem::node(node->false_branch()->hash(labels)) << elem::label("False");
    }

    traverse_generate(node->true_branch(), labels, file);
    traverse_generate(node->false_branch(), labels, file);
}

string graph_element::label(const string &label) {
    return " [label=\"" + label + "\"];\n";
}

string graph_element::node(size_t hash) {
    return fmt::format("\"{}\"", hash);
}

string graph_element::box(const string &label, size_t hash) {
    return fmt::format("\"{}\" [label=\"{}\", shape=box];\n", hash, label);
}

string graph_element::result(const std::unordered_map<string, int> &data, bool branch) {
    static int id = 0;
    string result = "\"";
    double sum = std::accumulate(data.begin(), data.end(), 0, [](auto curr, const auto& entry) { return curr + entry.second; });
    size_t map_size = data.size();
    size_t counter = 1;

    string classification{};
    for (const auto&[k, v]: data) {
        classification += fmt::format("{}: {:0.1f}%", k , v / sum * 100);
        if (counter++ < map_size)
            classification += "\\n ";
    }
    result += classification;

    string values = "\\nvalues: ";
    for (const auto&[k, v]: data) {
        values += fmt::format("{} ", v);
    }

    result += values;

    string result_id = fmt::format(" ({})", id++);
    result += result_id;

    string result_box = fmt::format("   {}\" {};\n", result, "[shape=box]");
    string label = fmt::format("\" {}", branch ? graph_element::label("True") : graph_element::label("False"));
    result += label;

    result += result_box;
    return result;
}

