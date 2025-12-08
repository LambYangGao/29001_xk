#ifndef STEPLED_H
#define STEPLED_H

#include <QAbstractButton>
#include <QTimer>

class QSimpleLed : public QAbstractButton
{
    Q_OBJECT

    typedef struct COLORGROUP {
        QColor on0;
        QColor on1;
        QColor off0;
        QColor off1;
    } ColorGroup, *ColorGroupPtr;

public:

    enum LEDCOLOR {
        CUSTOM  = 0,
        RED     = 1,
        GREEN   = 2,
        BLUE    = 3,
        YELLOW  = 4,
        ORANGE  = 5,
        GREY    = 6,
    };

    enum LEDSTATES {
        ON       = 0,
        OFF      = 1,
        BLINK    = 2,
    };

    QSimpleLed(QWidget *parent = nullptr, LEDCOLOR color = GREEN);
    void setCustomOnColor0(const QColor &color) { smColorPalette[CUSTOM].on0 = color; }
    void setCustomOnColor1(const QColor &color) { smColorPalette[CUSTOM].on1 = color; }
    void setCustomOffColor0(const QColor &color) { smColorPalette[CUSTOM].off0 = color; }
    void setCustomOffColor1(const QColor &color) { smColorPalette[CUSTOM].off1 = color; }
    LEDSTATES states() { return mStates; }
    void setStates(LEDSTATES states);
    void setInterval(int msec) { mInterval = msec; }
	LEDCOLOR mColor;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onBlinkTimerTimeout(void);
private:
    void resetStatus(void);
    LEDSTATES mStates = OFF;
    QTimer *mBlinkTimer = nullptr;
    int mInterval = 200;
    static ColorGroup smColorPalette[];
};

#endif // STEPLED_H
