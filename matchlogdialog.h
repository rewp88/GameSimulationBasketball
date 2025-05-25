#ifndef MATCHLOGDIALOG_H
#define MATCHLOGDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class MatchLogDialog : public QDialog {
    Q_OBJECT
public:
    explicit MatchLogDialog(QWidget* parent = nullptr);

    void appendLog(const QString& text);

private:
    QTextEdit* m_logTextEdit;
    QPushButton* m_closeButton;
};

#endif // MATCHLOGDIALOG_H
