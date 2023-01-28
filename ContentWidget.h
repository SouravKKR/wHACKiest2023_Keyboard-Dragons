#pragma once
#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H
#include<QLabel>
#include "UtilityFunctions.h"
#include<QPushButton>
#include <QHBoxLayout>

class ContentWidget : public QHBoxLayout
{
public:
    QLabel* ID = new QLabel;
    QLabel* Type = new QLabel;
    QLabel* Time = new QLabel;
    QLabel* Resolved = new QLabel;
    QLabel* Comments = new QLabel;
    ContentWidget();
    void Setup(Problem Element);
};

#endif // CONTENTWIDGET_H
