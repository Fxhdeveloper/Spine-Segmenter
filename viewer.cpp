#include "viewer.h"
#include "myvtkinteractorstyleimage.h"
#include <itkCurvatureFlowImageFilter.h>
#include <vtkAutoInit.h>
#include <vtkBorderWidget.h>
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkOBJExporter.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkbordercallback.h>

vtkStandardNewMacro(myVtkInteractorStyleImage)
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
        vtkSmartPointer<myVtkInteractorStyleImage>::New();

using CurvatureFlowImageFilterType =
    itk::CurvatureFlowImageFilter<InputImageType, InputImageType>;

Viewer::Viewer() { this->setupUi(this); }

void Viewer::readDicomData(std::string folder) {
  reader->SetDirectoryName(folder.c_str());
  reader->Update();
}

void Viewer::setViewer() {

  imageViewer->SetInputConnection(reader->GetOutputPort());

  qvtkWidget->SetRenderWindow(renderWindow);
  renderWindowInteractor = qvtkWidget->GetInteractor();

  imageViewer->SetRenderWindow(qvtkWidget->GetRenderWindow());
  myInteractorStyle->SetImageViewer(imageViewer);

  imageViewer->SetupInteractor(renderWindowInteractor);
  renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

  imageViewer->Render();
  //    imageViewer->GetRenderer()->ResetCamera();
  //    imageViewer->Render();
  renderWindowInteractor->Start();
}

void Viewer::showCropTool() {
  // create an interactor with our own style (inherit from
  // vtkInteractorStyleImage) in order to catch mousewheel and key events
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkBorderWidget> borderWidget =
      vtkSmartPointer<vtkBorderWidget>::New();
  borderWidget->SetInteractor(renderWindowInteractor);
  static_cast<vtkBorderRepresentation *>(borderWidget->GetRepresentation())
      ->GetBorderProperty()
      ->SetColor(1, 0, 0);
  borderWidget->SelectableOff();

  vtkSmartPointer<vtkBorderCallback> borderCallback =
      vtkSmartPointer<vtkBorderCallback>::New();

  borderCallback->SetImageViewer(imageViewer);
  borderWidget->AddObserver(vtkCommand::InteractionEvent, borderCallback);

  vtkSmartPointer<myVtkInteractorStyleImage> interactorStyle =
      vtkSmartPointer<myVtkInteractorStyleImage>::New();

  interactorStyle->SetImageViewer(imageViewer);
  imageViewer->SetupInteractor(renderWindowInteractor);

  renderWindowInteractor->SetInteractorStyle(interactorStyle);

  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();
  borderWidget->On();
  renderWindowInteractor->Start();
}

template <typename T>
vtkSmartPointer<vtkMarchingCubes> Viewer::extractSurface(T inputData) {

  auto surface = vtkSmartPointer<vtkMarchingCubes>::New();
  surface->SetInputData(inputData);
  surface->ComputeNormalsOn();
  surface->SetValue(0, 1.3);

  return surface;
}

vtkSmartPointer<vtkImageFlip>
Viewer::flipImage(vtkSmartPointer<vtkImageData> inputData,
                  int flipAxis) // flip x axis
{
  auto flipXFilter = vtkSmartPointer<vtkImageFlip>::New();
  flipXFilter->SetFilteredAxis(flipAxis);
  flipXFilter->SetInputData(inputData);
  flipXFilter->Update();

  return flipXFilter;
}

void Viewer::objExporter(std::string path) {

  vtkSmartPointer<vtkOBJExporter> myobjexporter =
      vtkSmartPointer<vtkOBJExporter>::New();
  myobjexporter->SetRenderWindow(renderWindowOpenGL2);
  myobjexporter->SetFilePrefix(path.c_str());
  myobjexporter->Write();
}

