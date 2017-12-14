#include "cfdg_highlighter.h"
#include <iostream>
#include <QtDebug>

cfdg_highlighter::cfdg_highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    QStringList shapePatterns;
    shape.setForeground(QColor("mediumseagreen"));
    // We don't need to use a lookbehind because the keywords' formatting will be overwritten by the next rule // This regex finds shape names when they're being called
    shapePatterns << "\\bshape\\s+\\S+" << "\\bstartshape\\s+\\S+" << "\\brule\\s+\\S+" << "\\bpath\\s+\\S+" << "\\S*(?=\\s*(?:\\[.*\\]|{.*}))";
    foreach (const QString &pattern, shapePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = shape;
        highlightingRules.append(rule);
    }

    paramtypes.setForeground(Qt::darkBlue);
    paramtypes.setFontWeight(QFont::Bold);
    QStringList ptypePatterns;
    ptypePatterns << "\\bnumber\\b" << "\\bvector\\b" << "\\badjustment\\b" << "\\bshape\\b" << "\\bnatural\\b" << "\\bstartshape\\b" << "\\brule\\b" << "\\bpath\\b";
    foreach (const QString &pattern, ptypePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = paramtypes;
        highlightingRules.append(rule);
    }
}

void cfdg_highlighter::highlightBlock(const QString &text) {
    // This implementation has an intrinsic tendency to hold on to shapes which no longer exist

//    QRegularExpression shapeDec = QRegularExpression("^(?:start)?shape ([[:alpha:]]+)");
//    QRegularExpressionMatchIterator shapeIt = shapeDec.globalMatch(text);
//    while(shapeIt.hasNext()){
//        QRegularExpressionMatch match = shapeIt.next();
//        QStringList caps = match.capturedTexts();
//        HighlightingRule shapeRule;
//        bool first = true;
//        foreach (QString cap, caps) {
//            if (first) {
//                first = false;
//                //qDebug() << "Continuing on string" << cap;
//                continue;
//            }
//            //qDebug() << "Not continuing on" << cap;
//            shapeRule.pattern = QRegularExpression("\\b" + cap + "\\b");
//            shapeRule.format = shape;
//            highlightingRules.append(shapeRule);
//        }
//    }

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
