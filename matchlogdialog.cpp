#include "matchlogdialog.h"

MatchLogDialog::MatchLogDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Лог матча");
    resize(600, 400);

    m_logTextEdit = new QTextEdit(this);
    m_logTextEdit->setReadOnly(true);

    m_closeButton = new QPushButton("Закрыть", this);
    connect(m_closeButton, &QPushButton::clicked, this, &QDialog::accept);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_logTextEdit);
    layout->addWidget(m_closeButton);

    setLayout(layout);
}

void MatchLogDialog::appendLog(const QString& text)
{
    m_logTextEdit->append(text);
}