template <typename T>
vtkSmartPointer<vtkMarchingCubes> Viewer::get3DSurface(T inputImage) {

  vtkSmartPointer<vtkImageData> volume = getVtkVolumeFromItkFilter(inputImage);
  auto surface = extractSurface(volume);
  return surface;
}

void Viewer::show3dModel(BinaryThresholdFilter::Pointer volume1,
                         BinaryThresholdFilter::Pointer volume2) {

  auto surface = get3DSurface(volume1);
  auto surface2 = get3DSurface(volume2);
  initMapper(rightmapper, surface2);
  initMapper(leftmapper, surface);
  initActor(rightactor, rightmapper);
  initActor(leftactor, leftmapper);

  vtkrenderWindow->SetSize(900, 900);
  interactor->SetRenderWindow(vtkrenderWindow);
  interactor->SetInteractorStyle(style);
  vtkrenderWindow->AddRenderer(leftRenderer);
  initRenderer();

  qvtkWidget_2->SetRenderWindow(renderWindowOpenGL2);
  qvtkWidget_2->GetRenderWindow()->AddRenderer(leftRenderer);
  qvtkWidget_2->update();
}

void Viewer::initMapper(vtkSmartPointer<vtkPolyDataMapper> mapper,
                        vtkSmartPointer<vtkMarchingCubes> surface) {

  mapper->SetInputConnection(surface->GetOutputPort());
  mapper->ScalarVisibilityOff();
}

void Viewer::initActor(vtkSmartPointer<vtkActor> actor,
                       vtkSmartPointer<vtkPolyDataMapper> mapper) {
  actor->GetProperty()->SetColor(1, 0.547237, 0.319073);
  actor->GetProperty()->SetEdgeVisibility(.9);
  actor->GetProperty()->SetEdgeColor(1, 0, 0);
  actor->GetProperty()->SetShading(.1);
  actor->GetProperty()->SetOpacity(1.0);
  actor->SetMapper(mapper);
}

void Viewer::initRenderer() {
  leftRenderer->SetBackground(0.329412, 0.34902, 0.427451);
  // leftRenderer->SetBackground(1, 0, 1);
  leftRenderer->AddActor(leftactor);
  leftRenderer->AddActor(rightactor);
  leftRenderer->ResetCamera();
}

void Viewer::updateImageViewer(vtkSmartPointer<vtkImageFlip> flipXFilter) {

  imageViewer->SetInputConnection(flipXFilter->GetOutputPort());
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->Render();
}

const vtkSmartPointer<vtkImageViewer2> Viewer::getImageViewer() const {

  return imageViewer;
}

void Viewer::updateCurrentSlice(int position) {

  imageViewer->SetSlice(position);
  imageViewer->Render();
}
template <typename T> void Viewer::renderVolume(T processedImage) {

  auto volume = getVtkVolumeFromItkFilter(processedImage);
  auto flipXFilter = flipImage(volume);
  updateImageViewer(flipXFilter);
}

template <typename T>
vtkSmartPointer<vtkImageData> Viewer::getVtkVolumeFromItkFilter(T inputImage) {

  auto connector = castItkToVtk(inputImage);
  auto volume = vtkSmartPointer<vtkImageData>::New();
  volume->DeepCopy(connector->GetOutput());
  return volume;
}

template <typename T> ConnectorType::Pointer Viewer::castItkToVtk(T inputData) {
  auto caster = CastingFilterType::New();
  auto connector = ConnectorType::New();

  caster->SetInput(inputData->GetOutput());
  connector->SetInput(caster->GetOutput());
  connector->Update();

  return connector;
}

template ConnectorType::Pointer
    Viewer::castItkToVtk<CurvatureFlowImageFilterType::Pointer>(
        CurvatureFlowImageFilterType::Pointer);

template void Viewer::renderVolume<CurvatureFlowImageFilterType::Pointer>(
    CurvatureFlowImageFilterType::Pointer);

template void Viewer::renderVolume<BinaryThresholdFilter::Pointer>(
    BinaryThresholdFilter::Pointer);
