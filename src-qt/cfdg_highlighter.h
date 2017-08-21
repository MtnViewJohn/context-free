#ifndef CFDG_HIGHLIGHTER_H
#define CFDG_HIGHLIGHTER_H

#include <QtGui/qsyntaxhighlighter.h>
#include <QRegularExpression>

class cfdg_highlighter : public QSyntaxHighlighter
{
public:
    cfdg_highlighter(QTextDocument *parent = 0);
protected:
    void highlightBlock(const QString &text) override;
private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStart;
    QRegularExpression commentEnd;

    QTextCharFormat paramtypes;
    QTextCharFormat shape;
    QTextCharFormat oneLineComment;
    QTextCharFormat quote;
    QTextCharFormat adjs;
};

#endif // CFDG_HIGHLIGHTER_H
