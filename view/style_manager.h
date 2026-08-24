#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QObject>
#include <QColor>

class StyleManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor primaryColor READ primaryColor WRITE setPrimaryColor NOTIFY primaryColorChanged)
    Q_PROPERTY(QColor primaryDark READ primaryDark WRITE setPrimaryDark NOTIFY primaryDarkChanged)
    Q_PROPERTY(QColor primaryLight READ primaryLight WRITE setPrimaryLight NOTIFY primaryLightChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor secondaryText READ secondaryText WRITE setSecondaryText NOTIFY secondaryTextChanged)
    Q_PROPERTY(QColor lightText READ lightText WRITE setLightText NOTIFY lightTextChanged)
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QColor white READ white WRITE setWhite NOTIFY whiteChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor accentTextColor READ accentTextColor WRITE setAccentTextColor NOTIFY accentTextColorChanged)

    Q_PROPERTY(int fontSizeLarge READ fontSizeLarge WRITE setFontSizeLarge NOTIFY fontSizeLargeChanged)
    Q_PROPERTY(int fontSizeTitle READ fontSizeTitle WRITE setFontSizeTitle NOTIFY fontSizeTitleChanged)
    Q_PROPERTY(int fontSizeGroup READ fontSizeGroup WRITE setFontSizeGroup NOTIFY fontSizeGroupChanged)
    Q_PROPERTY(int fontSizeNormal READ fontSizeNormal WRITE setFontSizeNormal NOTIFY fontSizeNormalChanged)
    Q_PROPERTY(int fontSizeSmall READ fontSizeSmall WRITE setFontSizeSmall NOTIFY fontSizeSmallChanged)

    Q_PROPERTY(int spacingLarge READ spacingLarge WRITE setSpacingLarge NOTIFY spacingLargeChanged)
    Q_PROPERTY(int spacingMedium READ spacingMedium WRITE setSpacingMedium NOTIFY spacingMediumChanged)
    Q_PROPERTY(int spacingSmall READ spacingSmall WRITE setSpacingSmall NOTIFY spacingSmallChanged)
    Q_PROPERTY(int spacingTiny READ spacingTiny WRITE setSpacingTiny NOTIFY spacingTinyChanged)

    Q_PROPERTY(int paddingGroup READ paddingGroup WRITE setPaddingGroup NOTIFY paddingGroupChanged)
    Q_PROPERTY(int topPaddingGroup READ topPaddingGroup WRITE setTopPaddingGroup NOTIFY topPaddingGroupChanged)
    Q_PROPERTY(int buttonHeight READ buttonHeight WRITE setButtonHeight NOTIFY buttonHeightChanged)
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight NOTIFY rowHeightChanged)
    Q_PROPERTY(int labelWidth READ labelWidth WRITE setLabelWidth NOTIFY labelWidthChanged)
    Q_PROPERTY(int phoneWidth READ phoneWidth WRITE setPhoneWidth NOTIFY phoneWidthChanged)

