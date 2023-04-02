#ifndef VIEWER_H
#define VIEWER_H

#include "ui_SimpleView.h"
#include <QMainWindow>

#include "CommonHeaders.h"
#include "itkCastImageFilter.h"
#include "itkImageToVTKImageFilter.h"
#include <itkBinaryThresholdImageFilter.h>
#include <vtkActor.h>

#include <vtkAutoInit.h>
#include <vtkDICOMImageReader.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageFlip.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

using BinaryThresholdFilter =
    itk::BinaryThresholdImageFilter<InputImageType, InputImageType>;
using ConnectorType = itk::ImageToVTKImageFilter<OutputImageType>;
using CastingFilterType = itk::CastImageFilter<InputImageType, OutputImageType>;

class Viewer : public QMainWindow, private Ui::SimpleView {
  Q_OBJECT
public:
  Viewer();

  void readDicomData(std::string folder);
  void setViewer();
  void showCropTool();
  const vtkSmartPointer<vtkImageViewer2> getImageViewer() const;
  void updateCurrentSlice(int position);
  void objExporter(std::string path);
  vtkSmartPointer<vtkImageFlip>
  flipImage(vtkSmartPointer<vtkImageData> inputData, int flipAxis = 1);

  void show3dModel(BinaryThresholdFilter::Pointer volume1,
                   BinaryThresholdFilter::Pointer volume2);
  template <typename T> void renderVolume(T processedImage);

private:
  template <typename T>
  vtkSmartPointer<vtkMarchingCubes> extractSurface(T inputData);
  template <typename T>
  vtkSmartPointer<vtkMarchingCubes> get3DSurface(T inputImage);
  template <typename T>
  vtkSmartPointer<vtkImageData> getVtkVolumeFromItkFilter(T inputImage);
  template <typename T> ConnectorType::Pointer castItkToVtk(T inputData);

  void initMapper(vtkSmartPointer<vtkPolyDataMapper> mapper,
                  vtkSmartPointer<vtkMarchingCubes> surface);
  void initActor(vtkSmartPointer<vtkActor> actor,
                 vtkSmartPointer<vtkPolyDataMapper> mapper);
  void initRenderer();
  void updateImageViewer(vtkSmartPointer<vtkImageFlip> flipXFilter);

  vtkSmartPointer<vtkDICOMImageReader> reader =
      vtkSmartPointer<vtkDICOMImageReader>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer =
      vtkSmartPointer<vtkImageViewer2>::New();
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow =
      vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderWindow> vtkrenderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkRenderer> leftRenderer =
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkPolyDataMapper> rightmapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> rightactor = vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  vtkSmartPointer<vtkPolyDataMapper> leftmapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> leftactor = vtkSmartPointer<vtkActor>::New();
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindowOpenGL2 =
      vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
};

#endif // VIEWER_H
