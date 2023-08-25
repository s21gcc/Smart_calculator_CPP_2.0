#ifndef CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H

#include <QMainWindow>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~MainWindow();
 private slots:
  void on_push_button_clear_clicked();
  void on_push_button_calc_clicked();
  void on_push_button_make_graph_clicked();

 private:
  Controller *controller_;
  Ui::MainWindow *ui_;
  void ConnectButtons();
  void InputNumbers();
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_VIEW_MAINWINDOW_H
