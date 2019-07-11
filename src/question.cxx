//
// Created by Julian on 24.06.18.
//

#include <decision_tree/question.h>
#include <decision_tree/help.h>
#include <cassert>

using namespace decision_tree;
using std::string;

Question::Question() : column_{0}, value_{} {}

Question::Question(const int column, string value) : column_{column}, value_{std::move(value)} {}

const bool Question::match(VecS example) const {
    const string &val = example.at(column_);

    try {
        // faster than calling isNumeric on both!
        return std::stod(val) >= std::stod(value_);
    } catch (const std::exception &e) {
        return val == value_;
    }
}

const string Question::toString(const VecS &labels) const {
    string condition = "==";
    if (isNumeric(value_))
        condition = ">=";
    return "Is " + labels.at(column_) + " " + condition + " " + value_ + "?";
}

const bool Question::isNumeric(std::string value) const {
    try {
        std::stod(value);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}
