//
// Created by ololosh on 12/15/16.
//

#include <memory>

#include "Token.h"

using namespace std;

Token::Token (string _data)
        : data (_data)
{}

Token::Token (string _data, double _idf, double _tf)
        : data (_data), idf (_idf), tf (_tf)
{}

Token::Token (Token&& source) {
    this->data = move (source.data);
    this->idf = move (source.idf);
    this->tf = move (source.tf);
}

string Token::getData () {
    return this->data;
}

const string Token::getData () const {
    return this->data;
}

void Token::setData (const string& data) {
    this->data = data;
}

void Token::setData (string&& data) {
    this->data = move (data);
}

const double Token::getIdf () const {
    return this->idf;
}

double Token::getIdf () {
    return this->idf;
}

void Token::setIdf (double idf) {
    this->idf = idf;
}

const double Token::getTf () const {
    return this->tf;
}

double Token::getTf () {
    return this->tf;
}

void Token::setTf (double tf) {
    this->tf = tf;
}