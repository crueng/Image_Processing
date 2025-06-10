#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Image_Processing.h"

class Image_Processing : public QMainWindow
{
    Q_OBJECT

public:
    Image_Processing(QWidget *parent = nullptr);
    ~Image_Processing();

private:
    Ui::Image_ProcessingClass ui;
};
