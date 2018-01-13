#include "creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Credits"));
    setWindowIcon(QIcon(":/icons/ic_info_white_18dp"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    m_layout = new QGridLayout;
    m_layout->setSizeConstraint(QLayout::SetFixedSize);

    mw_text = new QLabel(this);
    mw_text->setTextFormat(Qt::RichText);
    mw_text->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mw_text->setOpenExternalLinks(true);

    QFont font = mw_text->font();
    font.setPointSize(9);
    mw_text->setFont(font);

    mw_text->setText(tr("<style>" \
                        "a{color: #3399ff;}" \
                        "</style>" \
                        "<p>" \
                        "Some icons comes from <a href=\"https://material.io/icons/\">https://material.io/icons/</a><br>" \
                        "and are available under the Apache License Version 2.0.<hr>" \
                        "All trademarks are property of their respective owners." \
                        "</p>"));

    m_layout->addWidget(mw_text, 0, 0, 1, 1);

    setLayout(m_layout);
}
