#include <QApplication>
#include <QWidget>
#include <QPainter>

class TriangleWidget : public QWidget {
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Configurar el color amarillo
        QBrush brush(Qt::yellow);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);

        // Definir los puntos del cuadrado
        QPointF points[4] = {
            QPointF(20, 20),                     // Esquina superior izquierda
            QPointF(width() - 20, 20),           // Esquina superior derecha
            QPointF(width() - 20, height() - 20),// Esquina inferior derecha
            QPointF(20, height() - 20)           // Esquina inferior izquierda
        };

        // Dibujar el cuadrado
        painter.drawPolygon(points, 4);
    }
};


class CircleWidget : public QWidget {
    protected:
        void paintEvent(QPaintEvent *) override {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
    
            // Configurar el color amarillo
            QBrush brush(Qt::yellow);
            painter.setBrush(brush);
            painter.setPen(Qt::NoPen);
    
            // Dibujar el círculo en el centro de la ventana
            int diameter = qMin(width(), height()) - 40; // Ajustar el tamaño con margen
            painter.drawEllipse(QPointF(width() / 2.0, height() / 2.0), diameter / 2, diameter / 2);
        }
    };
    

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    TriangleWidget window;
    window.resize(400, 300);
    window.show();
    
    return app.exec();
}


class MyWindow : public QWidget {
public:
    MyWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Cerrar Ventana");
        resize(300, 200);
        
        QPushButton *closeButton = new QPushButton("Cerrar", this);
        connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
        
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(closeButton);   
        setLayout(layout);
    }
};










int main(int argc, char* argv) {
    QApplication app(argc, argv);
    MyWindow window;
    window.show();
    return app.exec();
}

class MyWindow: public QWidget {
public:
    MyWindow(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("ejercicio");
        resize(400,400);
    }

protected:

    void PaintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QBrush brush(Qt::yellow);
        painter.setBrush(brush);
        painter.setPen(Qt::noPen);

        int diameter = 100;
        painter.drawEllipse(QPointF(20,20), 100,100)
    }
}













class MyWidget: public QWidget {
public: 
    MyWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle
        resize

        QpushButton* button = new QpushButton("cerrar", this)
        connect(button, &QpushButton::clicked, this, &QWidget::close);

        QVBoxLayout^* layout = new Qvboxlayout(this);
        layout addwidget(button)
        setLayout(layout)
    }
}









protected:

    void paintEvent(QPaintEvent*) override {
        Qpainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QBrush brush(Qt::yellow);
        painter.setBrush  (brus)
        painter.setPen(qt no pen)

        QFpoints points[4]
    }



int main(int argc, char * argv[]) {
    Qapplication app(argc, argv);
    MyWindow w;
    w.show();
    return app.exec();
}

class MyWidget: public QWidget {
public:
    MyWidget(QWidget* parent= nullptr) : QWidget(parent) {
        setWindowTitle
        resize

        QpushButton* button = new Qpushbutton("cerrar", this)
        connect(button, &QPushbUTTON::clicked, this, &QWidget::close);

        QVBoxLayot* layot = new Qvbox (this);
        layot->addWidget(button)
        layot.>display
    }
protected:
    void PaintEvent(QPaintEvent*) override {
        QPainter initPainter

        Qbrush::(QT::yellow)
        painter.setcollor(brus)
        Qpen = qt::nopen

        QPointF points[4] = {QPointf(2,2), ..}
        drawPoligon(points,4) 
    }
}