#include "viewer.h"
#include "myvtkinteractorstyleimage.h"
#include <vtkBorderWidget.h>
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkOBJExporter.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkbordercallback.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

vtkStandardNewMacro(myVtkInteractorStyleImage)
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
        vtkSmartPointer<myVtkInteractorStyleImage>::New();

void Viewer::readDicomData(std::string folder) {
  readervtk->SetDirectoryName(folder.c_str());
  readervtk->Update();
}

void Viewer::setViewer() {

  imageViewer->SetInputConnection(readervtk->GetOutputPort());

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
