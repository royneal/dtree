# Decision Tree

[![Build Status](https://travis-ci.org/juliangaal/DecisionTree.svg?branch=master)](https://travis-ci.org/juliangaal/DecisionTree) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/bfa5313712764c4ba94a3263f45e999a)](https://www.codacy.com/app/juliangaal/DecisionTree?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=juliangaal/DecisionTree&amp;utm_campaign=Badge_Grade)

Decision Tree implementation in C++ based on Gini uncertainty and [this](https://github.com/random-forests/tutorials/blob/master/decision_tree.py) great example.

## Graphviz File Generator
use built-in [Graphviz](https://www.graphviz.org) dot file generator to export decision tree to `.dot` file, that you can visualize with [xdot](https://github.com/jrfonseca/xdot.py) or an online viewer. Example graph:

<p align="center">
    <img alt="Alt Text" src="docs/iris.dot.jpg?raw=true" />
</p>

results from [iris.dot](docs/graph.dot) and [this](test/data/iris.csv) dataset.

## Requirements
* Boost
* gcc >= 7

## TODO
* handle missing data in files
