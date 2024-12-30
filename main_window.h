#pragma once

#include <QGridLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

using Point = pcl::PointXYZ;
using PC = pcl::PointCloud<Point>;
using Clouder = pcl::visualization::PCLVisualizer;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  // qt功能
private slots:
  void OnAciontUp();

private:
  void Init();
  void InitPointCloud(); // 初始化点云
  void InitLog();        // 初始化控制台日志
  void InitMenuBar();
  void InitToolBar();
  void InitAction();
  void CloseEvent(QCloseEvent *event);
  void Connect();

  // ---- 点云 ----
  QWidget *cloud_widget_;
  QGridLayout *cloud_layout_;
  QVTKOpenGLNativeWidget *cloud_native_widget_;
  Clouder *clouder_;
  PC::Ptr pc_;
  Point p_min_, p_max_;          // 点云的最小值和最大值
  double max_len_;               // 最大长度
  QList<PC::Ptr> height_clouds_; // 高度渲染的点云列

  // ---- 控制台 ----
  QDockWidget *log_dock_widget_;
  QWidget *log_widget_;
  QGridLayout *log_layout_;
  QListWidget *log_list_widget_;

  // ---- 工程目录 ----
  QDockWidget *project_dock_widget_;
  QWidget *project_widget_;
  QGridLayout *project_layout_;

  // ---- 菜单栏 ----
  QMenuBar *menu_bar_;

  // ---- 工具栏 ----
  QToolBar *tool_bar_;
  QAction *up_;
  QAction *down_;
};