public:
    explicit StyleManager(QObject *parent = nullptr);

    // Getters
    QColor primaryColor() const { return m_primaryColor; }
    QColor primaryDark() const { return m_primaryDark; }
    QColor primaryLight() const { return m_primaryLight; }
    QColor textColor() const { return m_textColor; }
    QColor secondaryText() const { return m_secondaryText; }
    QColor lightText() const { return m_lightText; }
    QColor background() const { return m_background; }
    QColor white() const { return m_white; }
    QColor borderColor() const { return m_borderColor; }
    QColor accentTextColor() const { return m_accentTextColor; }

    int fontSizeLarge() const { return m_fontSizeLarge; }
    int fontSizeTitle() const { return m_fontSizeTitle; }
    int fontSizeGroup() const { return m_fontSizeGroup; }
    int fontSizeNormal() const { return m_fontSizeNormal; }
    int fontSizeSmall() const { return m_fontSizeSmall; }

    int spacingLarge() const { return m_spacingLarge; }
    int spacingMedium() const { return m_spacingMedium; }
    int spacingSmall() const { return m_spacingSmall; }
    int spacingTiny() const { return m_spacingTiny; }

    int paddingGroup() const { return m_paddingGroup; }
    int topPaddingGroup() const { return m_topPaddingGroup; }
    int buttonHeight() const { return m_buttonHeight; }
    int rowHeight() const { return m_rowHeight; }
    int labelWidth() const { return m_labelWidth; }
    int phoneWidth() const { return m_phoneWidth; }

    // Setters
    void setPrimaryColor(const QColor &c) { if (m_primaryColor != c) { m_primaryColor = c; emit primaryColorChanged(); } }
    void setPrimaryDark(const QColor &c) { if (m_primaryDark != c) { m_primaryDark = c; emit primaryDarkChanged(); } }
    void setPrimaryLight(const QColor &c) { if (m_primaryLight != c) { m_primaryLight = c; emit primaryLightChanged(); } }
    void setTextColor(const QColor &c) { if (m_textColor != c) { m_textColor = c; emit textColorChanged(); } }
    void setSecondaryText(const QColor &c) { if (m_secondaryText != c) { m_secondaryText = c; emit secondaryTextChanged(); } }
    void setLightText(const QColor &c) { if (m_lightText != c) { m_lightText = c; emit lightTextChanged(); } }
    void setBackground(const QColor &c) { if (m_background != c) { m_background = c; emit backgroundChanged(); } }
    void setWhite(const QColor &c) { if (m_white != c) { m_white = c; emit whiteChanged(); } }
    void setBorderColor(const QColor &c) { if (m_borderColor != c) { m_borderColor = c; emit borderColorChanged(); } }
    void setAccentTextColor(const QColor &c) { if (m_accentTextColor != c) { m_accentTextColor = c; emit accentTextColorChanged(); } }

    void setFontSizeLarge(int v) { if (m_fontSizeLarge != v) { m_fontSizeLarge = v; emit fontSizeLargeChanged(); } }
    void setFontSizeTitle(int v) { if (m_fontSizeTitle != v) { m_fontSizeTitle = v; emit fontSizeTitleChanged(); } }
    void setFontSizeGroup(int v) { if (m_fontSizeGroup != v) { m_fontSizeGroup = v; emit fontSizeGroupChanged(); } }
    void setFontSizeNormal(int v) { if (m_fontSizeNormal != v) { m_fontSizeNormal = v; emit fontSizeNormalChanged(); } }
    void setFontSizeSmall(int v) { if (m_fontSizeSmall != v) { m_fontSizeSmall = v; emit fontSizeSmallChanged(); } }

    void setSpacingLarge(int v) { if (m_spacingLarge != v) { m_spacingLarge = v; emit spacingLargeChanged(); } }
    void setSpacingMedium(int v) { if (m_spacingMedium != v) { m_spacingMedium = v; emit spacingMediumChanged(); } }
    void setSpacingSmall(int v) { if (m_spacingSmall != v) { m_spacingSmall = v; emit spacingSmallChanged(); } }
    void setSpacingTiny(int v) { if (m_spacingTiny != v) { m_spacingTiny = v; emit spacingTinyChanged(); } }

    void setPaddingGroup(int v) { if (m_paddingGroup != v) { m_paddingGroup = v; emit paddingGroupChanged(); } }
    void setTopPaddingGroup(int v) { if (m_topPaddingGroup != v) { m_topPaddingGroup = v; emit topPaddingGroupChanged(); } }
    void setButtonHeight(int v) { if (m_buttonHeight != v) { m_buttonHeight = v; emit buttonHeightChanged(); } }
    void setRowHeight(int v) { if (m_rowHeight != v) { m_rowHeight = v; emit rowHeightChanged(); } }
    void setLabelWidth(int v) { if (m_labelWidth != v) { m_labelWidth = v; emit labelWidthChanged(); } }
    void setPhoneWidth(int v) { if (m_phoneWidth != v) { m_phoneWidth = v; emit phoneWidthChanged(); } }

signals:
    void primaryColorChanged();
    void primaryDarkChanged();
    void primaryLightChanged();
    void textColorChanged();
    void secondaryTextChanged();
    void lightTextChanged();
    void backgroundChanged();
    void accentTextColorChanged();
    void whiteChanged();
    void borderColorChanged();
    void fontSizeLargeChanged();
    void fontSizeTitleChanged();
    void fontSizeGroupChanged();
    void fontSizeNormalChanged();
    void fontSizeSmallChanged();
    void spacingLargeChanged();
    void spacingMediumChanged();
    void spacingSmallChanged();
    void spacingTinyChanged();
    void paddingGroupChanged();
    void topPaddingGroupChanged();
    void buttonHeightChanged();
    void rowHeightChanged();
    void labelWidthChanged();
    void phoneWidthChanged();

private:
    QColor m_primaryColor   = QColor("#3498db");
    QColor m_primaryDark    = QColor("#2980b9");
    QColor m_primaryLight   = QColor("#e8f0fe");
    QColor m_textColor      = QColor("#2c3e50");
    QColor m_secondaryText  = QColor("#555555");
    QColor m_lightText      = QColor("#7f8c8d");
    QColor m_background     = QColor("#f4f6f9");
    QColor m_white          = QColor("#ffffff");
    QColor m_borderColor    = QColor("#3498db");
    QColor m_accentTextColor= QColor("#00BCD4");

    int m_fontSizeLarge     = 24;
    int m_fontSizeTitle     = 16;
    int m_fontSizeGroup     = 14;
    int m_fontSizeNormal    = 14;
    int m_fontSizeSmall     = 12;

    int m_spacingLarge      = 35;
    int m_spacingMedium     = 20;
    int m_spacingSmall      = 12;
    int m_spacingTiny       = 10;

    int m_paddingGroup      = 15;
    int m_topPaddingGroup   = 35;
    int m_buttonHeight      = 42;
    int m_rowHeight         = 40;
    int m_labelWidth        = 160;
    int m_phoneWidth        = 180;
};

#endif // STYLEMANAGER_H
