#include "ContentWidget.h"


ContentWidget::ContentWidget()
{
    addChildWidget(ID);
    addChildWidget(Type);
    addChildWidget(Time);
    addChildWidget(Resolved);
    addChildWidget(Comments);

}

void ContentWidget::Setup(Problem p)
{
    ID->setText(QString::fromStdString(p.ProblemID));
    Type->setText(QString::fromStdString(p.ProblemType));
    Time->setText(QString::fromStdString(p.TimeStamp));
    QString temp;
    if(p.Resolved)
        temp = "Resolved";
    else
        temp = "Pending";

    Resolved->setText(temp);
    Comments->setText(QString::fromStdString(p.Comments));

}
