#include "main_window.h"

#include <QCloseEvent>
#include <QDockWidget>
#include <QMenuBar>
#include <QToolBar>
#include <vtkGenericOpenGLRenderWindow.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) { Init(); }

MainWindow::~MainWindow() {}

void MainWindow::Init() {
  InitPointCloud();
  InitLog();
}

void MainWindow::InitPointCloud() {
  cloud_widget_ = new QWidget(this);
  setCentralWidget(cloud_widget_);

  cloud_native_widget_ = new QVTKOpenGLNativeWidget(cloud_widget_);
  cloud_native_widget_->setSizePolicy(QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);
  cloud_native_widget_->setMinimumSize(640, 480);

  cloud_layout_ = new QGridLayout(cloud_widget_);
  cloud_layout_->setObjectName("cloud_ldyout");
  cloud_layout_->addWidget(cloud_native_widget_, 0, 0, 1, 1);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();

  auto render_window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

  render_window->AddRenderer(renderer);
  clouder_ = new Clouder(renderer, render_window, "点云显示", false);
  clouder_->setupInteractor(cloud_native_widget_->interactor(),
                            cloud_native_widget_->renderWindow());
}

void MainWindow::InitLog() {
  log_widget_ = new QWidget();

  log_list_widget_ = new QListWidget(log_widget_);
  log_list_widget_->setEditTriggers(
      QAbstractItemView::EditTrigger::AllEditTriggers);
  log_list_widget_->setSelectionMode(
      QAbstractItemView::SelectionMode::SingleSelection);

  log_layout_ = new QGridLayout(log_widget_);
  log_layout_->addWidget(log_list_widget_, 0, 0, 1, 1);

  log_dock_widget_ = new QDockWidget(this);
  // 底部
  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, log_dock_widget_);
  log_dock_widget_->setWidget(log_widget_);
  log_dock_widget_->setWindowTitle("控制台");
}

void MainWindow::InitMenuBar() {
  menu_bar_ = new QMenuBar(this);
  menu_bar_->setObjectName("menu_bar");
}

void MainWindow::InitToolBar() {
  tool_bar_ = new QToolBar(this);
  tool_bar_->setObjectName("tool_bar");
  addToolBar(Qt::TopToolBarArea, tool_bar_);
  tool_bar_->addAction(up_);
  tool_bar_->addAction(down_);
}

void MainWindow::InitAction() {
  up_ = new QAction("up", this);
  down_ = new QAction("down", this);
}

void MainWindow::CloseEvent(QCloseEvent *event) {
  event->ignore();
  // height_dlg_.close();
}

void MainWindow::Connect() {
  connect(up_, &QAction::triggered, this, &MainWindow::OnAciontUp);
  // connect(&height_dlg_, &HeightDlg::Change, this, &MainWindow::RunHeightDlg);
}

void MainWindow::OnAciontUp() {
  if (!pc_->empty()) {
    clouder_->setCameraPosition(
        0.5 * (p_min_.x + p_max_.x), 0.5 * (p_min_.y + p_max_.y),
        p_max_.z + 2 * max_len_, 0.5 * (p_min_.x + p_max_.x),
        0.5 * (p_min_.y + p_max_.y), p_max_.z, 0, 1, 0);
    cloud_native_widget_->update();
  }
}
