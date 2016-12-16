//
// Created by ololosh on 12/15/16.
//

#include <memory>

#include "Token.h"

using namespace std;

Token::Token (Token&& source) {
    this->data = move (source.data);
    this->idf = move (source.idf);
    this->tf = move (source.tf);
}

string Token::getData () {
    return this->data;
}

void Token::setData (const string& data) {
    this->data = data;
}

void Token::setData (string&& data) {
    this->data = move (data);
}

double Token::getIdf () {
    return this->idf;
}

void Token::setIdf (double idf) {
    this->idf = idf;
}

double Token::getTf () {
    return this->tf;
}

void Token::setTf (double tf) {
    this->tf = tf;
}