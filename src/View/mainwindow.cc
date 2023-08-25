#include "mainwindow.h"

#include <iomanip>

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget* parent, Controller* controller)
    : QMainWindow(parent), controller_(controller), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  ConnectButtons();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::ConnectButtons() {  // сделал лямбду функции
  for (auto button : ui_->numbers->buttons()) {
    connect(button, &QPushButton::clicked, this, [this, button]() {
      QString new_label = ui_->result_line->text() + button->text();
      ui_->result_line->setText(new_label);
    });
  }
}

void MainWindow::on_push_button_clear_clicked() { ui_->result_line->clear(); }

void MainWindow::on_push_button_calc_clicked() {
  try {
    controller_->Calculate(ui_->result_line->text().toStdString(),
                           ui_->double_spin_box_x_value->value());
    ui_->result_line->setText(
        QString::number(controller_->GetResult(), 'd', 8));
    ui_->status_line->setText("OK");
  } catch (const std::exception& e) {
    ui_->result_line->setText("0");
    ui_->status_line->setText("ERROR");
  }
}

void MainWindow::on_push_button_make_graph_clicked() {
  double min_x = ui_->double_spin_box_min_x->value();
  double min_y = ui_->double_spin_box_min_y->value();
  double max_x = ui_->double_spin_box_max_x->value();
  double max_y = ui_->double_spin_box_max_y->value();
  double h = (max_x - min_x) / 10000;

  if (min_x < max_x && min_y < max_y) {
    QVector<double> x, y;
    x.clear();
    y.clear();

    ui_->graph->clearGraphs();

    for (double x_value = min_x; x_value <= max_x; x_value += h) {
      double y_value = 0;
      try {
        controller_->Calculate(ui_->result_line->text().toStdString(), x_value);
      } catch (const std::exception& e) {
        ui_->status_line->setText("ERROR");
        return;
      }
      y_value = controller_->GetResult();
      ui_->status_line->setText("OK");
      if (y_value < min_y) y_value = qQNaN();
      if (y_value > max_y) y_value = qQNaN();
      x.push_back(x_value);
      y.push_back(y_value);
    }

    ui_->graph->xAxis->setRange(min_x, max_x);
    ui_->graph->yAxis->setRange(min_y, max_y);
    ui_->graph->addGraph();
    ui_->graph->graph(0)->addData(x, y);
    ui_->graph->replot();
    x.clear();
    y.clear();
  }
}
}  // namespace s21
