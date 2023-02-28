#ifndef RenderWindowUIMultipleInheritance_H
#define RenderWindowUIMultipleInheritance_H

#include "Viewer.h"
#include "itk.h"
#include "ui_SimpleView.h"
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTemporaryDir>
#include <iostream>
#include <qfont.h>
#include <string>

class RenderWindowUIMultipleInheritance : public QMainWindow,
                                          private Ui::SimpleView {
  Q_OBJECT
public:
  RenderWindowUIMultipleInheritance();

public slots:

  virtual void slotExit();

private slots:

  void on_UpperThreshold_valueChanged(int value);
  void on_LowerThreshold_valueChanged(int value);
  void on_DCM_Slice_change_sliderMoved(int position);
  void on_ReadData_clicked();
  void on_Crop_clicked();
  void on_ShowModel_clicked();
  void on_Show_in_VR_clicked();

private:
  int theLowerThreshold{};
  int theUpperThreshold{};
  int GlobalActualSlice{};
  void Threshold(void);
  void ThresholdCord(void);
  void ShowCropTool();
  void Print(void);
  void updateLabel();
  void callThresholdFilter();
  void exportModel();
  void openVRviewer();
  void readDicom();
  void setLabels();
  std::string getDicomImagesFolder();

  std::unique_ptr<ITK> itkObject = std::make_unique<ITK>();
  std::unique_ptr<Viewer> viewer = std::make_unique<Viewer>();
  BinaryThresholdFilter::Pointer intervertebrae = BinaryThresholdFilter::New();
  BinaryThresholdFilter::Pointer spinalCord = BinaryThresholdFilter::New();
};

#endif RenderWindowUIMultipleInheritance_H
